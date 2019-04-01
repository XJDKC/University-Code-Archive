#pragma once
#include "RdtReceiver.h"

class TCPRdtReceiver :public RdtReceiver
{
private:
	int expectedSeqNum;
	Packet lastAckPkt;
public:
	TCPRdtReceiver();
	virtual ~TCPRdtReceiver();
public:
	void receive(Packet &packet);
};