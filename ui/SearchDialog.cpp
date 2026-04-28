#include "SearchDialog.h"
#include "services/FileSearcher.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileInfo>

SearchDialog::SearchDialog(const QString &searchPath,
                           FileSearcher  *searcher,
                           QWidget       *parent)
    : QDialog(parent),
      _searcher(searcher),
      _patternInput(new QLineEdit(this)),
      _pathInput(new QLineEdit(searchPath, this)),
      _results(new QListWidget(this)),
      _statusLabel(new QLabel("Enter a pattern and press Search.", this)),
      _goBtn(new QPushButton("Go to Directory", this))
{
    setWindowTitle("Search Files");
    resize(680, 480);

    _patternInput->setPlaceholderText("*.cpp  or  main  (supports * and ? wildcards)");
    _goBtn->setEnabled(false);

    auto *searchBtn = new QPushButton("Search", this);
    searchBtn->setDefault(true);
    auto *closeBtn = new QPushButton("Close", this);

    auto *grid = new QGridLayout();
    grid->addWidget(new QLabel("Search for:", this), 0, 0);
    grid->addWidget(_patternInput, 0, 1);
    grid->addWidget(new QLabel("Where:", this), 1, 0);
    grid->addWidget(_pathInput, 1, 1);

    auto *btnRow = new QHBoxLayout();
    btnRow->addWidget(searchBtn);
    btnRow->addWidget(_goBtn);
    btnRow->addStretch();
    btnRow->addWidget(closeBtn);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(grid);
    layout->addWidget(_results, 1);
    layout->addWidget(_statusLabel);
    layout->addLayout(btnRow);

    // Wire searcher signals → UI updates
    connect(_searcher, &FileSearcher::resultFound, this, [this](const QString &path) {
        _results->addItem(path);
    });
    connect(_searcher, &FileSearcher::finished, this, [this](int count) {
        _statusLabel->setText(count > 0
            ? QString("Found %1 file(s).").arg(count)
            : "No files found.");
    });

    connect(searchBtn,     &QPushButton::clicked,      this, &SearchDialog::doSearch);
    connect(_patternInput, &QLineEdit::returnPressed,  this, &SearchDialog::doSearch);
    connect(closeBtn,      &QPushButton::clicked,      this, &QDialog::reject);
    connect(_goBtn,        &QPushButton::clicked,      this, [this]() {
        if (auto *item = _results->currentItem())
            emit navigateToDir(QFileInfo(item->text()).absolutePath());
    });
    connect(_results, &QListWidget::itemDoubleClicked,
            this, &SearchDialog::onResultDoubleClicked);
    connect(_results, &QListWidget::currentItemChanged, this,
            [this](QListWidgetItem *cur) { _goBtn->setEnabled(cur != nullptr); });
}

void SearchDialog::doSearch() {
    _results->clear();
    _statusLabel->setText("Searching…");
    _searcher->search(_pathInput->text().trimmed(),
                      _patternInput->text().trimmed());
}

void SearchDialog::onResultDoubleClicked(QListWidgetItem *item) {
    if (item)
        emit navigateToDir(QFileInfo(item->text()).absolutePath());
}
