#ifndef FILECHECKTASK_H
#define FILECHECKTASK_H

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QDebug>

/**
 * @class FileCheckTask
 * @brief A task that periodically checks for the existence of a specified file.
 *
 * The FileCheckTask class allows the user to set a file path and checks if the
 * file exists at regular intervals. If the file does not exist, it prints a
 * message to the debug output.
 */
class FileCheckTask : public QObject {
    Q_OBJECT

public:
    explicit FileCheckTask(QObject *parent = nullptr);  // Constructor

    /**
     * @brief Starts the task to check the file existence.
     */
    void startTask();

    /**
     * @brief Sets the file path to check for existence.
     * @param filePath The path of the file to check.
     */
    void setFilePath(const QString &filePath);  // Method to set the file path

private:
    QString filePath;  ///< The path of the file to be checked.
};

#endif // FILECHECKTASK_H
