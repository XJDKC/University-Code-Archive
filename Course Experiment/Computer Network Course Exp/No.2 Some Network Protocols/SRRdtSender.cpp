#include "stdafx.h"
#include "Global.h"
#include "SRRdtSender.h"
#include <algorithm>
#include <string>

SRRdtSender::SRRdtSender():sendbase(0), nextseqnum(0)
{
	fill(acked, acked + Configuration::WINDOW_SIZE, false);
}

SRRdtSender::~SRRdtSender() {}

bool SRRdtSender::send(Message &message)
{
	if (this->getWaitingState() == true)
		return false;
	
	int pos = nextseqnum % Configuration::WINDOW_SIZE;		//计算当前序号的报文在窗口中的缓存位置
	this->window[pos].acknum = -1;
	this->window[pos].seqnum = nextseqnum;
	this->window[pos].checksum = 0;

	memcpy(this->window[pos].payload, message.data, sizeof(message.data));		//获取数据
	this->window[pos].checksum = pUtils->calculateCheckSum(this->window[pos]);	//计算校验和

	pUtils->printPacket("[=====发送数据报文=====]：发送方发送数据报文", this->window[pos]);
	pns->sendToNetworkLayer(RECEIVER, this->window[pos]);						//发送给网络层


	pns->startTimer(SENDER, Configuration::TIME_OUT, pos);						//给该位置计时
	
	nextseqnum++;																//下一个报文序号
	nextseqnum %= (1 << Configuration::SEQNUM_BYTES);

	return true;
}

void SRRdtSender::receive(Packet &ackPkt)
{
	int num = 1 << Configuration::SEQNUM_BYTES;									//计算序号表示范围+1 方便取模
	int pos = ackPkt.acknum%Configuration::WINDOW_SIZE;							//计算接收到的序号在窗口中的位置
	int checksum = pUtils->calculateCheckSum(ackPkt);							//计算校验和
	int right = (sendbase + Configuration::WINDOW_SIZE - 1) % num;
	
	if (checksum == ackPkt.checksum) {			//当收到确认报文正确的时候 停止该报文的计时 尝试滑动窗口
		if ((ackPkt.acknum - sendbase + num) % num < Configuration::WINDOW_SIZE)					//如果收到的报文是窗口内对应序号则进行处理 否则说明是对之前的ACK 那么不进行处理
		{
			if (!acked[pos])					//如果当前报文还未接收到 那么进行处理 否则就不处理
			{
				acked[pos] = true;						//该位置的报文已经接收成功
				pUtils->printPacket("[======正确接收ACK=====]：发送方正确收到ACK报文，接收到的正确报文为", ackPkt);
				pns->stopTimer(SENDER, pos);			//停止计时

				this->printWindow();
				for (int i = sendbase; i != nextseqnum && acked[i%Configuration::WINDOW_SIZE]; i = (i + 1) % num)	//如果窗口内前面连续的接收成功就滑动窗口
				{
					acked[i%Configuration::WINDOW_SIZE] = false;
					sendbase = (sendbase + 1) % num;
					this->printWindow();
				}
			}
		}
	}
	else {										//不需要处理收到错误报文的情况 因为可能之后的报文是正确的 也可能是超时函数处理
		pUtils->printPacket("[======错误接收ACK=====]：发送方没有正确收到ACK报文，接收到的错误报文为", ackPkt);
	}
}

void SRRdtSender::timeoutHandler(int seqNum)		//这里的seqNum 就是窗口位置 因为在程序中计时是根据位置来的
{
	cout << "[=========超时=========]：发送方定时器时间到，超时计时器序号为:" << seqNum << endl;
	pUtils->printPacket(("[=======重发数据=======]：重发窗口内之前发送数据报文" + to_string(this->window[seqNum].seqnum)).c_str(), this->window[seqNum]);
	pns->sendToNetworkLayer(RECEIVER, this->window[seqNum]);
	pns->stopTimer(SENDER, seqNum);									//停止超时的计时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);		//打开一个新的计时器
}

bool SRRdtSender::getWaitingState()
{
	int num = 1 << Configuration::SEQNUM_BYTES;
	int sub = (nextseqnum + num - sendbase) % num;
	if (sub >= Configuration::WINDOW_SIZE)
		return true;
	else
		return false;
}

void SRRdtSender::printWindow()
{
	cout << "[=====发送窗口内容=====]: 当前发送窗口内报文序号为: [";
	int No = sendbase;
	int right = (sendbase + Configuration::WINDOW_SIZE) % (1 << Configuration::SEQNUM_BYTES);
	while (No != right)
	{
		cout << No;
		if (acked[No%Configuration::WINDOW_SIZE])
			cout << "*";
		No = (No + 1) % (1 << Configuration::SEQNUM_BYTES);
		if (No != right)
			cout << ", ";

	}
	cout << "]" << endl;
}