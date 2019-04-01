#pragma once
#include "RdtSender.h"

class GBNRdtSender:public RdtSender
{
private:
	int base;
	int nextseqnum;
	int timerNo;
	Packet window[Configuration::WINDOW_SIZE];
public:
	GBNRdtSender();
	virtual ~GBNRdtSender();
	virtual void printWindow();
public:
	virtual bool send(Message &message);
	virtual void receive(Packet &ackPkt);
	virtual void timeoutHandler(int seqNum);
	virtual bool getWaitingState();
};