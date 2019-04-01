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
		pUtils->printPacket("[=====��ȷ��������=====]�����շ���ȷ�յ����ͷ������ݱ���", packet);

		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);

		lastAckPkt.acknum = packet.seqnum; //ȷ����ŵ����յ��ı������
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("[======�ɹ�����ACK=====]�����շ�����ȷ��ACK����", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);

		this->expectedSeqNum++;
		this->expectedSeqNum %= (1 << Configuration::SEQNUM_BYTES);
	}
	else {
		if (checksum != packet.checksum) {
			pUtils->printPacket("[=====�����������=====]�����շ�û����ȷ�յ����ͷ����͵����ݱ���,����У�����", packet);
		}
		else {
			pUtils->printPacket("[=====�����������=====]�����շ�û����ȷ�յ����ͷ����͵����ݱ���,������Ų���", packet);
		}
		pUtils->printPacket("[========�ط�ACK=======]���ӽ��շ����·����ϴε�ȷ�ϱ���", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
	}
}

