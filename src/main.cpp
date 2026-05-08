#include <QApplication>
#include "MainWindow.h"
#include <QFile>
#include <QTextStream>


//----------------------------------------------------------------
int main(int argc,char *argv[]){

    QApplication app(argc,argv);
    
    QFile file(":/style.qss"); 
    
    if (!file.exists()) {
        qDebug() << "EROARE: Fisierul nu exista la calea specificata!";
    }

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        
        
        app.setStyleSheet(styleSheet);
        
        file.close();
    }

    MainWindow window;
    
    window.show();
    return app.exec();
}
