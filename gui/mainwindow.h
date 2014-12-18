#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sky.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateCenterStar();

private:
    Sky sky;
    int lastRA;
    int lastDec;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
