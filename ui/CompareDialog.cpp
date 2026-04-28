#include "CompareDialog.h"
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

static QString fmtSize(const QFileInfo &fi) {
    if (!fi.exists()) return {};
    const qint64 b = fi.size();
    if (b < 1024)   return QString("%1 B").arg(b);
    if (b < 1 << 20) return QString("%1 KB").arg(b / 1024);
    return QString("%1 MB").arg(b / (1 << 20));
}

static QString fmtDate(const QFileInfo &fi) {
    return fi.exists() ? fi.lastModified().toString("yyyy-MM-dd hh:mm") : QString();
}

CompareDialog::CompareDialog(const QString &leftPath,
                             const QString &rightPath,
                             const QList<CompareEntry> &entries,
                             QWidget *parent)
    : QDialog(parent),
      _table(new QTableWidget(this)),
      _statusLabel(new QLabel(this))
{
    setWindowTitle(QString("Compare:  %1  ↔  %2").arg(leftPath, rightPath));
    resize(900, 500);

    _table->setColumnCount(6);
    _table->setHorizontalHeaderLabels(
        {"Name", "Status", "Left Size", "Right Size", "Left Modified", "Right Modified"});
    _table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    _table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _table->setSelectionBehavior(QAbstractItemView::SelectRows);
    _table->setAlternatingRowColors(true);
    _table->verticalHeader()->hide();
    _table->setSortingEnabled(true);

    auto *closeBtn = new QPushButton("Close", this);
    closeBtn->setDefault(true);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);

    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch();
    btnRow->addWidget(closeBtn);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(_table, 1);
    layout->addWidget(_statusLabel);
    layout->addLayout(btnRow);

    populate(entries);
}

void CompareDialog::populate(const QList<CompareEntry> &entries) {
    // Background colours (dark-theme aware)
    static const QColor kAmber (0x45, 0x3a, 0x00); // left only
    static const QColor kBlue  (0x1a, 0x2a, 0x40); // right only
    static const QColor kRed   (0x40, 0x1a, 0x1a); // different
    static const QColor kGreen (0x1a, 0x33, 0x1a); // equal

    static const QMap<CompareEntry::Status, QPair<QString, QColor>> kMeta = {
        {CompareEntry::LeftOnly,  {"Left only",  kAmber}},
        {CompareEntry::RightOnly, {"Right only", kBlue }},
        {CompareEntry::Different, {"Different",  kRed  }},
        {CompareEntry::Equal,     {"Equal",      kGreen}},
    };

    _table->setRowCount(entries.size());
    int leftOnly = 0, rightOnly = 0, diff = 0, equal = 0;

    for (int row = 0; row < entries.size(); ++row) {
        const CompareEntry &e = entries[row];
        const auto &[label, bg] = kMeta[e.status];

        auto cell = [&](int col, const QString &text) {
            auto *item = new QTableWidgetItem(text);
            item->setBackground(bg);
            _table->setItem(row, col, item);
        };

        cell(0, e.name);
        cell(1, label);
        cell(2, fmtSize(e.left));
        cell(3, fmtSize(e.right));
        cell(4, fmtDate(e.left));
        cell(5, fmtDate(e.right));

        switch (e.status) {
            case CompareEntry::LeftOnly:  ++leftOnly;  break;
            case CompareEntry::RightOnly: ++rightOnly; break;
            case CompareEntry::Different: ++diff;      break;
            case CompareEntry::Equal:     ++equal;     break;
        }
    }

    _statusLabel->setText(
        QString("Left only: %1   Right only: %2   Different: %3   Equal: %4   Total: %5")
            .arg(leftOnly).arg(rightOnly).arg(diff).arg(equal).arg(entries.size()));
}
