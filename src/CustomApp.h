#pragma once

#include <QApplication>
#include "MainWindow.h"
#include <QFile>
#include <QTextStream>

class CustomApp : public QApplication
{
    Q_OBJECT
    public:
        CustomApp(int &argc, char **argv);
        ~CustomApp();

        static CustomApp* instance();
        void applyStyleSheet();
    
    private:
        QString _styleSheetPath();
        static CustomApp* _instance;

};