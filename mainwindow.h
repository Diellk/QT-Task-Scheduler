#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "taskscheduler.h"

/**
 * @class MainWindow
 * @brief The main window of the application that manages tasks via a system tray icon.
 *
 * The MainWindow class provides a user interface for managing scheduled tasks.
 * It uses a QSystemTrayIcon to allow users to interact with the application,
 * including adding new tasks and viewing current tasks.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  // Constructor
    ~MainWindow();  // Destructor

private:
    QSystemTrayIcon *trayIcon;  ///< System tray icon for the application.
    QMenu *trayMenu;  ///< Context menu for the system tray icon.
    QAction *exitAction;  ///< Action to exit the application.
    QAction *viewTasksAction;  ///< Action to view the current tasks.
    QAction *addTaskAction;  ///< Action to add a new task.
    TaskScheduler *scheduler;  ///< Task scheduler to manage tasks.

    /**
     * @brief Creates the system tray icon and its context menu.
     */
    void createTrayIcon();

    /**
     * @brief Creates the actions for the tray menu.
     */
    void createActions();

private slots:
    /**
     * @brief Handles the activation of the system tray icon.
     * @param reason The reason for the tray icon activation.
     */
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

    /**
     * @brief Shows a dialog to view the current tasks.
     */
    void showViewTasksDialog();

    /**
     * @brief Shows a dialog to add a new task.
     */
    void showAddTaskDialog();
};

#endif // MAINWINDOW_H
