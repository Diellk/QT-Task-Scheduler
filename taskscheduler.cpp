#include "taskscheduler.h"

/**
 * @brief Constructs a TaskScheduler object.
 * @param parent The parent QObject, defaults to nullptr.
 */
TaskScheduler::TaskScheduler(QObject *parent)
    : QObject(parent) {}

/**
 * @brief Adds a new task to the scheduler.
 * @param taskFunction The function to execute for the task.
 * @param interval The interval at which the task should be executed, in milliseconds.
 * @param type A string identifier for the task type.
 */
void TaskScheduler::addTask(std::function<void()> taskFunction, int interval, const QString &type) {
    Task task = { taskFunction, interval, type };
    activeTasks.append(task);  // Add task to the list of active tasks

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this,std::bind(&TaskScheduler::enqueueTask, this, task));
    timer->start(interval);
}

/**
 * @brief Adds a task to the task queue and attempts to execute it.
 * @param task The task to be added and executed.
 */
void TaskScheduler::enqueueTask(const Task &task){
    QMutexLocker locker(&mutex); //Locks the mutex to ensure safe access to the task queue.
    taskQueue.enqueue(task); //Adds the given task to the queue.
    attemptExecuteTask(); // Calls method to try to execute the next task in the queue.
}

/**
 * @brief Attempts to execute the next task in the queue.
 */
void TaskScheduler::attemptExecuteTask() {
    if (mutex.tryLock()) { // Try to lock the mutex without blocking
        if (!taskQueue.isEmpty()) {
            Task task = taskQueue.dequeue();
            task.taskFunction();
        }
        mutex.unlock(); // Unlock the mutex after execution
    } else {
        // If the mutex is locked, reattempt after a short time
        QTimer::singleShot(100, this, &TaskScheduler::attemptExecuteTask);
    }
}

/**
 * @brief Retrieves a list of active tasks that are still periodically executing.
 * @return A QStringList containing descriptions of the active tasks.
 */
QStringList TaskScheduler::getActiveTasks() const {
    QStringList taskList;
    foreach (const Task &task, activeTasks) {
        taskList.append(QString("Type: %1, Interval: %2 ms").arg(task.type).arg(task.interval));
    }
    return taskList;
}
