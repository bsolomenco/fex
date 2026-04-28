/**
 * @file main.cpp
 * @brief Application entry point.
 *
 * Responsibilities:
 *  1. Create the QApplication instance.
 *  2. Load and apply @c style.qss (with live-reload during development).
 *  3. Construct and show MainWindow.
 *
 * ### Stylesheet loading strategy
 * The CMake build injects the macro @c SOURCE_DIR pointing to the project
 * source root.  At startup the app tries to open @c SOURCE_DIR/style.qss
 * directly from the filesystem.  If it exists, a QFileSystemWatcher is
 * set up so that every time the file is saved the stylesheet is re-applied
 * without restarting the application — useful while tweaking colours.
 *
 * If the source file is not present (e.g. in a distributed build), the
 * embedded Qt resource @c :/style.qss is used instead.
 *
 * @note Some editors (VS Code, Kate) save files by deleting and recreating
 *       them, which causes the OS to remove the inotify watch.  The watcher
 *       callback re-adds the path after each change event to handle this.
 */

#include <QApplication>
#include <QFile>
#include <QFileSystemWatcher>
#include "mainwindow.h"

/**
 * @brief Returns the path to @c style.qss that should be loaded.
 *
 * Prefers the on-disk source file for live editing; falls back to the
 * embedded resource @c :/style.qss when the source tree is unavailable.
 *
 * @return Absolute filesystem path, or @c ":/style.qss" for the resource.
 */
static QString styleFilePath() {
    QFile f(QString(SOURCE_DIR) + "/style.qss");
    return f.exists() ? f.fileName() : ":/style.qss";
}

/**
 * @brief Reads @c style.qss and applies it to the application.
 *
 * Safe to call multiple times — each call fully replaces the previous
 * stylesheet.
 *
 * @param app The running QApplication instance.
 */
static void applyStyleSheet(QApplication &app) {
    QFile f(styleFilePath());
    if (f.open(QFile::ReadOnly)) {
        app.setStyleSheet(f.readAll());
        f.close();
    }
}

/**
 * @brief Application entry point.
 * @param argc Argument count passed by the OS.
 * @param argv Argument vector passed by the OS.
 * @return Exit code returned to the OS (0 on clean exit).
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    applyStyleSheet(a);

    QString path = styleFilePath();
    if (!path.startsWith(":/")) {
        auto *watcher = new QFileSystemWatcher({path}, &a);
        QObject::connect(watcher, &QFileSystemWatcher::fileChanged,
                         &a, [&a, watcher, path](const QString &) {
            applyStyleSheet(a);
            // Re-add the path if the editor replaced the file (delete + create).
            if (!watcher->files().contains(path))
                watcher->addPath(path);
        });
    }

    MainWindow w;
    w.show();

    return a.exec();
}
