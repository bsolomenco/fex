#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMainWindow>


class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow()=default;

private:
    QVBoxLayout* _layout;
    QLabel* _label;


};
