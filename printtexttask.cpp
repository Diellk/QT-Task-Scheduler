#include "printtexttask.h"

/**
 * @brief Constructs a PrintTextTask object.
 * @param parent The parent QObject, defaults to nullptr.
 */
PrintTextTask::PrintTextTask(QObject *parent)
    : QObject(parent) {}  // Constructor

/**
 * @brief Starts the task to print text.
 */
void PrintTextTask::startTask() {
    qDebug() << text;  // Print text to debug output
}

/**
 * @brief Sets the text to be printed.
 * @param text The text to be printed.
 */
void PrintTextTask::setText(const QString &text) {
    this->text = text;
}
