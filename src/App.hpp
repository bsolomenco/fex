#pragma once
#include <QApplication>

class App : public QApplication {
public:
    App(int &argc, char **argv);
};