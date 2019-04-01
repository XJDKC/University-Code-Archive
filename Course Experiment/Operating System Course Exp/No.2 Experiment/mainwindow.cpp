#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OS_Exp2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    running=false;

    console=this->findChild<QScrollArea *>("console");
    console->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    console->viewport()->setBackgroundRole(QPalette::Light);
    console->viewport()->setAutoFillBackground(true);

    label = new QLabel(this);
    console->setWidget(label);
    label->setMinimumSize(20000, 20000);
    label->setAlignment(Qt::AlignTop);

    start = this->findChild<QPushButton *>("start");
    close = this->findChild<QPushButton *>("close");

    QObject::connect(start, SIGNAL(clicked()), this, SLOT(on_start_clicked()));
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(on_close_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    if (!running)
    {
        pthread_create(&mainThread,NULL,run,this);
        running=true;
    }
}

void MainWindow::on_close_clicked()
{
    if (running)
    {
        void *ret;
        this->label->setText("");
        pthread_join(mainThread,&ret);
        running=false;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    on_close_clicked();
}
