#pragma once
#include <ZinxTCP.h>
class my_tcpData :
	public ZinxTcpData
{
public:
	my_tcpData(int _fd);
	virtual ~my_tcpData();

	// ͨ�� ZinxTcpData �̳�
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};

class my_tcpconnFact :public IZinxTcpConnFact {
	// ͨ�� IZinxTcpConnFact �̳�
	virtual ZinxTcpData * CreateTcpDataChannel(int _fd) override;
};

