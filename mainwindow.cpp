#include "mainwindow.h"
#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QInputDialog>
#include <functional>
#include "printtexttask.h"
#include "filechecktask.h"

/**
 * @brief Constructs a MainWindow object.
 * @param parent The parent QWidget, defaults to nullptr.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scheduler(new TaskScheduler(this)) {
    createActions();  // Create actions for the tray menu
    createTrayIcon();  // Create the tray icon

    // Add initial/example tasks to the scheduler
    PrintTextTask *printTextTask = new PrintTextTask(this);
    printTextTask->setText("Example Text");
    scheduler->addTask(std::bind(&PrintTextTask::startTask, printTextTask), 10000, "Print Text");

    FileCheckTask *fileCheckTask = new FileCheckTask(this);
    fileCheckTask->setFilePath("C:/EXAMPLE.txt");
    scheduler->addTask(std::bind(&FileCheckTask::startTask, fileCheckTask), 30000, "Check File");
}

MainWindow::~MainWindow() {}

/**
 * @brief Creates the actions for the tray menu.
 */
void MainWindow::createActions() {
    exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

    viewTasksAction = new QAction("View Tasks", this);
    connect(viewTasksAction, &QAction::triggered, this, &MainWindow::showViewTasksDialog);

    addTaskAction = new QAction("Add Task", this);
    connect(addTaskAction, &QAction::triggered, this, &MainWindow::showAddTaskDialog);
}

/**
 * @brief Creates the system tray icon and its context menu.
 */
void MainWindow::createTrayIcon() {
    trayMenu = new QMenu(this);
    trayMenu->addAction(viewTasksAction);
    trayMenu->addAction(addTaskAction);
    trayMenu->addAction(exitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/new/prefix1/resources/TICARE-200x78.png"));
    trayIcon->setContextMenu(trayMenu);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::trayIconActivated);

    trayIcon->show();
}

/**
 * @brief Handles the activation of the system tray icon.
 * @param reason The reason for the tray icon activation.
 */
void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        if (isVisible()) {
            hide();
        } else {
            show();
            activateWindow();
        }
    } else if (reason == QSystemTrayIcon::DoubleClick) {
        show();
        activateWindow();
    }
}

/**
 * @brief Shows a dialog to view the current tasks.
 */
void MainWindow::showViewTasksDialog() {
    QString taskList;
    auto tasks = scheduler->getActiveTasks();
    for (const auto &task : tasks) {
        taskList += task + "\n";
    }
    if (taskList.isEmpty()) {
        taskList = "No tasks scheduled.";
    }
    QMessageBox::information(this, "Current Tasks", taskList);
}

/**
 * @brief Shows a dialog to add a new task.
 */
void MainWindow::showAddTaskDialog() {
    bool ok;
    QStringList taskTypes;
    taskTypes << "Print Text" << "Check File";
    QString taskType = QInputDialog::getItem(this, "Add Task", "Task Type:", taskTypes, 0, false, &ok);
    if (ok && !taskType.isEmpty()) {
        if (taskType == "Print Text") {
            QString text = QInputDialog::getText(this, "Add Print Text Task", "Enter text to print:", QLineEdit::Normal, "", &ok);
            if (ok && !text.isEmpty()) {
                PrintTextTask *printTextTask = new PrintTextTask(this);
                printTextTask->setText(text);
                scheduler->addTask(std::bind(&PrintTextTask::startTask, printTextTask), 10000, "Print Text");
            }
        } else if (taskType == "Check File") {
            QString filePath = QInputDialog::getText(this, "Add File Check Task", "Enter file path to check:", QLineEdit::Normal, "", &ok);
            if (ok && !filePath.isEmpty()) {
                FileCheckTask *fileCheckTask = new FileCheckTask(this);
                fileCheckTask->setFilePath(filePath);
                scheduler->addTask(std::bind(&FileCheckTask::startTask, fileCheckTask), 30000, "Check File");
            }
        }
    }
}
