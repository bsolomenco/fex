#include "CommandBar.h"

CommandBar::CommandBar(QWidget *parent)
    : QWidget(parent),
      _layout(new QHBoxLayout(this)),
      _label(new QLabel(this)),
      _input(new QLineEdit(this))
{
    setObjectName("commandBar");
    _layout->setContentsMargins(4, 1, 4, 1);
    _layout->setSpacing(4);

    _label->setObjectName("commandLabel");
    _label->setText("~>");

    _input->setObjectName("commandInput");
    _input->setFrame(false);

    _layout->addWidget(_label);
    _layout->addWidget(_input, 1);

    connect(_input, &QLineEdit::returnPressed, this, [this]() {
        emit commandEntered(_input->text());
        _input->clear();
    });
}

void CommandBar::setPrompt(const QString &path) {
    _label->setText(path + ">");
}
