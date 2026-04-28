#include "FilePanel.h"
#include <QStorageInfo>
#include <QHeaderView>
#include <QDir>
#include <QKeyEvent>

FilePanel::FilePanel(QWidget *parent)
    : QWidget(parent),
      _layout(new QVBoxLayout(this)),
      _driveBar(new QWidget(this)),
      _pathLabel(new QLabel(this)),
      _view(new QTableView(this)),
      _model(new QFileSystemModel(this))
{
    setObjectName("filePanel");
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);

    _driveBar->setObjectName("panelDriveBar");
    buildDriveBar();

    _pathLabel->setObjectName("pathLabel");

    _layout->addWidget(_driveBar);
    _layout->addWidget(_pathLabel);
    _layout->addWidget(_view, 1);

    setupView();
    navigateTo(QDir::homePath());
}

void FilePanel::buildDriveBar() {
    auto *barLayout = new QHBoxLayout(_driveBar);
    barLayout->setContentsMargins(4, 2, 4, 2);
    barLayout->setSpacing(2);
    barLayout->setAlignment(Qt::AlignLeft);

    for (const QStorageInfo &vol : QStorageInfo::mountedVolumes()) {
        if (!vol.isValid() || !vol.isReady()) continue;
        QString root = vol.rootPath();
        auto *btn = new QPushButton(root, _driveBar);
        btn->setObjectName("driveButton");
        btn->setFixedHeight(20);
        connect(btn, &QPushButton::clicked, this, [this, root]() {
            navigateTo(root);
        });
        barLayout->addWidget(btn);
    }
    barLayout->addStretch();
}

void FilePanel::setupView() {
    _model->setRootPath("/");
    _model->setFilter(QDir::AllEntries | QDir::NoDot | QDir::Hidden);

    _view->setModel(_model);
    _view->setAlternatingRowColors(true);
    _view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _view->setSelectionBehavior(QAbstractItemView::SelectRows);
    _view->setSortingEnabled(true);
    _view->sortByColumn(0, Qt::AscendingOrder);
    _view->verticalHeader()->hide();
    _view->setShowGrid(false);
    _view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    _view->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    _view->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    _view->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    _view->setFocusPolicy(Qt::StrongFocus);

    connect(_view, &QTableView::doubleClicked, this, &FilePanel::onDoubleClicked);
    connect(_view, &QTableView::clicked, this, [this](const QModelIndex &) {
        emit activated(this);
    });
}

void FilePanel::navigateTo(const QString &path) {
    QModelIndex idx = _model->index(path);
    _view->setRootIndex(idx);
    _pathLabel->setText("  " + QDir::toNativeSeparators(path));
    emit pathChanged(path);
}

QString FilePanel::currentPath() const {
    return _model->filePath(_view->rootIndex());
}

QStringList FilePanel::selectedFiles() const {
    QStringList result;
    for (const QModelIndex &idx : _view->selectionModel()->selectedRows())
        result << _model->filePath(idx);
    return result;
}

void FilePanel::refresh() {
    navigateTo(currentPath());
}

void FilePanel::onDoubleClicked(const QModelIndex &index) {
    if (_model->isDir(index)) {
        navigateTo(_model->filePath(index));
    }
}
