#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QCloseEvent>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QTimer>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

using namespace std;

void forking(int &type);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int type);
    ~MainWindow();

    int tag;
    QPushButton *start;
    QLabel *label;
    QScrollArea *console;
    QTimer *timer;

private:
    Ui::MainWindow *ui;

    int count;
    ifstream inFile;

private slots:
    void update();
    void on_start_clicked();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
