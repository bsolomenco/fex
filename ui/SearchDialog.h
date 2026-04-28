/**
 * @file SearchDialog.h
 * @brief Pure-UI search dialog — delegates all search logic to FileSearcher.
 *
 * The dialog owns no search algorithm. It receives a @c FileSearcher*
 * (injected by SearchController) and connects to its @c resultFound /
 * @c finished signals to stream results into the list widget.
 *
 * This satisfies DIP: SearchDialog depends on the FileSearcher abstraction,
 * not on a concrete search implementation.
 */

#pragma once
#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>

class FileSearcher; // forward declaration — keeps the header lightweight

/**
 * @class SearchDialog
 * @brief Modeless file-search dialog powered by an injected FileSearcher.
 *
 * Layout:
 * @code
 *  Search for: [ *.cpp                    ]
 *  Where:      [ /home/user/projects       ]
 *  ┌─────────────────────────────────────┐
 *  │ /home/user/projects/src/main.cpp    │
 *  │ /home/user/projects/src/app.cpp     │
 *  │ …                                   │
 *  └─────────────────────────────────────┘
 *  Found 42 file(s).
 *  [Search]  [Go to Directory]          [Close]
 * @endcode
 *
 * The dialog sets @c WA_DeleteOnClose so it destroys itself when the user
 * closes it (the FileSearcher is parented to the dialog and is cleaned up
 * along with it).
 */
class SearchDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructs the dialog with a pre-filled root path and an injected searcher.
     *
     * @param searchPath Initial "Where:" directory (editable by the user).
     * @param searcher   FileSearcher instance owned externally (or parented to this dialog).
     *                   The dialog connects to its signals; it does NOT take ownership.
     * @param parent     Optional Qt parent widget.
     */
    explicit SearchDialog(const QString &searchPath,
                          FileSearcher  *searcher,
                          QWidget       *parent = nullptr);

    /** @brief Destructor. */
    ~SearchDialog() = default;

signals:
    /**
     * @brief Emitted when the user requests navigation to a result.
     *
     * Triggered by double-clicking a result row or clicking "Go to Directory".
     * SearchController relays this to the active FilePanel.
     *
     * @param dirPath Absolute path of the directory containing the result.
     */
    void navigateToDir(const QString &dirPath);

private:
    FileSearcher *_searcher;      ///< Injected search service — not owned.
    QLineEdit    *_patternInput;  ///< "Search for:" field.
    QLineEdit    *_pathInput;     ///< "Where:" root directory field.
    QListWidget  *_results;       ///< Live-populated list of matching paths.
    QLabel       *_statusLabel;   ///< "Found N file(s)." or progress text.
    QPushButton  *_goBtn;         ///< "Go to Directory" — enabled on selection.

    /**
     * @brief Clears the results list and calls @c _searcher->search().
     *
     * Results arrive asynchronously via the @c resultFound signal that was
     * connected in the constructor.
     */
    void doSearch();

    /**
     * @brief Emits @c navigateToDir with the double-clicked item's parent directory.
     * @param item The double-clicked QListWidgetItem.
     */
    void onResultDoubleClicked(QListWidgetItem *item);
};

#endif
