#include "stdafx.h"

#include "client_browser_app.h"

void ClientAppBrowser::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{
	//�鿴����������� http://peter.sh/experiments/chromium-command-line-switches/#disable-gpu-process-prelaunch

	// cef3 ��Lantern ��ϵͳ����ʱ.pac �ļ�ʱ�����
	// �Ѿ�ȷ���Ǵ˰汾Cef��bug
	// Ŀǰ�ȼ���˲��������ߴ�����ȥִ��.pac�ļ���
	command_line->AppendSwitch("no-proxy-server");

	//����GPU����
	command_line->AppendSwitch("--disable-gpu");

	//�������е�ҳ�湲��һ�����̣��Խ�ʡ������
	command_line->AppendSwitchWithValue("--renderer-process-limit", "1");

#if 0
	/*�Ƽ�ʹ�����·���*/
	command_line->AppendSwitchWithValue("ppapi-flash-path", "PepperFlash/pepflashplayer.dll");
	command_line->AppendSwitchWithValue("ppapi-flash-version", "22.0.0.192");
	command_line->AppendSwitchWithValue("plugin-policy", "allow");
#endif
}