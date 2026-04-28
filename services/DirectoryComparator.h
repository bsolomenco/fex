/**
 * @file DirectoryComparator.h
 * @brief Data types and algorithm for comparing two directory listings.
 *
 * Completely decoupled from any UI — returns a plain list of CompareEntry
 * structs that a dialog or any other consumer can display however it likes.
 */

#pragma once
#ifndef DIRECTORYCOMPARATOR_H
#define DIRECTORYCOMPARATOR_H

#include <QString>
#include <QList>
#include <QFileInfo>

/**
 * @struct CompareEntry
 * @brief Represents one entry (file or directory) found in either or both directories.
 */
struct CompareEntry {

    /** @brief Relationship of this entry between the two directories. */
    enum Status {
        LeftOnly,  ///< Exists only in the left directory.
        RightOnly, ///< Exists only in the right directory.
        Different, ///< Exists in both but differs in size or modification time.
        Equal      ///< Exists in both and is byte-for-byte identical in metadata.
    };

    QString   name;   ///< Filename (without directory prefix).
    Status    status; ///< Comparison outcome.
    QFileInfo left;   ///< Metadata from the left side (invalid when RightOnly).
    QFileInfo right;  ///< Metadata from the right side (invalid when LeftOnly).
};

/**
 * @class DirectoryComparator
 * @brief Stateless service that compares two directories by filename, size, and mtime.
 *
 * The comparison is non-recursive (top-level entries only) and is based
 * purely on @c QFileInfo metadata — no file content is read.
 *
 * ### Usage
 * @code
 * DirectoryComparator cmp;
 * QList<CompareEntry> results = cmp.compare("/home/user/left", "/home/user/right");
 * @endcode
 */
class DirectoryComparator {
public:
    /**
     * @brief Compares two directories and returns one entry per unique filename.
     *
     * The result list is sorted by filename (map iteration order).
     * Hidden files and system entries are included; @c . and @c .. are excluded.
     *
     * @param leftPath  Absolute path of the left directory.
     * @param rightPath Absolute path of the right directory.
     * @return List of CompareEntry values, one per unique filename found in either side.
     */
    QList<CompareEntry> compare(const QString &leftPath,
                                const QString &rightPath) const;
};

#endif
