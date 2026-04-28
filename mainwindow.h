/**
 * @file mainwindow.h
 * @brief Top-level application window — layout and signal wiring only.
 *
 * MainWindow is a thin coordinator:
 *  - It assembles UI widgets into the final layout.
 *  - It creates the three controllers and wires their signals.
 *  - It extracts data from the panels (paths, selections) and passes it
 *    to the appropriate controller — it never performs operations itself.
 *
 * All business logic lives in the controller and service layers.
 *
 * @code
 *  ┌─────────────────────────────────────────┐
 *  │  ToolBarWidget  (menu bar)              │
 *  ├──────────────────┬──────┬───────────────┤
 *  │  FilePanel left  │Center│ FilePanel right│
 *  ├──────────────────┴──────┴───────────────┤
 *  │  CommandBar                             │
 *  ├─────────────────────────────────────────┤
 *  │  FunctionBar  (F1–F10)                  │
 *  └─────────────────────────────────────────┘
 * @endcode
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui/ToolBarWidget.h"
#include "ui/FilePanel.h"
#include "ui/CenterBar.h"
#include "ui/CommandBar.h"
#include "ui/FunctionBar.h"
#include "controller/FileOperationController.h"
#include "controller/CompareController.h"
#include "controller/SearchController.h"

/**
 * @class MainWindow
 * @brief Root window that owns all UI panels and the three action controllers.
 *
 * The window tracks which FilePanel is "active" (last clicked) so that
 * controllers always operate on the correct panel without needing to
 * know about panels themselves.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs and shows the complete UI, wires all signals.
     * @param parent Optional Qt parent (normally @c nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /** @brief Destructor. */
    ~MainWindow();

private:
    // ── UI panels ────────────────────────────────────────────────────────
    ToolBarWidget *_menuBar;     ///< Top menu bar.
    FilePanel     *_leftPanel;   ///< Left file-browser pane.
    CenterBar     *_centerBar;   ///< Copy / Compare / Search buttons.
    FilePanel     *_rightPanel;  ///< Right file-browser pane.
    CommandBar    *_commandBar;  ///< Path prompt and command input.
    FunctionBar   *_functionBar; ///< F1–F10 shortcut bar.

    FilePanel *_activePanel; ///< Panel that received the most recent click.

    // ── Controllers ──────────────────────────────────────────────────────
    FileOperationController *_fileOpController;  ///< Handles copy flow.
    CompareController       *_compareController; ///< Handles compare flow.
    SearchController        *_searchController;  ///< Handles search flow.

    // ── Setup helpers ─────────────────────────────────────────────────────
    /** @brief Creates and arranges all child widgets. */
    void setupLayout();

    /** @brief Creates controllers and wires all inter-widget signals. */
    void connectSignals();

    /**
     * @brief Updates @c _activePanel and syncs the command bar prompt.
     * @param panel The panel that was just activated by the user.
     */
    void setActivePanel(FilePanel *panel);

    /** @brief Returns the panel that is NOT currently active. */
    FilePanel *inactivePanel() const;
};

#endif
