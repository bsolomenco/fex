#pragma once

#include <QApplication>
#include "MainWindow.h"
#include <QFile>
#include <QTextStream>
#include <QString>

class CustomApp : public QApplication
{
    Q_OBJECT
    public:
        CustomApp(int &argc, char **argv);
        ~CustomApp();

        static CustomApp* instance();
        void applyStyleSheet();
        void applyStyleSheet(const QString &path);
    
    private:
        void setupStyleWatcher();
        QString getStyleFilePath() const;
    private:
        QString _styleSheetPath();
        static CustomApp* _instance;

};