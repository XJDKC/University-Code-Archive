#pragma once
#include "RdtReceiver.h"

class SRRdtReceiver :public RdtReceiver
{
private:
	int revbase;
	bool received[Configuration::WINDOW_SIZE];
	Packet ackPkt;
	Message window[Configuration::WINDOW_SIZE];
public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();
	virtual void printWindow();
public:
	void receive(Packet &packet);
};