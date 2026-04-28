#include "FileOperations.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>

bool FileOperations::copyPath(const QString &src, const QString &dst) {
    QFileInfo fi(src);
    if (fi.isDir()) {
        if (!QDir().mkpath(dst)) return false;
        QDirIterator it(src, QDir::AllEntries | QDir::NoDotAndDotDot);
        while (it.hasNext()) {
            it.next();
            if (!copyPath(it.filePath(), dst + "/" + it.fileName()))
                return false;
        }
        return true;
    }
    return QFile::copy(src, dst);
}
