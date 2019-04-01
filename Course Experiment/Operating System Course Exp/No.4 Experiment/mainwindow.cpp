#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OS_Exp4.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    running=false;

    label=new QLabel(this);
    start = this->findChild<QPushButton *>("start");
    dir=this->findChild<QLineEdit *>("dir");
    console=this->findChild<QScrollArea *>("console");
    console->viewport()->setBackgroundRole(QPalette::Light);
    console->viewport()->setAutoFillBackground(true);

    console->setWidget(label);
    label->setAlignment(Qt::AlignTop);
    label->setFont(QFont("YaHei Consolas Hybrid", 10, QFont::Thin));
    label->adjustSize();

    QObject::connect(start, SIGNAL(clicked()), this, SLOT(on_start_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    if (!running)
    {
        this->label->setText("");
        pthread_create(&mainThread,NULL,run,this);
        running=true;
    }
}

void MainWindow::endThread()
{
    running=false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (running)
    {
        void *ret;
        this->label->setText("");
        pthread_kill(mainThread,SIGKILL);
        pthread_join(mainThread,&ret);
        running=false;
    }
}
