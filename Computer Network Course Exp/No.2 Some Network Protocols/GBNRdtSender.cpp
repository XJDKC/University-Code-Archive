#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"
#include <string>

GBNRdtSender::GBNRdtSender() :base(0), nextseqnum(0),timerNo(-1) {}

GBNRdtSender::~GBNRdtSender() {}

bool GBNRdtSender::send(Message &message)
{
	if (this->getWaitingState() == true)
		return false;
	
	int pos = nextseqnum % Configuration::WINDOW_SIZE;
	this->window[pos].acknum = -1;
	this->window[pos].seqnum = nextseqnum;
	this->window[pos].checksum = 0;

	memcpy(this->window[pos].payload, message.data, sizeof(message.data));
	this->window[pos].checksum = pUtils->calculateCheckSum(this->window[pos]);

	pUtils->printPacket("[=====�������ݱ���=====]�����ͷ��������ݱ���", this->window[pos]);
	pns->sendToNetworkLayer(RECEIVER, this->window[pos]);
	
	if (base == nextseqnum)
	{
		timerNo = base;
		pns->startTimer(SENDER,Configuration::TIME_OUT, base);
	}
	nextseqnum++;
	nextseqnum %= (1 << Configuration::SEQNUM_BYTES);
	
	return true;
}


void GBNRdtSender::receive(Packet &ackPkt)
{
	int checksum = pUtils->calculateCheckSum(ackPkt);
	
	if (checksum == ackPkt.checksum) {			//���յ�ȷ�ϱ�����ȷ��ʱ����Ҫ
		pUtils->printPacket("[======��ȷ����ACK=====]�����ͷ���ȷ�յ�ACK���ģ����յ�����ȷ����Ϊ", ackPkt);
		base = (ackPkt.acknum + 1) % (1 << Configuration::SEQNUM_BYTES);
		if (base == nextseqnum)					//�����ǰ���ڵ�������Ϣȫ��������� 
			pns->stopTimer(SENDER, timerNo);	//ֹͣ���ڵ�ǰ���ڵļ�ʱ ֱ��ֹͣ
		else
		{
			pns->stopTimer(SENDER, timerNo);
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
			timerNo = base;
		}
		//��ʾ���º�Ĵ���
		this->printWindow();
	}
	else {										//����Ҫ�����յ������ĵ���� ��Ϊ����֮��ı�������ȷ�� Ҳ�����ǳ��к�������
		pUtils->printPacket("[======�������ACK=====]�����ͷ�û����ȷ�յ�ACK���ģ����յ��Ĵ�����Ϊ", ackPkt);
	}
}

void GBNRdtSender::timeoutHandler(int seqNum)
{
	cout << "[=========��ʱ=========]�����ͷ���ʱ��ʱ�䵽" << endl;
	for (int i = base, pos = 0; i != nextseqnum; i = (i + 1) % (1 << Configuration::SEQNUM_BYTES))
	{
		pos = i % Configuration::WINDOW_SIZE;
		pUtils->printPacket(("[=======�ط�����=======]���ط�������֮ǰ�������ݱ���" + to_string(i)).c_str(), this->window[pos]);
		pns->sendToNetworkLayer(RECEIVER, this->window[pos]);
	}
	timerNo = base;
	pns->stopTimer(SENDER, seqNum);				//ֹͣ��ʱ�ļ�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, base);		//��һ���µļ�ʱ��
}

bool GBNRdtSender::getWaitingState()
{
	int sub = (nextseqnum - base + (1 << Configuration::SEQNUM_BYTES)) % (1 << Configuration::SEQNUM_BYTES);
	if (sub >= Configuration::WINDOW_SIZE)
		return true;
	else
		return false;
}

void GBNRdtSender::printWindow()
{
	cout << "[=====���ʹ�������=====]: ��ǰ���ʹ����ڱ������Ϊ: [";
	int No = base;
	int right = (base + Configuration::WINDOW_SIZE) % (1 << Configuration::SEQNUM_BYTES);
	while (No != right)
	{
		if (No == nextseqnum)
			cout << "| ";
		cout << No;
		No = (No + 1) % (1 << Configuration::SEQNUM_BYTES);
		if (No != right)
			cout << ", ";
		
	}
	cout << "]" << endl;
}