#pragma once
#include "RdtReceiver.h"

class GBNRdtReceiver :public RdtReceiver
{
private:
	int expectedSeqNum;
	Packet lastAckPkt;
public:
	GBNRdtReceiver();
	virtual ~GBNRdtReceiver();

public:
	void receive(Packet &packet);
};