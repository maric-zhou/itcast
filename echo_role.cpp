#include "echo_role.h"

#include "cmd_msg.h"
#include "cmd_parse_protocol.h"

echo_role::echo_role()
{
}


echo_role::~echo_role()
{
}

bool echo_role::Init()
{
	//�����ʼ���ɹ�
	return true;
}

//������Ϣ������
UserData * echo_role::ProcMsg(UserData & _poUserData)
{
	//ȡ�������Ե�����
	GET_REF2DATA(cmd_msg, input, _poUserData);
	std::string echo_string = input.echo_string;
	
	//������������Ϣ
	cmd_msg *pout = new cmd_msg();
	pout->echo_string = echo_string;
	//���ͳ�ȥ
	ZinxKernel::Zinx_SendOut(*pout, *(cmd_parse_protocol::GetInstance()));

	//û�к�������
	return nullptr;
}

void echo_role::Fini()
{
}

bool exit_framework_role::Init()
{
	return false;
}

UserData * exit_framework_role::ProcMsg(UserData & _poUserData)
{
	return nullptr;
}

void exit_framework_role::Fini()
{
}

bool output_mng_role::Init()
{
	return false;
}

UserData * output_mng_role::ProcMsg(UserData & _poUserData)
{
	return nullptr;
}

void output_mng_role::Fini()
{
}
