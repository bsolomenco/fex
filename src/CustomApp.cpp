#include "CustomApp.h"

CustomApp* CustomApp::_instance = nullptr;

CustomApp::CustomApp(int &argc,char **argv): QApplication(argc, argv)
{
    if (_instance) {
            qFatal("Error: Only one instance of CustomApplication is allowed!");
    }
        _instance = this;

    applyStyleSheet();   
}

CustomApp::~CustomApp() {}
void CustomApp::applyStyleSheet()
{

    QFile file(":/style.qss"); 
    
    if (!file.exists()) {
        qDebug() << "EROARE: Fisierul nu exista la calea specificata!";
    }

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        
        
        this->setStyleSheet(styleSheet);
        
        file.close();
    }

}