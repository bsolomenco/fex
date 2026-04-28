#include "FileOperationController.h"
#include "services/FileOperations.h"
#include <QMessageBox>
#include <QProgressDialog>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QApplication>

FileOperationController::FileOperationController(QWidget *parentWidget, QObject *parent)
    : QObject(parent), _parentWidget(parentWidget) {}

void FileOperationController::copy(const QStringList &sources,
                                   const QString &destination) {
    if (sources.isEmpty()) {
        QMessageBox::information(_parentWidget, "Copy",
            "No files selected.\nSelect files first, then press Copy.");
        return;
    }

    const auto reply = QMessageBox::question(_parentWidget, "Copy",
        QString("Copy %1 item(s) to:\n%2").arg(sources.size()).arg(destination),
        QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    QStringList conflicts;
    for (const QString &src : sources) {
        if (QFileInfo::exists(destination + "/" + QFileInfo(src).fileName()))
            conflicts << QFileInfo(src).fileName();
    }
    if (!conflicts.isEmpty()) {
        const auto r = QMessageBox::question(_parentWidget, "Overwrite?",
            QString("%1 file(s) already exist in the destination. Overwrite all?")
                .arg(conflicts.size()),
            QMessageBox::Yes | QMessageBox::No);
        if (r != QMessageBox::Yes) return;
    }

    QProgressDialog progress("Copying…", "Cancel", 0, sources.size(), _parentWidget);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(0);

    int i = 0;
    for (const QString &src : sources) {
        if (progress.wasCanceled()) break;
        const QString name   = QFileInfo(src).fileName();
        const QString target = destination + "/" + name;
        progress.setLabelText(name);
        progress.setValue(i++);
        QApplication::processEvents();

        if (QFileInfo::exists(target)) {
            if (QFileInfo(target).isDir()) QDir(target).removeRecursively();
            else                           QFile::remove(target);
        }
        FileOperations::copyPath(src, target);
    }
    progress.setValue(sources.size());

    emit copyCompleted(destination);
}
