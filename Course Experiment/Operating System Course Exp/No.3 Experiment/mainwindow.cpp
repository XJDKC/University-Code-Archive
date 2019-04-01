#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OS_Exp3.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    sharedMem(new QSharedMemory(GUI_ID)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    running=false;
    GUI_LOCK=semget(ftok(".",0),2,IPC_CREAT|0666);
    semctl(GUI_LOCK, 0, SETVAL, 1);
    semctl(GUI_LOCK, 1, SETVAL, 0);

    if (sharedMem->isAttached())
        sharedMem->detach();
    if (sharedMem->create(101))
    {
        char *data=static_cast<char *>(sharedMem->data());
        data[0]=0;data[1]=0;
    }
    else {
        qDebug() << "fail to create sharedmem!" << endl;
        exit(0);
    }


    console=this->findChild<QScrollArea *>("console");
    console->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    console->viewport()->setBackgroundRole(QPalette::Light);
    console->viewport()->setAutoFillBackground(true);

    label = new QLabel(this);
    console->setWidget(label);
    label->setMinimumSize(20000, 20000);
    label->setAlignment(Qt::AlignTop);

    timer=new QTimer(this);
    timer->start(1);

    source=this->findChild<QLineEdit *>("source");
    destination=this->findChild<QLineEdit *>("destination");
    progress=this->findChild<QProgressBar *>("progress");
    start = this->findChild<QPushButton *>("start");

    progress->setMinimum(0);
    progress->setMaximum(100);
    progress->setValue(0);

    QObject::connect(start, SIGNAL(clicked()), this, SLOT(on_start_clicked()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    if (!running)
    {
        qDebug()<<"creating";
        static_cast<char *>(sharedMem->data())[0]=0;
        this->label->setText("");
        pthread_create(&mainThread,NULL,run,(void *)this);
        running=true;
    }
}

void MainWindow::closeThread()
{
    if (running)
    {
        usleep(100);
        qDebug()<<"killing!";
        pthread_kill(mainThread,SIGINT);
        running=false;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    closeThread();
    sharedMem->detach();
    semctl(GUI_LOCK,0,IPC_RMID,0);
}

void MainWindow::update()
{
    char *data=static_cast<char *>(sharedMem->data());
    progress->setValue(data[0]);
    if (data[0]==100||data[0]==-1)
        closeThread();
    if (data[1]!='\0')
    {
        P(GUI_LOCK,1);
        QString text=label->text();
        QString newtext(data+1);
        text+=newtext+'\n';
        label->setText(text);
        data[1]='\0';
        V(GUI_LOCK,0);
    }
}
