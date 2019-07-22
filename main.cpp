#include <cstdio>
#include <iostream>
#include <zinx.h>

using namespace std;



//������׼���ͨ����
class stdout_channel :public Ichannel {
	// ͨ�� Ichannel �̳�
	virtual bool Init() override
	{
		return true;
	}
	virtual bool ReadFd(std::string & _input) override
	{
		return false;
	}
	virtual bool WriteFd(std::string & _output) override
	{
		cout << _output << endl;
		return true;
	}
	virtual void Fini() override
	{
	}
	virtual int GetFd() override
	{
		return 1;
	}
	virtual std::string GetChannelInfo() override
	{
		return "stdout_channel";
	}
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override
	{
		return nullptr;
	}
};



//2. �������ݴ�����--���̳�AzhinxHandler
class echo :public AZinxHandler {
	// ͨ�� AZinxHandler �̳�
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override
	{
		/*�������������׼���*/
		GET_REF2DATA(BytesMsg, byte, _oInput);
	
		ZinxKernel::Zinx_SendOut(byte.szData, *(ZinxKernel::Zinx_GetChannel_ByInfo("stdout_channel")));

		return nullptr;
	}
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override
	{
		//û����һ������
		return nullptr;
	}
};

echo g_echo;



class exitFramework :public AZinxHandler {
	// ͨ�� AZinxHandler �̳�
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override
	{
		ZinxKernel::Zinx_Exit();
		return nullptr;
	}
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override
	{
		return nullptr;
	}
};

exitFramework g_exit;

class cmd :public AZinxHandler {
	// ͨ�� AZinxHandler �̳�
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override
	{
		/*͸��������ֽ�--��copy����*/
		GET_REF2DATA(BytesMsg, byte, _oInput);
		return new BytesMsg(byte);
	}
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override
	{
		/*����echo�������exitframework����*/
		GET_REF2DATA(BytesMsg, byte, _oNextMsg);
		if ("exit" == byte.szData)
		{
			//�����˳���Ķ���
			return &g_exit;
		}
		else
		{
			//���ػ��Զ���
			return &g_echo;
		}
		return nullptr;
	}
};

cmd g_cmd;

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
		/*���ش����ȡ�����ݵĶ���,���������ж���Ķ���*/
		return &g_cmd;
	}
};

int main()
{
	//1. ��ʼ�����
	if (true == ZinxKernel::ZinxKernelInit())
	{
		stdin_channel *pstdin_channel = new stdin_channel();
		stdout_channel *pstdout_channel = new stdout_channel();
		//4. ���ͨ�������kernel��
		ZinxKernel::Zinx_Add_Channel(*pstdin_channel);
		ZinxKernel::Zinx_Add_Channel(*pstdout_channel);
		//5. ����run
		ZinxKernel::Zinx_Run();

		ZinxKernel::Zinx_Del_Channel(*pstdin_channel);
		ZinxKernel::Zinx_Del_Channel(*pstdout_channel);

		delete pstdin_channel;
		delete pstdout_channel;

		ZinxKernel::ZinxKernelFini();
	}
}