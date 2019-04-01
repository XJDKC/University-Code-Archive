#include "stdafx.h"
#include "Global.h"
#include "TCPRdtSender.h"

TCPRdtSender::TCPRdtSender() :base(0), nextseqnum(0), timerNo(-1), quickResend(0) {}

TCPRdtSender::~TCPRdtSender()
{

}

bool TCPRdtSender::send(Message &message)
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
		pns->startTimer(SENDER, Configuration::TIME_OUT, base);
	}


	nextseqnum++;
	nextseqnum %= (1 << Configuration::SEQNUM_BYTES);

	return true;
}

void TCPRdtSender::receive(Packet &ackPkt)
{
	int pos = base % Configuration::WINDOW_SIZE;
	int num = 1 << Configuration::SEQNUM_BYTES;
	int checksum = pUtils->calculateCheckSum(ackPkt);

	if (checksum == ackPkt.checksum) {			//���յ�ȷ�ϱ�����ȷ��ʱ����Ҫ
		if ((ackPkt.acknum - base + num) % num < Configuration::WINDOW_SIZE)
		{
			quickResend = 1;
			pUtils->printPacket("[======��ȷ����ACK=====]�����ͷ���ȷ�յ�ACK���ģ����յ�����ȷ����Ϊ", ackPkt);
			base = (ackPkt.acknum + 1) % (1 << Configuration::SEQNUM_BYTES);
			if (base == nextseqnum)					//�����ǰ���ڵ�������Ϣȫ��������� 
				pns->stopTimer(SENDER, timerNo);	//ֹͣ���ڵ�ǰ���ڵļ�ʱ ֱ��ֹͣ

			this->printWindow();
		}
		else
		{
			quickResend++;
			if (quickResend == 3)
			{
				pUtils->printPacket("[=======�����ش�=======]�����ͷ������ش����δȷ�ϵı���", this->window[pos]);
				pns->sendToNetworkLayer(RECEIVER, this->window[pos]);
			}
		}
	}
	else {										//����Ҫ�����յ������ĵ���� ��Ϊ����֮��ı�������ȷ�� Ҳ�����ǳ��к�������
		pUtils->printPacket("[======�������ACK=====]�����ͷ�û����ȷ�յ�ACK���ģ����յ��Ĵ�����Ϊ", ackPkt);
	}
}

void TCPRdtSender::timeoutHandler(int seqNum)
{
	int pos = base % Configuration::WINDOW_SIZE;
	cout << "[=========��ʱ=========]�����ͷ���ʱ��ʱ�䵽" << endl;
	pUtils->printPacket("[=======�ط�����=======]���ط�������֮ǰ�������ݱ���", this->window[pos]);
	pns->sendToNetworkLayer(RECEIVER, this->window[pos]);

	timerNo = base;
	pns->stopTimer(SENDER, seqNum);								//ֹͣ��ʱ�ļ�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, base);		//��һ���µļ�ʱ��
}

bool TCPRdtSender::getWaitingState()
{
	int sub = (nextseqnum - base + (1 << Configuration::SEQNUM_BYTES)) % (1 << Configuration::SEQNUM_BYTES);
	if (sub >= Configuration::WINDOW_SIZE)
		return true;
	else
		return false;
}

void TCPRdtSender::printWindow()
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