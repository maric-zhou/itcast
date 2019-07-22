#include <cstdio>
#include <iostream>
#include <zinx.h>

using namespace std;

//2. �������ݴ�����--���̳�AzhinxHandler
class echo :public AZinxHandler {
	// ͨ�� AZinxHandler �̳�
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override
	{
		/*�������������׼���*/
		GET_REF2DATA(BytesMsg, byte, _oInput);
		cout << byte.szData << endl;
		return nullptr;
	}
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override
	{
		//û����һ������
		return nullptr;
	}
};

echo g_echo;

//3. ����IOͨ����-- - ���̳�Ichannel��
class stdin_channel :public Ichannel {
	// ͨ�� Ichannel �̳�
	virtual bool Init() override
	{
		return true;
	}
	virtual bool ReadFd(std::string & _input) override
	{
		//����׼��������ݴ浽_input��
		cin >> _input;
		return true;
	}
	virtual bool WriteFd(std::string & _output) override
	{
		return false;
	}
	virtual void Fini() override
	{
	}
	virtual int GetFd() override
	{
		return 0;
	}
	virtual std::string GetChannelInfo() override
	{
		return "stdin_channel";
	}
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override
	{
		/*���ش����ȡ�����ݵĶ���,����g_echo����*/
		return &g_echo;
	}
};

int main()
{
	//1. ��ʼ�����
	ZinxKernel::ZinxKernelInit();
	stdin_channel *pchannel = new stdin_channel();


	//4. ���ͨ�������kernel��
	ZinxKernel::Zinx_Add_Channel(*pchannel);
	//5. ����run
	ZinxKernel::Zinx_Run();

}