#include "my_tcpData.h"
#include "cmd_parse_protocol.h"



my_tcpData::my_tcpData(int _fd):ZinxTcpData(_fd)
{
}


my_tcpData::~my_tcpData()
{
}

AZinxHandler * my_tcpData::GetInputNextStage(BytesMsg & _oInput)
{
	return cmd_parse_protocol::GetInstance();
}

ZinxTcpData * my_tcpconnFact::CreateTcpDataChannel(int _fd)
{
	//����һ��TCP����ͨ�����󣬷���֮
	
	return new my_tcpData(_fd);
}
