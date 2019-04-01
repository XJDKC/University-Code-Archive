// StopWait.cpp : 定义控制台应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "GBNRdtSender.h"
#include "GBNRdtReceiver.h"
#include "SRRdtSender.h"
#include "SRRdtReceiver.h"
#include "TCPRdtSender.h"
#include "TCPRdtReceiver.h"
#include <cstdio>


int main(int argc, char* argv[])
{
	freopen("data.txt", "w", stdout);

	RdtSender *ps;
	RdtReceiver * pr;
	switch (argc > 1 ? argv[1][0] : '\0')
	{
		case '0':ps = new GBNRdtSender(); pr = new GBNRdtReceiver(); break;
		case '1':ps = new SRRdtSender(); pr = new SRRdtReceiver(); break;
		case '2':ps = new TCPRdtSender(); pr = new TCPRdtReceiver(); break;
		default:ps = new GBNRdtSender(); pr = new GBNRdtReceiver();
	}

	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("input.txt");
	pns->setOutputFile("output.txt");
	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//指向唯一的工具类实例，只在main函数结束前delete
	delete pns;										//指向唯一的模拟网络环境类实例，只在main函数结束前delete
	
	return 0;
}