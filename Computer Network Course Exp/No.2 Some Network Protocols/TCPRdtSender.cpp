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

	pUtils->printPacket("[=====发送数据报文=====]：发送方发送数据报文", this->window[pos]);
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

	if (checksum == ackPkt.checksum) {			//当收到确认报文正确的时候需要
		if ((ackPkt.acknum - base + num) % num < Configuration::WINDOW_SIZE)
		{
			quickResend = 1;
			pUtils->printPacket("[======正确接收ACK=====]：发送方正确收到ACK报文，接收到的正确报文为", ackPkt);
			base = (ackPkt.acknum + 1) % (1 << Configuration::SEQNUM_BYTES);
			if (base == nextseqnum)					//如果当前窗口的所有消息全部发送完毕 
				pns->stopTimer(SENDER, timerNo);	//停止对于当前窗口的计时 直接停止

			this->printWindow();
		}
		else
		{
			quickResend++;
			if (quickResend == 3)
			{
				pUtils->printPacket("[=======快速重传=======]：发送方快速重传最久未确认的报文", this->window[pos]);
				pns->sendToNetworkLayer(RECEIVER, this->window[pos]);
			}
		}
	}
	else {										//不需要处理收到错误报文的情况 因为可能之后的报文是正确的 也可能是超市函数处理
		pUtils->printPacket("[======错误接收ACK=====]：发送方没有正确收到ACK报文，接收到的错误报文为", ackPkt);
	}
}

void TCPRdtSender::timeoutHandler(int seqNum)
{
	int pos = base % Configuration::WINDOW_SIZE;
	cout << "[=========超时=========]：发送方定时器时间到" << endl;
	pUtils->printPacket("[=======重发数据=======]：重发窗口内之前发送数据报文", this->window[pos]);
	pns->sendToNetworkLayer(RECEIVER, this->window[pos]);

	timerNo = base;
	pns->stopTimer(SENDER, seqNum);								//停止超时的计时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, base);		//打开一个新的计时器
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
	cout << "[=====发送窗口内容=====]: 当前发送窗口内报文序号为: [";
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