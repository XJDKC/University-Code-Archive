#include "HTTPServerGUI.h"
#include "Server.h"
#include "Config.h"
#include <conio.h>
#include <thread>
#include <iostream>

Server srv;
thread main;

HTTPServerGUI::HTTPServerGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	if (Config::getConfig() == -1) return;

	console = this->findChild<QScrollArea *>("Console");
	console->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	console->viewport()->setBackgroundRole(QPalette::Light);
	console->viewport()->setAutoFillBackground(true);
	
	label = new QLabel(this);
	console->setWidget(label);
	label->setMinimumSize(20000, 20000);
	label->setAlignment(Qt::AlignTop);
	start = this->findChild<QPushButton *>("Start");
	close = this->findChild<QPushButton *>("Close");
	SetIP = this->findChild<QPushButton *>("SetIP");
	SetPORT = this->findChild<QPushButton *>("SetPORT");
	IP = this->findChild<QLineEdit *>("IP");
	Port = this->findChild<QLineEdit *>("Port");

	QObject::connect(start, SIGNAL(clicked()), this, SLOT(on_startbutton_clicked()));
	QObject::connect(close, SIGNAL(clicked()), this, SLOT(on_closebutton_clicked()));
	QObject::connect(SetIP, SIGNAL(clicked()), this, SLOT(on_ipbutton_clicked()));
	QObject::connect(SetPORT, SIGNAL(clicked()), this, SLOT(on_portbutton_clicked()));
}

void HTTPServerGUI::on_startbutton_clicked()
{
	if (!srv.opened())
	{
		srv.setGUI(this);
		//this->label->setText("1");
		if (srv.WinsockStartup() == -1) return ;
		if (srv.ServerStartup() == -1) return ;
		if (srv.ListenStartup() == -1) return ;
		main = std::thread(&Server::Loop, &srv);
	}

}
void HTTPServerGUI::on_closebutton_clicked()
{
	if (srv.opened())
	{
		srv.close();
		srv.~Server();
		if (main.joinable())
			main.join();
		this->label->setText("");
	}

}

void HTTPServerGUI::on_ipbutton_clicked()
{
	QString temp=IP->text();
	Config::setIP(temp.toStdString());
}

void HTTPServerGUI::on_portbutton_clicked()
{
	QString temp = Port->text();
	Config::setPORT(temp.toStdString());
}

void HTTPServerGUI::closeEvent(QCloseEvent *event)
{
	on_closebutton_clicked();
}