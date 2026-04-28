#include "DirectoryComparator.h"
#include <QDir>
#include <QMap>

QList<CompareEntry> DirectoryComparator::compare(const QString &leftPath,
                                                  const QString &rightPath) const {
    struct Pair { QFileInfo left; QFileInfo right; };
    QMap<QString, Pair> map;

    const auto flags = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden;
    for (const QFileInfo &fi : QDir(leftPath).entryInfoList(flags))
        map[fi.fileName()].left = fi;
    for (const QFileInfo &fi : QDir(rightPath).entryInfoList(flags))
        map[fi.fileName()].right = fi;

    QList<CompareEntry> result;
    result.reserve(map.size());

    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        CompareEntry e;
        e.name  = it.key();
        e.left  = it.value().left;
        e.right = it.value().right;

        if      (!e.left.exists())  e.status = CompareEntry::RightOnly;
        else if (!e.right.exists()) e.status = CompareEntry::LeftOnly;
        else if (e.left.size() != e.right.size() ||
                 e.left.lastModified() != e.right.lastModified())
                                    e.status = CompareEntry::Different;
        else                        e.status = CompareEntry::Equal;

        result.append(e);
    }
    return result;
}
