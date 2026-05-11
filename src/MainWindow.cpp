#include "MainWindow.hpp"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow()
    : QMainWindow(nullptr)
{
    QWidget* centralWidget = new QWidget(this);

    QLabel* label = new QLabel("Hello World!");
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(label);

    setCentralWidget(centralWidget);
}
