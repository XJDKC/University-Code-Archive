#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QCloseEvent>
#include "ui_HTTPServerGUI.h"
#include "Config.h"


class HTTPServerGUI : public QMainWindow
{
	Q_OBJECT
		friend class Server;

public:
	HTTPServerGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::HTTPServerGUIClass ui;

	QPushButton *start;
	QPushButton *close;
	QPushButton *SetIP;
	QPushButton *SetPORT;
	QLabel *label;
	QScrollArea *console;
	QLineEdit *IP;
	QLineEdit *Port;

private slots:
	void on_startbutton_clicked();
	void on_closebutton_clicked();
	void on_ipbutton_clicked();
	void on_portbutton_clicked();
	void closeEvent(QCloseEvent *event);

};
