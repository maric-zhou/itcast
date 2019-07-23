#include "cmd_parse_protocol.h"
#include "cmd_msg.h"
#include <list>
#include"echo_role.h"

cmd_parse_protocol cmd_parse_protocol::m_instance;

cmd_parse_protocol::cmd_parse_protocol()
{
}


cmd_parse_protocol::~cmd_parse_protocol()
{
}

UserData * cmd_parse_protocol::raw2request(std::string _szInput)
{
	//�������
	cmd_msg *pout = new cmd_msg();
	if ("exit" == _szInput)
	{
		pout->is_frame_exit = true;
	}
	if ("close" == _szInput)
	{
		pout->output_open = false;
	}
	if ("open" == _szInput)
	{
		pout->output_open = true;
	}

	pout->echo_string = _szInput;
	return pout;
}

std::string * cmd_parse_protocol::response2raw(UserData & _oUserData)
{
	GET_REF2DATA(cmd_msg, output, _oUserData);

	return new std::string(output.echo_string);
}

Irole * cmd_parse_protocol::GetMsgProcessor(UserDataMsg & _oUserDataMsg)
{
	//�ж���Ϣ���ݷַ�����ͬrole����
	GET_REF2DATA(cmd_msg, output, *_oUserDataMsg.poUserData);
	//����role������
	std::list<Irole*> role_list = ZinxKernel::Zinx_GetAllRole();
	/*���������role����*/
	if (output.echo_string == "exit")
	{
		/*����exit_framework����*/
		for (auto role : role_list)
		{
			if (NULL != dynamic_cast<exit_framework_role *>(role))
			{
				return role;
			}
		}
	}
	if (output.echo_string == "open" || output.echo_string == "close")
	{
		/*����output_mng_role����*/
		for (auto role : role_list)
		{
			if (NULL != dynamic_cast<output_mng_role *>(role))
			{
				return role;
			}
		}
	}
	/*����echo_role����*/
	for (auto role : role_list)
	{
		if (NULL != dynamic_cast<echo_role *>(role))
		{
			return role;
		}
	}
	return nullptr;
}

Ichannel * cmd_parse_protocol::GetMsgSender(BytesMsg & _oBytes)
{
	return ZinxKernel::Zinx_GetChannel_ByInfo("stdout_channel");;
}
