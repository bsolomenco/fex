#include "MainWindow.h"

//----------------------------------------------------------------
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)    
{    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    _label = new QLabel("Hello World!");
    _layout = new QVBoxLayout(centralWidget);
    
    _label->setAlignment(Qt::AlignCenter);
    setFixedSize(650, 400);
    
    _layout->addWidget(_label);

}

