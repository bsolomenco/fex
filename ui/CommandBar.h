/**
 * @file CommandBar.h
 * @brief Single-line command input bar displayed below the file panels.
 *
 * Mirrors the command bar found in Total Commander: a prompt label on the
 * left shows the active directory, and a QLineEdit on the right accepts
 * typed commands.  Pressing Enter emits @c commandEntered and clears the
 * input field.
 *
 * The prompt is updated automatically by MainWindow whenever the active
 * panel changes directory.
 */

#pragma once
#ifndef COMMANDBAR_H
#define COMMANDBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

/**
 * @class CommandBar
 * @brief Path-prompt widget and shell command input line.
 *
 * Layout: <tt>[ /home/user> ] [ ________________________________ ]</tt>
 *
 * The widget uses the Qt object name @c "commandBar".
 * Its prompt label uses @c "commandLabel" and the input field uses
 * @c "commandInput" — all styled in @c style.qss.
 */
class CommandBar : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the command bar with an initial @c "~>" prompt.
     * @param parent Optional Qt parent widget.
     */
    explicit CommandBar(QWidget *parent = nullptr);

    /** @brief Destructor (child widgets cleaned up by Qt's parent chain). */
    ~CommandBar() = default;

    /**
     * @brief Updates the prompt label to show the given path.
     *
     * Called by MainWindow whenever @c FilePanel::pathChanged is emitted
     * for the currently active panel.
     *
     * @param path The new directory path to display in the prompt.
     */
    void setPrompt(const QString &path);

signals:
    /**
     * @brief Emitted when the user presses Enter in the input field.
     *
     * The input field is cleared immediately after this signal is emitted.
     *
     * @param command The text that was entered by the user.
     */
    void commandEntered(const QString &command);

private:
    QHBoxLayout *_layout; ///< Horizontal layout of the bar.
    QLabel      *_label;  ///< Prompt label showing the current path.
    QLineEdit   *_input;  ///< Text field for command input.
};

#endif
