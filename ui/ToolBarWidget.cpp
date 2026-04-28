#include "ToolBarWidget.h"
#include "ToolTextButton.h"
#include <QMenu>

static QMenu *buildFilesMenu(QWidget *parent) {
    auto *m = new QMenu(parent);
    m->addAction("Change Drive (Left)...");
    m->addAction("Change Drive (Right)...");
    m->addSeparator();
    m->addAction("Rename / Move\tF6");
    m->addAction("Copy\tF5");
    m->addAction("Delete\tF8");
    m->addAction("Make Directory\tF7");
    m->addSeparator();
    m->addAction("Properties\tAlt+Enter");
    m->addSeparator();
    m->addAction("Quit\tAlt+F4");
    return m;
}

static QMenu *buildMarkMenu(QWidget *parent) {
    auto *m = new QMenu(parent);
    m->addAction("Select Group...\t+");
    m->addAction("Unselect Group...\t-");
    m->addSeparator();
    m->addAction("Select All\tCtrl++");
    m->addAction("Unselect All\tCtrl+-");
    m->addAction("Invert Selection\t*");
    m->addSeparator();
    m->addAction("Select by Extension");
    m->addAction("Restore Selection");
    return m;
}

static QMenu *buildCommandsMenu(QWidget *parent) {
    auto *m = new QMenu(parent);
    m->addAction("Find Files...\tAlt+F7");
    m->addSeparator();
    m->addAction("Compare Directories");
    m->addAction("Synchronize Directories");
    m->addSeparator();
    m->addAction("Pack Files...\tAlt+F5");
    m->addAction("Unpack Files...\tAlt+F9");
    m->addAction("Test Archives\tAlt+Shift+F9");
    m->addSeparator();
    m->addAction("Compare by Content");
    m->addAction("Open Command Prompt\tCtrl+P");
    return m;
}

static QMenu *buildNetMenu(QWidget *parent) {
    auto *m = new QMenu(parent);
    m->addAction("FTP Connect...\tF2");
    m->addAction("FTP New Connection...");
    m->addSeparator();
    m->addAction("Network Neighborhood");
    m->addAction("Disconnect Network Drive");
    return m;
}

static QMenu *buildShowMenu(QWidget *parent) {
    auto *m = new QMenu(parent);
    m->addAction("Brief (File Names Only)\tCtrl+F1");
    m->addAction("Full (All Details)\tCtrl+F2");
    m->addSeparator();
    m->addAction("Sort by Name\tCtrl+F3");
    m->addAction("Sort by Extension\tCtrl+F4");
    m->addAction("Sort by Size\tCtrl+F5");
    m->addAction("Sort by Date\tCtrl+F6");
    m->addSeparator();
    m->addAction("Show Hidden / System Files");
    m->addAction("Show Long Names");
    return m;
}

static QMenu *buildConfigMenu(QWidget *parent) {
    auto *m = new QMenu(parent);
    m->addAction("Options...\tCtrl+Shift+O");
    m->addAction("Button Bar...");
    m->addAction("Colors...");
    m->addSeparator();
    m->addAction("Save Settings Now");
    return m;
}

static QMenu *buildStartMenu(QWidget *parent) {
    auto *m = new QMenu(parent);
    m->addAction("User-defined commands...");
    return m;
}

static QMenu *buildHelpMenu(QWidget *parent) {
    auto *m = new QMenu(parent);
    m->addAction("Help Topics\tF1");
    m->addSeparator();
    m->addAction("Keyboard Shortcuts");
    m->addSeparator();
    m->addAction("About Total Commander");
    return m;
}

// -----------------------------------------------------------------------

ToolBarWidget::ToolBarWidget(QWidget *parent)
    : QWidget(parent),
      _layout(new QHBoxLayout(this)),
      _left(new QHBoxLayout()),
      _right(new QHBoxLayout())
{
    setObjectName("menuBar");
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);

    _left->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    _left->setSpacing(0);
    _right->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    _right->setSpacing(0);

    _layout->addLayout(_left);
    _layout->addStretch();
    _layout->addLayout(_right);

    auto addBtn = [&](QHBoxLayout *layout, const QString &label,
                      ToolTextButton::ButtonType type, QMenu *menu) {
        auto *btn = new ToolTextButton(label, type, this);
        btn->setMenu(menu);
        layout->addWidget(btn);
    };

    addBtn(_left,  "Files",         ToolTextButton::Files,         buildFilesMenu(this));
    addBtn(_left,  "Mark",          ToolTextButton::Mark,          buildMarkMenu(this));
    addBtn(_left,  "Commands",      ToolTextButton::Commands,      buildCommandsMenu(this));
    addBtn(_left,  "Net",           ToolTextButton::Net,           buildNetMenu(this));
    addBtn(_left,  "Show",          ToolTextButton::Show,          buildShowMenu(this));
    addBtn(_left,  "Configuration", ToolTextButton::Configuration, buildConfigMenu(this));
    addBtn(_left,  "Start",         ToolTextButton::Start,         buildStartMenu(this));
    addBtn(_right, "Help",          ToolTextButton::Help,          buildHelpMenu(this));
}
