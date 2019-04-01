#pragma once
#include "RdtSender.h"

class TCPRdtSender :public RdtSender
{
private:
	int base;				
	int nextseqnum;			//��һ��Ҫ���͵ķ����Ӧ�����
	int timerNo;			//ʱ�Ӽ�ʱ
	int quickResend;		//�����ش�����
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