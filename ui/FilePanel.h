/**
 * @file FilePanel.h
 * @brief Single-pane file browser widget used inside the dual-panel layout.
 *
 * Each FilePanel is self-contained: it owns a drive selector bar, a path
 * label, and a QTableView backed by a QFileSystemModel. Two instances of
 * this widget (left and right) are placed side-by-side in MainWindow.
 *
 * Layout inside the widget:
 * @code
 *  ┌─────────────────────────────────────┐
 *  │  /  /home  /mnt  …  (drive buttons) │  ← _driveBar
 *  ├─────────────────────────────────────┤
 *  │  /home/user/Documents               │  ← _pathLabel
 *  ├─────────────────────────────────────┤
 *  │  Name          Size    Date         │
 *  │  .git/          –      2024-01-01   │  ← _view / _model
 *  │  README.md    4 KB     2024-03-15   │
 *  │  …                                  │
 *  └─────────────────────────────────────┘
 * @endcode
 */

#pragma once
#ifndef FILEPANEL_H
#define FILEPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QFileSystemModel>
#include <QLabel>
#include <QPushButton>

/**
 * @class FilePanel
 * @brief A file-browser pane backed by QFileSystemModel.
 *
 * The panel displays the contents of one directory at a time. Navigating
 * into a subdirectory is done by double-clicking a folder row. Drive
 * buttons at the top jump to the root of each mounted volume.
 *
 * The widget uses the Qt object name @c "filePanel" so that @c style.qss
 * can target it with <tt>#filePanel { … }</tt>.
 */
class FilePanel : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the panel, sets up the model and view, and navigates
     *        to the user's home directory.
     * @param parent Optional Qt parent widget.
     */
    explicit FilePanel(QWidget *parent = nullptr);

    /** @brief Destructor (child widgets cleaned up by Qt's parent chain). */
    ~FilePanel() = default;

    /**
     * @brief Navigates the panel to the given directory.
     *
     * Updates both the table view root index and the path label, then
     * emits @c pathChanged.
     *
     * @param path Absolute path to the target directory.
     */
    void navigateTo(const QString &path);

    /**
     * @brief Returns the absolute path of the currently displayed directory.
     * @return Current directory path.
     */
    QString currentPath() const;

    /**
     * @brief Returns the absolute paths of all currently selected entries.
     *
     * Uses @c QItemSelectionModel::selectedRows() so each entry is counted
     * once regardless of how many columns are visible.
     *
     * @return List of absolute file/directory paths; empty if nothing is selected.
     */
    QStringList selectedFiles() const;

    /**
     * @brief Forces the panel to reload the current directory.
     *
     * Internally calls @c navigateTo() with the current path, which
     * resets the model root index and re-reads the directory.
     */
    void refresh();

signals:
    /**
     * @brief Emitted whenever the displayed directory changes.
     * @param path The new absolute directory path.
     */
    void pathChanged(const QString &path);

    /**
     * @brief Emitted when the user clicks anywhere inside this panel.
     *
     * MainWindow connects this to @c setActivePanel() to track which
     * panel is currently focused.
     *
     * @param panel Pointer to @c this panel.
     */
    void activated(FilePanel *panel);

private slots:
    /**
     * @brief Handles a double-click on a table row.
     *
     * Navigates into the entry if it is a directory; files are currently
     * ignored (open-with support can be added here).
     *
     * @param index Model index of the double-clicked item.
     */
    void onDoubleClicked(const QModelIndex &index);

private:
    QVBoxLayout      *_layout;    ///< Root vertical layout of the panel.
    QWidget          *_driveBar;  ///< Horizontal bar of mounted-volume buttons.
    QLabel           *_pathLabel; ///< Shows the current directory path.
    QTableView       *_view;      ///< Table showing directory contents.
    QFileSystemModel *_model;     ///< Filesystem data source for _view.

    /**
     * @brief Populates @c _driveBar with one button per mounted volume.
     *
     * Uses QStorageInfo::mountedVolumes() to enumerate volumes at startup.
     * Clicking a drive button calls @c navigateTo() with the volume's root.
     */
    void buildDriveBar();

    /**
     * @brief Configures @c _view appearance and connects model/view signals.
     *
     * Sets column resize modes, hides the vertical header, enables
     * alternating row colors, and enables multi-row selection.
     */
    void setupView();
};

#endif
