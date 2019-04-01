#pragma once
#include "RdtSender.h"

class SRRdtSender :public RdtSender
{
private:
	int sendbase;
	int nextseqnum;
	bool acked[Configuration::WINDOW_SIZE];
	Packet window[Configuration::WINDOW_SIZE];
public:
	SRRdtSender();
	virtual ~SRRdtSender();
	virtual void printWindow();
public:
	virtual bool send(Message &message);
	virtual void receive(Packet &ackPkt);
	virtual void timeoutHandler(int seqNum);
	virtual bool getWaitingState();
};