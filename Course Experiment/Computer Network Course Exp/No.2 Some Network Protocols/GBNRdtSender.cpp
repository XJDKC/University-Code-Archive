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

	pUtils->printPacket("[=====发送数据报文=====]：发送方发送数据报文", this->window[pos]);
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
	
	if (checksum == ackPkt.checksum) {			//当收到确认报文正确的时候需要
		pUtils->printPacket("[======正确接收ACK=====]：发送方正确收到ACK报文，接收到的正确报文为", ackPkt);
		base = (ackPkt.acknum + 1) % (1 << Configuration::SEQNUM_BYTES);
		if (base == nextseqnum)					//如果当前窗口的所有消息全部发送完毕 
			pns->stopTimer(SENDER, timerNo);	//停止对于当前窗口的计时 直接停止
		else
		{
			pns->stopTimer(SENDER, timerNo);
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
			timerNo = base;
		}
		//显示更新后的窗口
		this->printWindow();
	}
	else {										//不需要处理收到错误报文的情况 因为可能之后的报文是正确的 也可能是超市函数处理
		pUtils->printPacket("[======错误接收ACK=====]：发送方没有正确收到ACK报文，接收到的错误报文为", ackPkt);
	}
}

void GBNRdtSender::timeoutHandler(int seqNum)
{
	cout << "[=========超时=========]：发送方定时器时间到" << endl;
	for (int i = base, pos = 0; i != nextseqnum; i = (i + 1) % (1 << Configuration::SEQNUM_BYTES))
	{
		pos = i % Configuration::WINDOW_SIZE;
		pUtils->printPacket(("[=======重发数据=======]：重发窗口内之前发送数据报文" + to_string(i)).c_str(), this->window[pos]);
		pns->sendToNetworkLayer(RECEIVER, this->window[pos]);
	}
	timerNo = base;
	pns->stopTimer(SENDER, seqNum);				//停止超时的计时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, base);		//打开一个新的计时器
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