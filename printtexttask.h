#ifndef PRINTTEXTTASK_H
#define PRINTTEXTTASK_H

#include <QObject>
#include <QTimer>
#include <QDebug>

/**
 * @class PrintTextTask
 * @brief A task that periodically prints a text to the debug output.
 *
 * The PrintTextTask class allows the user to set a text message that will be
 * printed to the debug output at regular intervals.
 */
class PrintTextTask : public QObject {
    Q_OBJECT

public:

    explicit PrintTextTask(QObject *parent = nullptr);  // Constructor
    /**
     * @brief Starts the task to print text.
     */
    void startTask();

    /**
     * @brief Sets the text to be printed.
     * @param text The text to be printed.
     */
    void setText(const QString &text);  // Method to set the text to print

private:
    QString text; ///< The text to be printed at regular intervals.
};

#endif // PRINTTEXTTASK_H
