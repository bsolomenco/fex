#include "CustomApp.h"

//----------------------------------------------------------------
int main(int argc,char *argv[]){

    CustomApp app(argc,argv);
    
    

    MainWindow window;
    
    window.show();
    return app.exec();
}
