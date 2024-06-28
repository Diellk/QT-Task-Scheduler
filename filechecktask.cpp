#include "filechecktask.h"

/**
 * @brief Constructs a FileCheckTask object.
 * @param parent The parent QObject, defaults to nullptr.
 */
FileCheckTask::FileCheckTask(QObject *parent)
    : QObject(parent) {}  // Constructor

/**
 * @brief Starts the task to check the file existence.
 */
void FileCheckTask::startTask() {
    if (!QFile::exists(filePath)) {  // Check if the file exists
        qDebug() << "File does not exist" << filePath;  // Print message if the file does not exist
    }else {
        qDebug() << "File is present" << filePath;
    }
}

/**
 * @brief Sets the file path to check for existence.
 * @param filePath The path of the file to check.
 */
void FileCheckTask::setFilePath(const QString &filePath) {
    this->filePath = filePath;
}
