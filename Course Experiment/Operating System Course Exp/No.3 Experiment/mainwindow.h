#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QCloseEvent>
#include <QLineEdit>
#include <QProgressBar>
#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "pthread.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>

#define GUI_ID "106"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool running;
    pthread_t mainThread;

    Ui::MainWindow *ui;

    QPushButton *start;
    QProgressBar *progress;
    QScrollArea *console;
    QTimer *timer;

    void closeThread();

public:
    QLabel *label;
    QLineEdit *source;
    QLineEdit *destination;
    QSharedMemory *sharedMem;
    int GUI_LOCK;

private slots:
    void update();
    void on_start_clicked();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
