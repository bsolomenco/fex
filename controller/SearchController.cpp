#include "SearchController.h"
#include "ui/SearchDialog.h"
#include "services/FileSearcher.h"

SearchController::SearchController(QWidget *parentWidget, QObject *parent)
    : QObject(parent), _parentWidget(parentWidget) {}

void SearchController::openSearch(const QString &rootPath) {
    auto *searcher = new FileSearcher();
    auto *dlg      = new SearchDialog(rootPath, searcher, _parentWidget);

    searcher->setParent(dlg); // tie lifetime to dialog — cleaned up on close

    dlg->setAttribute(Qt::WA_DeleteOnClose);
    connect(dlg, &SearchDialog::navigateToDir,
            this, &SearchController::navigateRequested);
    dlg->show();
}
