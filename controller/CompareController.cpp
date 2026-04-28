#include "CompareController.h"
#include "ui/CompareDialog.h"

CompareController::CompareController(QWidget *parentWidget, QObject *parent)
    : QObject(parent), _parentWidget(parentWidget) {}

void CompareController::compare(const QString &leftPath, const QString &rightPath) {
    const QList<CompareEntry> entries = _comparator.compare(leftPath, rightPath);

    auto *dlg = new CompareDialog(leftPath, rightPath, entries, _parentWidget);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();
}
