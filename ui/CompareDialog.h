/**
 * @file CompareDialog.h
 * @brief Pure-UI dialog that displays pre-computed directory comparison results.
 *
 * This class has no knowledge of the filesystem — it receives a
 * @c QList<CompareEntry> (produced by DirectoryComparator) and renders it
 * as a colour-coded table.  All business logic lives in the service layer.
 *
 * | Row colour | CompareEntry::Status |
 * |------------|----------------------|
 * | Amber      | LeftOnly             |
 * | Blue       | RightOnly            |
 * | Red        | Different            |
 * | Green      | Equal                |
 */

#pragma once
#ifndef COMPAREDIALOG_H
#define COMPAREDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QLabel>
#include <QList>
#include "services/DirectoryComparator.h"

/**
 * @class CompareDialog
 * @brief Read-only table dialog for directory comparison results.
 *
 * Opened by CompareController after DirectoryComparator has finished.
 * The dialog is modal and sets @c WA_DeleteOnClose.
 *
 * Table columns: Name | Status | Left Size | Right Size |
 *                Left Modified | Right Modified
 */
class CompareDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructs the dialog and immediately populates the table.
     *
     * @param leftPath  Left directory path — shown in the window title only.
     * @param rightPath Right directory path — shown in the window title only.
     * @param entries   Pre-computed comparison results from DirectoryComparator.
     * @param parent    Optional Qt parent widget.
     */
    explicit CompareDialog(const QString &leftPath,
                           const QString &rightPath,
                           const QList<CompareEntry> &entries,
                           QWidget *parent = nullptr);

    /** @brief Destructor. */
    ~CompareDialog() = default;

private:
    QTableWidget *_table;       ///< Table showing one row per CompareEntry.
    QLabel       *_statusLabel; ///< Summary: counts per status category.

    /**
     * @brief Populates @c _table from @p entries and updates @c _statusLabel.
     * @param entries The list produced by DirectoryComparator::compare().
     */
    void populate(const QList<CompareEntry> &entries);
};

#endif
