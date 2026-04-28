#include "ToolTextButton.h"

ToolTextButton::ToolTextButton(const QString &text, ButtonType type, QWidget *parent)
    : QPushButton(text, parent),
      m_type(type)
{
    setFlat(true);
    setCursor(Qt::PointingHandCursor);
}

ToolTextButton::ButtonType ToolTextButton::getType() const {
    return m_type;
}
