#include "FunctionBar.h"

static const struct { int key; const char *label; } kFunctionKeys[] = {
    {1,  "Help"},   {2, "UserMenu"}, {3, "View"},   {4, "Edit"},
    {5,  "Copy"},   {6, "Move"},     {7, "MkDir"},  {8, "Delete"},
    {9,  "PullDn"}, {10, "Quit"}
};

FunctionBar::FunctionBar(QWidget *parent)
    : QWidget(parent),
      _layout(new QHBoxLayout(this))
{
    setObjectName("functionBar");
    _layout->setContentsMargins(0, 1, 0, 1);
    _layout->setSpacing(1);

    for (const auto &fk : kFunctionKeys) {
        addButton(fk.key, fk.label);
    }
}

void FunctionBar::addButton(int fKey, const QString &label) {
    auto *btn = new QPushButton(QString("F%1 %2").arg(fKey).arg(label), this);
    btn->setObjectName("functionButton");
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(btn, &QPushButton::clicked, this, [this, fKey]() {
        emit functionKeyPressed(fKey);
    });
    _layout->addWidget(btn);
}
