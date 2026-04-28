#include "CenterBar.h"

CenterBar::CenterBar(QWidget *parent)
    : QWidget(parent),
      _layout(new QVBoxLayout(this))
{
    setObjectName("centerBar");
    _layout->setContentsMargins(5, 0, 5, 0);
    _layout->setSpacing(8);
    _layout->setAlignment(Qt::AlignCenter);

    auto *copyBtn    = makeButton("Copy");
    auto *compareBtn = makeButton("Compare");
    auto *searchBtn  = makeButton("Search");

    connect(copyBtn,    &QPushButton::clicked, this, [this]() { emit copyRequested();    });
    connect(compareBtn, &QPushButton::clicked, this, [this]() { emit compareRequested(); });
    connect(searchBtn,  &QPushButton::clicked, this, [this]() { emit searchRequested();  });
}

QPushButton *CenterBar::makeButton(const QString &label) {
    auto *btn = new QPushButton(label, this);
    btn->setObjectName("centerBarButton");
    _layout->addWidget(btn, 0, Qt::AlignHCenter);
    return btn;
}
