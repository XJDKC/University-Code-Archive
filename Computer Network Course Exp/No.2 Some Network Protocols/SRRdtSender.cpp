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
	
	int pos = nextseqnum % Configuration::WINDOW_SIZE;		//���㵱ǰ��ŵı����ڴ����еĻ���λ��
	this->window[pos].acknum = -1;
	this->window[pos].seqnum = nextseqnum;
	this->window[pos].checksum = 0;

	memcpy(this->window[pos].payload, message.data, sizeof(message.data));		//��ȡ����
	this->window[pos].checksum = pUtils->calculateCheckSum(this->window[pos]);	//����У���

	pUtils->printPacket("[=====�������ݱ���=====]�����ͷ��������ݱ���", this->window[pos]);
	pns->sendToNetworkLayer(RECEIVER, this->window[pos]);						//���͸������


	pns->startTimer(SENDER, Configuration::TIME_OUT, pos);						//����λ�ü�ʱ
	
	nextseqnum++;																//��һ���������
	nextseqnum %= (1 << Configuration::SEQNUM_BYTES);

	return true;
}

void SRRdtSender::receive(Packet &ackPkt)
{
	int num = 1 << Configuration::SEQNUM_BYTES;									//������ű�ʾ��Χ+1 ����ȡģ
	int pos = ackPkt.acknum%Configuration::WINDOW_SIZE;							//������յ�������ڴ����е�λ��
	int checksum = pUtils->calculateCheckSum(ackPkt);							//����У���
	int right = (sendbase + Configuration::WINDOW_SIZE - 1) % num;
	
	if (checksum == ackPkt.checksum) {			//���յ�ȷ�ϱ�����ȷ��ʱ�� ֹͣ�ñ��ĵļ�ʱ ���Ի�������
		if ((ackPkt.acknum - sendbase + num) % num < Configuration::WINDOW_SIZE)					//����յ��ı����Ǵ����ڶ�Ӧ�������д��� ����˵���Ƕ�֮ǰ��ACK ��ô�����д���
		{
			if (!acked[pos])					//�����ǰ���Ļ�δ���յ� ��ô���д��� ����Ͳ�����
			{
				acked[pos] = true;						//��λ�õı����Ѿ����ճɹ�
				pUtils->printPacket("[======��ȷ����ACK=====]�����ͷ���ȷ�յ�ACK���ģ����յ�����ȷ����Ϊ", ackPkt);
				pns->stopTimer(SENDER, pos);			//ֹͣ��ʱ

				this->printWindow();
				for (int i = sendbase; i != nextseqnum && acked[i%Configuration::WINDOW_SIZE]; i = (i + 1) % num)	//���������ǰ�������Ľ��ճɹ��ͻ�������
				{
					acked[i%Configuration::WINDOW_SIZE] = false;
					sendbase = (sendbase + 1) % num;
					this->printWindow();
				}
			}
		}
	}
	else {										//����Ҫ�����յ������ĵ���� ��Ϊ����֮��ı�������ȷ�� Ҳ�����ǳ�ʱ��������
		pUtils->printPacket("[======�������ACK=====]�����ͷ�û����ȷ�յ�ACK���ģ����յ��Ĵ�����Ϊ", ackPkt);
	}
}

void SRRdtSender::timeoutHandler(int seqNum)		//�����seqNum ���Ǵ���λ�� ��Ϊ�ڳ����м�ʱ�Ǹ���λ������
{
	cout << "[=========��ʱ=========]�����ͷ���ʱ��ʱ�䵽����ʱ��ʱ�����Ϊ:" << seqNum << endl;
	pUtils->printPacket(("[=======�ط�����=======]���ط�������֮ǰ�������ݱ���" + to_string(this->window[seqNum].seqnum)).c_str(), this->window[seqNum]);
	pns->sendToNetworkLayer(RECEIVER, this->window[seqNum]);
	pns->stopTimer(SENDER, seqNum);									//ֹͣ��ʱ�ļ�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);		//��һ���µļ�ʱ��
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
	cout << "[=====���ʹ�������=====]: ��ǰ���ʹ����ڱ������Ϊ: [";
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