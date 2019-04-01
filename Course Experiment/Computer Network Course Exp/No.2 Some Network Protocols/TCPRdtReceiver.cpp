#include "stdafx.h"
#include "Global.h"
#include "TCPRdtReceiver.h"

TCPRdtReceiver::TCPRdtReceiver() :expectedSeqNum(0)
{
	lastAckPkt.acknum = -1;
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

TCPRdtReceiver::~TCPRdtReceiver()
{

}

void TCPRdtReceiver::receive(Packet &packet)
{
	int checksum = pUtils->calculateCheckSum(packet);

	if (checksum == packet.checksum&&this->expectedSeqNum == packet.seqnum)
	{
		pUtils->printPacket("[=====正确接收数据=====]：接收方正确收到发送方的数据报文", packet);

		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);

		lastAckPkt.acknum = packet.seqnum; //确认序号等于收到的报文序号
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("[======成功发送ACK=====]：接收方发送确认ACK报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);

		this->expectedSeqNum++;
		this->expectedSeqNum %= (1 << Configuration::SEQNUM_BYTES);
	}
	else {
		if (checksum != packet.checksum) {
			pUtils->printPacket("[=====错误接收数据=====]：接收方没有正确收到发送方发送的数据报文,数据校验错误", packet);
		}
		else {
			pUtils->printPacket("[=====错误接收数据=====]：接收方没有正确收到发送方发送的数据报文,报文序号不对", packet);
		}
		pUtils->printPacket("[========重发ACK=======]：接接收方重新发送上次的确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
	}
}

