#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FullKeyboard.h"
#include "HanCharacter.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    FullKeyboard *fullKeyboard;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H