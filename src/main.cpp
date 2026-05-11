#include "App.hpp"
#include "MainWindow.hpp"

//----------------------------------------------------------------
int main(int argc,char *argv[]){
    App app(argc, argv);

    MainWindow window;
    window.resize(650, 400);
    window.show();

    return app.exec();
}
