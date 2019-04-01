#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cpuUse->installEventFilter(this);
    ui->ramUse->installEventFilter(this);
    timer=new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    QObject::connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(on_tabWidget_currentChanged(int)));
    timer->start(1000);

    allInfo = new sysStatInfo();
    allInfo->getSysStatInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete allInfo;
}

void MainWindow::refresh()
{
    int index=ui->tabWidget->currentIndex();

    allInfo->updateSysStatInfo();
    show_index_tabWidget(index);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    show_index_tabWidget(index);
    return ;
}


void MainWindow::show_index_tabWidget(int index)
{
    int tab2Index=ui->resources->currentIndex();
    switch(index)
    {
        case 0:show_index_0();break;
        case 1:if (tab2Index==0)
                show_index_1_0();
               else
                show_index_1_1();
               break;
        case 2:show_index_2();break;
        case 3:show_index_3();break;
    }
}

void MainWindow::show_index_0()
{
    QTableWidgetItem *item;
    int no;
    double cpu=0;
    int secs=allInfo->cpuInfo.totalCPUTime.size();
    int rowNum=ui->processTable->rowCount();
    int processNum=allInfo->processInfo.size();

    ui->processTable->setSortingEnabled(false);

    for (int i=0;i<ui->processTable->rowCount();i++)
    {
        no=allInfo->findProcess(ui->processTable->item(i,0)->text().toInt());
        if (no>=0)
        {
            cpu=0;
            if (secs>=2)
            {
                cpu=allInfo->processInfo[no].totalProcessCPUTime[1]-allInfo->processInfo[no].totalProcessCPUTime[0];
                cpu=cpu/(allInfo->cpuInfo.totalCPUTime[secs-1]-allInfo->cpuInfo.totalCPUTime[secs-2])*100;
            }
            ui->processTable->item(i,1)->setText(QString::fromStdString(allInfo->processInfo[no].name));
            ui->processTable->item(i,2)->setText(QString(allInfo->processInfo[no].state));
            ui->processTable->item(i,3)->setData(Qt::DisplayRole,cpu);
            ui->processTable->item(i,4)->setData(Qt::DisplayRole,allInfo->processInfo[no].usedProcessMemSize);
            ui->processTable->item(i,5)->setData(Qt::DisplayRole,allInfo->processInfo[no].priority);
            allInfo->processInfo[no].showed=true;
        }
        else {
            ui->processTable->removeRow(i);
        }
    }

    for (int i=0;i<processNum;i++)
    {
        if (!allInfo->processInfo[i].showed)
        {
            int rowNum=ui->processTable->rowCount();
            ui->processTable->insertRow(rowNum);
            cpu=0;
            if (secs>=2)
            {
                cpu=allInfo->processInfo[i].totalProcessCPUTime[1]-allInfo->processInfo[i].totalProcessCPUTime[0];
                cpu=cpu/(allInfo->cpuInfo.totalCPUTime[secs-1]-allInfo->cpuInfo.totalCPUTime[secs-2])*100;
            }
            item=new QTableWidgetItem();
            item->setData(Qt::DisplayRole,allInfo->processInfo[i].PID);
            ui->processTable->setItem(rowNum,0,item);
            item=new QTableWidgetItem(QString::fromStdString(allInfo->processInfo[i].name));
            ui->processTable->setItem(rowNum,1,item);
            item=new QTableWidgetItem(QString(allInfo->processInfo[i].state));
            ui->processTable->setItem(rowNum,2,item);
            item=new QTableWidgetItem();
            item->setData(Qt::DisplayRole,cpu);
            ui->processTable->setItem(rowNum,3,item);
            item=new QTableWidgetItem();
            item->setData(Qt::DisplayRole,allInfo->processInfo[i].usedProcessMemSize);
            ui->processTable->setItem(rowNum,4,item);
            item=new QTableWidgetItem();
            item->setData(Qt::DisplayRole,allInfo->processInfo[i].priority);
            ui->processTable->setItem(rowNum,5,item);
        }
    }

    ui->processTable->setSortingEnabled(true);
}

void MainWindow::show_index_1_0()
{
    int userate=0,size=0;
    ui->modelname->setText(QString::fromStdString(allInfo->cpuInfo.modelName));
    ui->cpumenu->setText(QString("内核:\n")
                       + QString("逻辑处理器:\n")
                       + QString("L1 缓存:\n")
                       + QString("L2 缓存:\n")
                       + QString("L3 缓存:\n"));
    ui->cpuinfo->setText(QString::number(allInfo->cpuInfo.coresNum)+"\n"
                       + QString::number(allInfo->cpuInfo.logicalProcessorNum)+"\n"
                       + QString::number(allInfo->cpuInfo.Cache[0])+"KB\n"
                       + QString::number(allInfo->cpuInfo.Cache[1])+"KB\n"
                       + QString::number(allInfo->cpuInfo.Cache[2])+"KB\n");
    size = allInfo->cpuInfo.totalCPUTime.size();
    if (size>=2)
    {
        userate=allInfo->cpuInfo.totalCPUTime[size-1]-allInfo->cpuInfo.totalCPUTime[size-2];
        userate=(userate-(allInfo->cpuInfo.idelCPUTime[size-1]-allInfo->cpuInfo.idelCPUTime[size-2]))/userate;
    }
    ui->useValue->setText(QString::number(userate)+"%");
    ui->speedValue->setText(QString::number(allInfo->cpuInfo.curSpeed/1024,'f',2)+" GHz");
    ui->processValue->setText(QString::number(allInfo->processInfo.size()));
}

