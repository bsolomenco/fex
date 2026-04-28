#include "FileSearcher.h"
#include <QDir>
#include <QDirIterator>
#include <QApplication>

FileSearcher::FileSearcher(QObject *parent) : QObject(parent) {}

void FileSearcher::search(const QString &root, const QString &pattern) {
    if (root.isEmpty() || pattern.isEmpty()) {
        emit finished(0);
        return;
    }

    const bool isGlob = pattern.contains('*') || pattern.contains('?');

    QDirIterator it(root, QDir::Files | QDir::NoDotAndDotDot,
                    QDirIterator::Subdirectories);
    int found = 0;
    while (it.hasNext()) {
        it.next();
        const QString name    = it.fileName();
        const bool    matched = isGlob
            ? QDir::match(pattern, name)
            : name.contains(pattern, Qt::CaseInsensitive);

        if (matched) {
            emit resultFound(it.filePath());
            ++found;
            if (found % 50 == 0)
                QApplication::processEvents();
        }
    }
    emit finished(found);
}
