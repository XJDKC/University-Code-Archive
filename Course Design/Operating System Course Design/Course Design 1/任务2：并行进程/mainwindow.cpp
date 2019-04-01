#include "mainwindow.h"
#include "ui_mainwindow.h"

extern pid_t p1,p2,p3;

MainWindow::MainWindow(int type) :
    QMainWindow(nullptr)
{
    ui=new Ui::MainWindow;
    ui->setupUi(this);

    this->label=new QLabel(this);
    this->start=new QPushButton(this);
    this->timer=new QTimer(this);
    this->timer->start(1000);
    QObject::connect(start, SIGNAL(clicked()), this, SLOT(on_start_clicked()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    QFont tmp;
    tag=type;

    switch(type)
    {
        case 0: this->setWindowTitle("Concurrent");
                this->setGeometry(900,800,200,80);
                this->start->setGeometry(50,20,100,40);
                this->start->setText("Close");
                break;
        case 1: this->setWindowTitle("Time");
                this->setGeometry(300,400,400,300);
                this->start->hide();
                this->label->setGeometry(50,100,300,100);
                this->label->setAlignment(Qt::AlignCenter);
                this->label->setText("----年--月--日 --:--:--");
                tmp.setPointSize(15);
                this->label->setFont(tmp);
                break;
        case 2: this->setWindowTitle("Text");
                this->setGeometry(800,400,400,300);
                this->start->hide();
                console=new QScrollArea(this);
                //console->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                console->viewport()->setBackgroundRole(QPalette::Light);
                console->viewport()->setAutoFillBackground(true);
                console->setWidget(label);
                console->setGeometry(0,0,400,300);
                label->setMinimumSize(20000, 20000);
                label->setAlignment(Qt::AlignTop);
                inFile.open("/etc/fstab");
                if (inFile.is_open())
                {
                    label->setText("打开成功!\n");
                }
                break;
        case 3: this->setWindowTitle("Number");
                this->setGeometry(1300,400,400,300);
                this->start->hide();
                this->label->setGeometry(50,0,300,300);
                this->label->setAlignment(Qt::AlignCenter);
                this->label->setText("0");
                tmp.setPointSize(20);
                this->label->setFont(tmp);
                count=0;
                break;
    }
}

void MainWindow::on_start_clicked()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int status;
    if (p1&&p2&&p3)
    {
        kill(p1,SIGINT);
        kill(p2,SIGINT);
        kill(p3,SIGINT);
        waitpid(p1,&status,0);
        waitpid(p2,&status,0);
        waitpid(p3,&status,0);
    }
}

void MainWindow::update()
{
    QString qtmp("");
    string tmp("");
    stringstream ss;
    time_t t;
    struct tm * lt;
    bool ok;

    switch(tag)
    {
        case 0: break;
        case 1: time (&t);
                lt = localtime (&t);//----年--月--日 --:--:-- from 1900
                ss<<setfill('0')<<1900+lt->tm_year<<"年"<<setw(2)<<lt->tm_mon+1<<"月"<<setw(2)<<lt->tm_mday<<"日 "
                  <<setw(2)<<lt->tm_hour<<":"<<setw(2)<<lt->tm_min<<":"<<setw(2)<<lt->tm_sec;
                qtmp=QString::fromStdString(ss.str());
                this->label->setText(qtmp);
                break;
        case 2: getline(inFile,tmp);
                qtmp=this->label->text()+QString::fromStdString(tmp)+'\n';
                this->label->setText(qtmp);
                break;
        case 3: count=count+1;
                this->label->setText(QString::number(count+this->label->text().toInt()));
                break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
