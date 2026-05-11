#include "CustomApp.h"
#include <QFileSystemWatcher>
#include <memory>


CustomApp* CustomApp::_instance = nullptr;

CustomApp::CustomApp(int &argc,char **argv): QApplication(argc, argv)
{
    if (_instance) {
            qFatal("Error: Only one instance of CustomApplication is allowed!");
    }
        _instance = this;

    applyStyleSheet();   
    setupStyleWatcher();
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

void CustomApp::applyStyleSheet(const QString &path)
{
    QString actualPath = path.isEmpty() ? ":/style.qss" : path;
    QFile file(actualPath); 
    
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        this->setStyleSheet(file.readAll());
        file.close();
        qDebug() << "StyleSheet aplicat din:" << actualPath;
    }
}
QString CustomApp::getStyleFilePath() const {
    QFile f(QString(SOURCE_DIR) + "/resources/style.qss");
    return f.exists() ? f.fileName() : ":/resources/style.qss";
}

void CustomApp::setupStyleWatcher() {
    QString path = getStyleFilePath();
    qDebug() << path;
    if (!path.isEmpty()) {
        auto *watcher = new QFileSystemWatcher({path}, this);
        
        QObject::connect(watcher, &QFileSystemWatcher::fileChanged, this, [this, watcher, path](const QString &) {
            this->applyStyleSheet(path);
            
            if (!watcher->files().contains(path)) {
                watcher->addPath(path);
            }
        });
        
        qDebug() << "Monitorizare activată pentru:" << path;
    }
}