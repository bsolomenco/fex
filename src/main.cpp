#include <QApplication>
#include "MainWindow.hpp"

//----------------------------------------------------------------
int main(int argc,char *argv[]){
    QApplication app(argc,argv);

    MainWindow window;
    window.setFixedSize(650, 400);    
    window.show();
    
    return app.exec();
}
