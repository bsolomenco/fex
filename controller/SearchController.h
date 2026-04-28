/**
 * @file SearchController.h
 * @brief Wires a FileSearcher and a SearchDialog, relays navigation to MainWindow.
 *
 * Handles the Open/Closed concern for search: if the search implementation
 * ever changes (e.g. threaded, indexed), only this controller and
 * FileSearcher need updating — SearchDialog and MainWindow stay untouched.
 */

#pragma once
#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QString>

/**
 * @class SearchController
 * @brief Creates FileSearcher + SearchDialog and relays their signals.
 *
 * Each call to @c openSearch() spawns a new independent modeless dialog,
 * allowing several concurrent searches in different directories.
 *
 * The controller emits @c navigateRequested so MainWindow can forward it
 * to whichever FilePanel is currently active, without the controller
 * needing to know about panels at all (DIP satisfied).
 */
class SearchController : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs the controller.
     * @param parentWidget Parent widget for the SearchDialog window.
     * @param parent       Optional Qt object parent.
     */
    explicit SearchController(QWidget *parentWidget, QObject *parent = nullptr);

    /**
     * @brief Opens a modeless SearchDialog rooted at @p rootPath.
     *
     * Creates a new @c FileSearcher (owned by the dialog) and a new
     * @c SearchDialog. The dialog self-deletes on close.
     *
     * @param rootPath Initial "Where:" directory shown in the dialog.
     */
    void openSearch(const QString &rootPath);

signals:
    /**
     * @brief Emitted when the user double-clicks a result or clicks "Go to Directory".
     *
     * MainWindow connects this to the active FilePanel's @c navigateTo() slot.
     *
     * @param dirPath Absolute directory path to navigate to.
     */
    void navigateRequested(const QString &dirPath);

private:
    QWidget *_parentWidget; ///< Parent for spawned SearchDialog instances.
};

#endif