void MainWindow::show_index_1_1()
{
    int memTotal;
    int memFree;
    int memAvailable;
    int memBuffers;
    int memCached;      // Cached+SReclaimable
    int memSwapTotal;
    ui->rammenu->setText(QString("内存总容量:\n")
                       + QString("内存空闲大小:\n")
                       + QString("内存可用大小:\n")
                       + QString("缓冲区大小:\n")
                       + QString("Cache大小:\n")
                       + QString("交换分区大小:\n"));

    ui->raminfo->setText(QString(QString::number(allInfo->ramInfo.memTotal/1024.0/1024.0,'f',1))+" GB\n"
                       + QString(QString::number(allInfo->ramInfo.memFree/1024.0/1024.0,'f',1))+" GB\n"
                       + QString(QString::number(allInfo->ramInfo.memAvailable/1024.0/1024.0,'f',1))+" GB\n"
                       + QString(QString::number(allInfo->ramInfo.memBuffers/1024.0/1024.0,'f',1))+" GB\n"
                       + QString(QString::number(allInfo->ramInfo.memCached/1024.0/1024.0,'f',1))+" GB\n"
                       + QString(QString::number(allInfo->ramInfo.memSwapTotal/1024.0/1024.0,'f',1))+" GB\n");

    ui->totalsize->setText(QString(QString::number(allInfo->ramInfo.memTotal/1024.0/1024.0,'f',1))+" GB");
}

void MainWindow::show_index_2()
{
    ui->os_version->setText(QString::fromStdString(allInfo->osInfo.osVersion));
    ui->osmenu->setText(QString("设备名称\n")
                      + QString("内存\n")
                      + QString("处理器\n")
                      + QString("操作系统类型\n"));
    ui->osinfo->setText(QString::fromStdString(allInfo->osInfo.hostName)+"\n"
                      + QString::number(allInfo->ramInfo.memTotal/1024.0/1024.0,'f',1)+"\n"
                      + QString::fromStdString(allInfo->cpuInfo.modelName)+"\n"
                      + QString("64 位"));
}

void MainWindow::show_index_3()
{
    ui->aboutinfo->setText(QString("作者名称:\tXJDKC\n")
                         + QString("联系方式:\txjdkcsq3@gmail.com\n")
                         + QString("开发环境:\tQt 5.12.0\n")
                         + QString("\t\tLinux 4.15.0-45-generic\n")
                         + QString("\t\tgcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0\n"));
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event){

    if(watched == ui->cpuUse  && event->type() == QEvent::Paint){
        drawCPUUse();
    }
    else if(watched == ui->ramUse  && event->type() == QEvent::Paint){
        drawRAMUse();
    }
    return QWidget::eventFilter(watched,event);
}


void MainWindow::drawCPUUse()
{
    QPainter painter(ui->cpuUse);
    painter.setPen(QColor(114, 159, 207));
    int width=ui->cpuUse->width();
    int height=ui->cpuUse->height();
    for (double i=0;i<height;i+=height/10.0)
        painter.drawLine(0,i,width,i);
    for (double i=0;i<width;i+=width/15.0)
        painter.drawLine(i,0,i,height);

    QPen pen;
    pen.setColor(QColor(114, 159, 207));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing,true);
    for (int i=(62-allInfo->cpuInfo.totalCPUTime.size()),j=0;i<=59;i++,j++)
    {
        //i i+1 i+1 i+2
        double prevrate=0,nextrate=0;
        prevrate=allInfo->cpuInfo.totalCPUTime[j+1]-allInfo->cpuInfo.totalCPUTime[j];
        prevrate=(prevrate-(allInfo->cpuInfo.idelCPUTime[j+1]-allInfo->cpuInfo.idelCPUTime[j]))/prevrate;
        nextrate=allInfo->cpuInfo.totalCPUTime[j+2]-allInfo->cpuInfo.totalCPUTime[j+1];
        nextrate=(nextrate-(allInfo->cpuInfo.idelCPUTime[j+2]-allInfo->cpuInfo.idelCPUTime[j+1]))/nextrate;
        painter.drawLine(i*width/60.0,(1-prevrate)*height,(i+1)*width/60.0,(1-nextrate)*height);
    }
}

void MainWindow::drawRAMUse()
{
    QPainter painter(ui->ramUse);
    painter.setPen(QColor(114, 159, 207));
    int width=ui->ramUse->width();
    int height=ui->ramUse->height();
    for (double i=0;i<height;i+=height/10.0)
        painter.drawLine(0,i,width,i);
    for (double i=0;i<width;i+=width/15.0)
        painter.drawLine(i,0,i,height);

    QPen pen;
    pen.setColor(QColor(114, 159, 207));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing,true);
    for (int i=(61-allInfo->ramInfo.memUsed.size()),j=0;i<=59;i++,j++)
    {
        //i i+1 i+1 i+2
        double prevrate=0,nextrate=0;
        prevrate=(double)allInfo->ramInfo.memUsed[j]/allInfo->ramInfo.memTotal;
        nextrate=(double)allInfo->ramInfo.memUsed[j+1]/allInfo->ramInfo.memTotal;
        painter.drawLine(i*width/60.0,(1-prevrate)*height,(i+1)*width/60.0,(1-nextrate)*height);
    }
}
