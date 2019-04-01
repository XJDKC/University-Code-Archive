#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QCloseEvent>
#include <QLabel>
#include "pthread.h"


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
    pthread_t mainThread;
    bool running;

    Ui::MainWindow *ui;

    QPushButton *start;
    QPushButton *close;
    QScrollArea *console;

public:
    QLabel *label;

private slots:
    void on_start_clicked();
    void on_close_clicked();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H