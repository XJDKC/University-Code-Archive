#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QCloseEvent>
#include <QLineEdit>
#include <QLabel>
#include <sys/ipc.h>
#include <signal.h>


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

public:
    QLineEdit *dir;
    QLabel *label;
    QScrollArea *console;

    void endThread();

private slots:
    void on_start_clicked();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
