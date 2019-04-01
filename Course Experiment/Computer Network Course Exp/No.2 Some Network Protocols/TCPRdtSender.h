#pragma once
#include "RdtSender.h"

class TCPRdtSender :public RdtSender
{
private:
	int base;				
	int nextseqnum;			//下一个要发送的分组对应的序号
	int timerNo;			//时钟计时
	int quickResend;		//快速重传计数
	Packet window[Configuration::WINDOW_SIZE];
public:
	TCPRdtSender();
	virtual ~TCPRdtSender();
	virtual void printWindow();
public:
	virtual bool send(Message &message);
	virtual void receive(Packet &ackPkt);
	virtual void timeoutHandler(int seqNum);
	virtual bool getWaitingState();
};