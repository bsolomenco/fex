/**
 * @file FileOperations.h
 * @brief Pure filesystem utility functions — no UI, no Qt widgets.
 *
 * All functions operate on plain paths and return a success flag.
 * They can be called from any thread or test without a QApplication.
 */

#pragma once
#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QString>

/**
 * @namespace FileOperations
 * @brief Stateless filesystem helpers used by FileOperationController.
 */
namespace FileOperations {

/**
 * @brief Copies @p src to @p dst, handling both files and directory trees.
 *
 * For directories the copy is recursive: the directory is created at @p dst
 * and all its children are copied preserving the relative structure.
 * Existing files at the destination are NOT removed here — the caller is
 * responsible for conflict resolution before invoking this function.
 *
 * @param src Absolute path of the source file or directory.
 * @param dst Absolute path of the desired destination.
 * @return @c true on full success; @c false if any individual operation failed.
 */
bool copyPath(const QString &src, const QString &dst);

} // namespace FileOperations

#endif
