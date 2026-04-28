/**
 * @file ToolBarWidget.h
 * @brief Menu bar widget displayed at the top of the main window.
 *
 * Hosts eight ToolTextButton items (Files, Mark, Commands, Net, Show,
 * Configuration, Start, Help), each wired to a QMenu populated with
 * the standard Total Commander menu entries.
 *
 * Left-side buttons are left-aligned; "Help" is pushed to the right.
 */

#pragma once
#ifndef MYTOOLBARWIDGET_H
#define MYTOOLBARWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

/**
 * @class ToolBarWidget
 * @brief The top-level menu bar containing all application menus.
 *
 * The widget uses the Qt object name @c "menuBar" so that @c style.qss
 * can target it with the selector <tt>#menuBar { … }</tt>.
 *
 * Menu contents are built by static factory functions defined in the
 * corresponding .cpp file and assigned to each button via
 * @c QPushButton::setMenu().
 */
class ToolBarWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the menu bar and populates all menus.
     * @param parent Optional Qt parent widget.
     */
    explicit ToolBarWidget(QWidget *parent = nullptr);

    /** @brief Destructor (child widgets are cleaned up by Qt's parent chain). */
    ~ToolBarWidget() = default;

private:
    QHBoxLayout *_layout; ///< Root horizontal layout of the bar.
    QHBoxLayout *_left;   ///< Left-aligned group (Files … Start).
    QHBoxLayout *_right;  ///< Right-aligned group (Help).
};

#endif
