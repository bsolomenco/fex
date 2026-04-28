/**
 * @file FileOperationController.h
 * @brief Orchestrates copy operations between the UI layer and FileOperations service.
 *
 * Owns all user-facing copy flow:
 *  - confirmation dialog ("Copy N items to …?")
 *  - conflict detection and overwrite prompt
 *  - modal progress dialog
 *  - delegation of actual I/O to @c FileOperations::copyPath()
 *
 * MainWindow creates one instance and connects @c copyCompleted to the
 * destination panel's @c refresh() slot.
 */

#pragma once
#ifndef FILEOPERATIONCONTROLLER_H
#define FILEOPERATIONCONTROLLER_H

#include <QObject>
#include <QStringList>
#include <QWidget>

/**
 * @class FileOperationController
 * @brief Mediates between UI copy requests and the FileOperations service.
 *
 * Depends only on @c QWidget* (for dialog parenting) and the stateless
 * @c FileOperations namespace — it never touches FilePanel directly.
 */
class FileOperationController : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs the controller.
     * @param parentWidget Widget used as the parent for confirmation and
     *                     progress dialogs, ensuring correct modality.
     * @param parent       Optional Qt object parent.
     */
    explicit FileOperationController(QWidget *parentWidget,
                                     QObject *parent = nullptr);

    /**
     * @brief Initiates a confirmed, progress-tracked copy operation.
     *
     * Shows a confirmation dialog, checks for destination conflicts (with
     * an overwrite prompt), then copies each item using
     * @c FileOperations::copyPath(). Emits @c copyCompleted when done.
     *
     * @param sources     Absolute paths of the files/directories to copy.
     * @param destination Absolute path of the target directory.
     */
    void copy(const QStringList &sources, const QString &destination);

signals:
    /**
     * @brief Emitted after the copy finishes (or is cancelled partway through).
     * @param destination The directory that was written to; use this to
     *                    refresh the destination FilePanel.
     */
    void copyCompleted(const QString &destination);

private:
    QWidget *_parentWidget; ///< Parent for modal QMessageBox / QProgressDialog.
};

#endif
