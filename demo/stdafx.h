// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "resource.h"
#include "UIlib.h"

using namespace DuiLib;
using namespace Gdiplus;

#include "base/Cef3/cef_util.h"
#include "base/ControlEx/ControlEx.h"

#ifdef _DEBUG
	#pragma comment(lib, "Duilib/DuiLib_d.lib")
	#pragma comment(lib, "duicef/duicef_d.lib")
#else
	#pragma comment(lib, "Duilib/DuiLib.lib")
	#pragma comment(lib, "duicef/duicef.lib")
#endif

//#include <vld.h>