/**
 * @file FileSearcher.h
 * @brief Recursive file-search service that streams results via Qt signals.
 *
 * Decoupled from any dialog or widget — callers connect to @c resultFound
 * and @c finished to receive results incrementally as the search runs.
 *
 * ### Pattern matching rules
 * - If the pattern contains @c * or @c ?, it is matched with @c QDir::match()
 *   (standard glob, case-insensitive).
 * - Otherwise a plain case-insensitive substring search is used.
 *
 * ### Threading
 * @c search() runs synchronously on the caller's thread.
 * @c QApplication::processEvents() is called every 50 results so the UI
 * remains responsive without requiring a background thread.
 */

#pragma once
#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <QObject>
#include <QString>

/**
 * @class FileSearcher
 * @brief Stateless search service with signal-based result delivery.
 *
 * Inject an instance into SearchDialog so the dialog stays decoupled
 * from the search algorithm. The same FileSearcher can theoretically
 * be replaced with a threaded version without changing SearchDialog.
 *
 * ### Usage
 * @code
 * auto *searcher = new FileSearcher(this);
 * connect(searcher, &FileSearcher::resultFound, list, &QListWidget::addItem);
 * connect(searcher, &FileSearcher::finished,    this, &MyDialog::onDone);
 * searcher->search("/home/user", "*.cpp");
 * @endcode
 */
class FileSearcher : public QObject {
    Q_OBJECT

public:
    /** @brief Constructs the searcher. @param parent Optional Qt parent. */
    explicit FileSearcher(QObject *parent = nullptr);

    /**
     * @brief Starts a synchronous recursive search.
     *
     * Emits @c resultFound for every match and @c finished when done.
     * Safe to call multiple times in sequence.
     *
     * @param root    Absolute directory to search recursively.
     * @param pattern Glob or plain substring to match against filenames.
     */
    void search(const QString &root, const QString &pattern);

signals:
    /**
     * @brief Emitted for each file whose name matches the pattern.
     * @param path Absolute path of the matching file.
     */
    void resultFound(const QString &path);

    /**
     * @brief Emitted once when the entire tree has been scanned.
     * @param totalFound Number of matching files found.
     */
    void finished(int totalFound);
};

#endif
