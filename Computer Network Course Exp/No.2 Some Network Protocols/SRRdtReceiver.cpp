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
	int num = 1 << Configuration::SEQNUM_BYTES;				//����ܱ�ʾ�ķ�Χ+1 ����ȡģ
	int pos = packet.seqnum%Configuration::WINDOW_SIZE;		//��ǰ��ű����ڽ��մ����е�λ��
	int checksum = pUtils->calculateCheckSum(packet);		//�����жϱ����Ƿ���ȷ ��û�з������ʹ���
	int right = (revbase + Configuration::WINDOW_SIZE - 1) % num;
	if (checksum == packet.checksum)			//������ķ�����ȷ
	{
		if ((packet.seqnum - revbase + num) % num < Configuration::WINDOW_SIZE)//˵������һ�����մ��ڵı���
		{
			pUtils->printPacket("[=====��ȷ��������=====]�����շ���ȷ�յ����ͷ������ݱ���", packet);

			received[pos] = true;			//�������ڵĽ��ձ�־��Ӧλ����1

			//�����ܵ������ݻ��浽������
			memcpy(window[pos].data, packet.payload, sizeof(packet.payload));

			//���͸���ŵ�ack���ĸ����ͷ�
			ackPkt.acknum = packet.seqnum; //ȷ����ŵ����յ��ı������
			ackPkt.checksum = 0;
			ackPkt.checksum = pUtils->calculateCheckSum(ackPkt);
			pUtils->printPacket("[======�ɹ�����ACK=====]�����շ�����ȷ��ACK����", ackPkt);
			pns->sendToNetworkLayer(SENDER, ackPkt);

			this->printWindow();
			//���Խ�revbase��ʼ �������Ѿ����յ��ı��ķ���
			for (int i = revbase; i != (revbase + Configuration::WINDOW_SIZE) % num; i = (i + 1) % num)
			{
				if (received[i%Configuration::WINDOW_SIZE])		//����Ѿ����յ��� ��ô�ͷ��͸��ϲ�
				{
					pns->delivertoAppLayer(RECEIVER, window[i%Configuration::WINDOW_SIZE]);
					received[i%Configuration::WINDOW_SIZE] = false;		//������Ϊfalse
					revbase = (revbase + 1) % num;				//��������
					this->printWindow();
				}
				else											//һ����������û�н��յ��� ����ѭ�� ��֤��Ӧ�ò������˳������ȷ��
					break;
			}
		}
		else									//����˵����֮ǰ���� ����ԭ����ack���Ķ�ʧ������ ��ô��Ӧack��֪��ȷ �÷��ͷ����ڻ���
		{
			ackPkt.acknum = packet.seqnum;
			ackPkt.checksum = 0;
			ackPkt.checksum = pUtils->calculateCheckSum(ackPkt);
			pUtils->printPacket("[=====�յ���ȥ����=====]�����շ��յ�֮ǰ�������ݣ����շ����·���ȷ�ϱ���", ackPkt);
			pns->sendToNetworkLayer(SENDER, ackPkt);
		}
	}
	else
	{
		pUtils->printPacket("[=====�����������=====]�����շ�û����ȷ�յ����ͷ����͵����ݱ���,����У�����", packet);
	}
}

void SRRdtReceiver::printWindow()
{
	cout << "[=====���մ�������=====]: ��ǰ���մ����ڱ������Ϊ: [";
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