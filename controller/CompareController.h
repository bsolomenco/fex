/**
 * @file CompareController.h
 * @brief Orchestrates directory comparison: runs the service, opens the dialog.
 *
 * Separates *when* and *how* to compare (controller responsibility) from
 * *what* the comparison algorithm does (DirectoryComparator) and *how*
 * results are displayed (CompareDialog).
 */

#pragma once
#ifndef COMPARECONTROLLER_H
#define COMPARECONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QString>
#include "services/DirectoryComparator.h"

/**
 * @class CompareController
 * @brief Mediates between the UI compare request and the DirectoryComparator service.
 *
 * Owns a @c DirectoryComparator instance. On @c compare(), it:
 *  1. Delegates computation to the comparator.
 *  2. Opens a CompareDialog pre-populated with the results.
 *
 * MainWindow creates one instance and calls @c compare() when the
 * CenterBar emits @c compareRequested.
 */
class CompareController : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs the controller.
     * @param parentWidget Parent widget for the CompareDialog.
     * @param parent       Optional Qt object parent.
     */
    explicit CompareController(QWidget *parentWidget, QObject *parent = nullptr);

    /**
     * @brief Runs a comparison and presents results in a CompareDialog.
     *
     * The dialog is modal and self-deletes on close (@c WA_DeleteOnClose).
     *
     * @param leftPath  Current directory of the left panel.
     * @param rightPath Current directory of the right panel.
     */
    void compare(const QString &leftPath, const QString &rightPath);

private:
    QWidget             *_parentWidget; ///< Parent for the CompareDialog.
    DirectoryComparator  _comparator;   ///< Stateless comparison service.
};

#endif
