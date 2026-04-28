/**
 * @file FunctionBar.h
 * @brief F1–F10 shortcut button bar at the bottom of the main window.
 *
 * Replicates the classic Total Commander function key bar where each
 * button is labelled with its F-key number and a short action name:
 *
 * @code
 * [F1 Help][F2 UserMenu][F3 View][F4 Edit][F5 Copy][F6 Move]
 * [F7 MkDir][F8 Delete][F9 PullDn][F10 Quit]
 * @endcode
 *
 * Buttons are equally distributed across the full width of the bar.
 * When clicked, @c functionKeyPressed(n) is emitted and the caller
 * (MainWindow) is responsible for executing the associated action.
 */

#pragma once
#ifndef FUNCTIONBAR_H
#define FUNCTIONBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

/**
 * @class FunctionBar
 * @brief Horizontal row of F1–F10 action buttons.
 *
 * The widget uses the Qt object name @c "functionBar"; each individual
 * button uses @c "functionButton" — both are styled in @c style.qss.
 *
 * Currently the bar only emits signals.  Connecting them to actual
 * operations (View, Edit, Copy …) is done in MainWindow.
 */
class FunctionBar : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the bar and adds all ten function key buttons.
     * @param parent Optional Qt parent widget.
     */
    explicit FunctionBar(QWidget *parent = nullptr);

    /** @brief Destructor (child widgets cleaned up by Qt's parent chain). */
    ~FunctionBar() = default;

signals:
    /**
     * @brief Emitted when any function key button is clicked.
     * @param fKey The F-key number (1 through 10).
     */
    void functionKeyPressed(int fKey);

private:
    QHBoxLayout *_layout; ///< Horizontal layout holding all ten buttons.

    /**
     * @brief Creates one function key button and appends it to @c _layout.
     *
     * The button text is formatted as @c "F<n> <label>", e.g. @c "F5 Copy".
     * Clicking the button emits @c functionKeyPressed(fKey).
     *
     * @param fKey  F-key number (1–10).
     * @param label Short action description shown after the key number.
     */
    void addButton(int fKey, const QString &label);
};

#endif
