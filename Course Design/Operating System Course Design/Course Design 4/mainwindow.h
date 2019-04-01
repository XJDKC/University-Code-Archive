#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QString>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include "statinfo.h"


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
     bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    sysStatInfo *allInfo;

    void show_index_0();
    void show_index_1_0();
    void show_index_1_1();
    void show_index_2();
    void show_index_3();
    void show_index_tabWidget(int index);
    void drawCPUUse();
    void drawRAMUse();

private slots:
    void refresh();
    void on_tabWidget_currentChanged(int index);
};




#endif // MAINWINDOW_H
