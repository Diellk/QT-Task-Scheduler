#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QTimer>
#include <functional>
#include <QStringList>

/**
 * @struct Task
 * @brief Represents a single scheduled task.
 *
 * This structure holds the function to be executed, the interval
 * at which the task should be executed, and a type identifier for the task.
 */
struct Task {
    std::function<void()> taskFunction; ///< The function to execute for the task.
    int interval; ///< The interval at which the task is executed, in milliseconds.
    QString type; ///< A string identifier for the task type.
};

/**
 * @class TaskScheduler
 * @brief Manages the scheduling and execution of tasks.
 *
 * The TaskScheduler class allows tasks to be added with specific intervals
 * and ensures that they are executed in a serialized manner. It supports adding
 * tasks with different types and intervals and manages their execution order.
 */
class TaskScheduler : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs a TaskScheduler object.
     * @param parent The parent QObject, defaults to nullptr.
     */
    explicit TaskScheduler(QObject *parent = nullptr);

    /**
     * @brief Adds a new task to the scheduler.
     * @param taskFunction The function to execute for the task.
     * @param interval The interval at which the task should be executed, in milliseconds.
     * @param type A string identifier for the task type.
     */
    void addTask(std::function<void()> taskFunction, int interval, const QString &type);

    /**
     * @brief Retrieves a list of active tasks that are still periodically executing.
     * @return A QStringList containing descriptions of the active tasks.
     */
    QStringList getActiveTasks() const;

private:
    QQueue<Task> taskQueue; ///< Queue to store tasks.
    QList<Task> activeTasks; ///< List to store active tasks.
    QMutex mutex; ///< Mutex to control access to the function execution.

private slots:
    /**
     * @brief Attempts to execute the next task in the queue.
     */
    void attemptExecuteTask();
    /**
     * @brief Adds a task to the task queue and attempts to execute it.
     * @param task The task to be added and executed.
     */
    void enqueueTask(const Task &task);
};

#endif // TASKSCHEDULER_H
