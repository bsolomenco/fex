/**
 * @file CenterBar.h
 * @brief Vertical action bar placed between the two FilePanel widgets.
 *
 * Provides three buttons that trigger file-manager operations:
 *
 * | Button  | Action                                             |
 * |---------|----------------------------------------------------|
 * | Copy    | Copy selection from active panel to the other      |
 * | Compare | Open CompareDialog for the two panel directories   |
 * | Search  | Open SearchDialog rooted at the active panel path  |
 *
 * The bar has a fixed width (set in @c style.qss via @c #centerBar) so
 * it does not stretch as the window is resized.
 */

#pragma once
#ifndef CENTERBAR_H
#define CENTERBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

/**
 * @class CenterBar
 * @brief Fixed-width vertical bar with Copy, Compare, and Search buttons.
 *
 * The bar only emits signals — it has no knowledge of the file panels or
 * any business logic. MainWindow connects the signals to the appropriate
 * handler slots.
 *
 * The widget uses object name @c "centerBar"; its buttons use
 * @c "centerBarButton" — both are styled in @c style.qss.
 */
class CenterBar : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the bar and creates the three action buttons.
     * @param parent Optional Qt parent widget.
     */
    explicit CenterBar(QWidget *parent = nullptr);

    /** @brief Destructor (child widgets cleaned up by Qt's parent chain). */
    ~CenterBar() = default;

signals:
    /**
     * @brief Emitted when the user clicks the "Copy" button.
     *
     * MainWindow handles this by copying the active panel's selection
     * into the other panel's current directory.
     */
    void copyRequested();

    /**
     * @brief Emitted when the user clicks the "Compare" button.
     *
     * MainWindow opens a CompareDialog for the two panels' directories.
     */
    void compareRequested();

    /**
     * @brief Emitted when the user clicks the "Search" button.
     *
     * MainWindow opens a SearchDialog rooted at the active panel's path.
     */
    void searchRequested();

private:
    QVBoxLayout *_layout; ///< Vertical layout holding the three buttons.

    /**
     * @brief Creates a styled button, adds it to @c _layout, and returns it.
     * @param label The button's display text.
     * @return Pointer to the newly created QPushButton.
     */
    QPushButton *makeButton(const QString &label);
};

#endif
