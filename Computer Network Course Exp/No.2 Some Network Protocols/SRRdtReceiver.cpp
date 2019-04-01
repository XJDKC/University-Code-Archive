#include "stdafx.h"
#include "Global.h"
#include "SRRdtReceiver.h"
#include <algorithm>

SRRdtReceiver::SRRdtReceiver() :revbase(0)
{
	fill(received, received + Configuration::WINDOW_SIZE, false);

	ackPkt.acknum = -1;
	ackPkt.checksum = 0;
	ackPkt.seqnum = -1;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		ackPkt.payload[i] = '.';
	}
	ackPkt.checksum = pUtils->calculateCheckSum(ackPkt);
}

SRRdtReceiver::~SRRdtReceiver() {}

void SRRdtReceiver::receive(Packet &packet)
{
	int num = 1 << Configuration::SEQNUM_BYTES;				//序号能表示的范围+1 方便取模
	int pos = packet.seqnum%Configuration::WINDOW_SIZE;		//当前序号报文在接收窗口中的位置
	int checksum = pUtils->calculateCheckSum(packet);		//用于判断报文是否正确 有没有发生传送错误
	int right = (revbase + Configuration::WINDOW_SIZE - 1) % num;
	if (checksum == packet.checksum)			//如果报文发送正确
	{
		if ((packet.seqnum - revbase + num) % num < Configuration::WINDOW_SIZE)//说明来了一个接收窗口的报文
		{
			pUtils->printPacket("[=====正确接收数据=====]：接收方正确收到发送方的数据报文", packet);

			received[pos] = true;			//将窗口内的接收标志对应位置置1

			//将接受到的数据缓存到窗口内
			memcpy(window[pos].data, packet.payload, sizeof(packet.payload));

			//发送该序号的ack报文给发送方
			ackPkt.acknum = packet.seqnum; //确认序号等于收到的报文序号
			ackPkt.checksum = 0;
			ackPkt.checksum = pUtils->calculateCheckSum(ackPkt);
			pUtils->printPacket("[======成功发送ACK=====]：接收方发送确认ACK报文", ackPkt);
			pns->sendToNetworkLayer(SENDER, ackPkt);

			this->printWindow();
			//尝试将revbase开始 连续的已经接收到的报文发给
			for (int i = revbase; i != (revbase + Configuration::WINDOW_SIZE) % num; i = (i + 1) % num)
			{
				if (received[i%Configuration::WINDOW_SIZE])		//如果已经接收到了 那么就发送给上层
				{
					pns->delivertoAppLayer(RECEIVER, window[i%Configuration::WINDOW_SIZE]);
					received[i%Configuration::WINDOW_SIZE] = false;		//重新置为false
					revbase = (revbase + 1) % num;				//滑动窗口
					this->printWindow();
				}
				else											//一旦有遇到还没有接收到的 跳出循环 保证给应用层的数据顺序是正确的
					break;
			}
		}
		else									//否则说明是之前报文 产生原因是ack报文丢失或者损坏 那么回应ack告知正确 让发送方窗口滑动
		{
			ackPkt.acknum = packet.seqnum;
			ackPkt.checksum = 0;
			ackPkt.checksum = pUtils->calculateCheckSum(ackPkt);
			pUtils->printPacket("[=====收到过去数据=====]：接收方收到之前窗口数据，接收方重新发送确认报文", ackPkt);
			pns->sendToNetworkLayer(SENDER, ackPkt);
		}
	}
	else
	{
		pUtils->printPacket("[=====错误接收数据=====]：接收方没有正确收到发送方发送的数据报文,数据校验错误", packet);
	}
}

void SRRdtReceiver::printWindow()
{
	cout << "[=====接收窗口内容=====]: 当前接收窗口内报文序号为: [";
	int No = revbase;
	int right = (revbase + Configuration::WINDOW_SIZE) % (1 << Configuration::SEQNUM_BYTES);
	while (No != right)
	{
		cout << No;
		if (received[No%Configuration::WINDOW_SIZE])
			cout << "*";
		No = (No + 1) % (1 << Configuration::SEQNUM_BYTES);
		if (No != right)
			cout << ", ";

	}
	cout << "]" << endl;
}