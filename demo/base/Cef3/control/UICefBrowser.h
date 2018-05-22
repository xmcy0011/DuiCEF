#pragma once

#include <queue>

#include "include/cef_client.h"

#include "../common/process_message_handler.h"
#include "../common/cef_client_handler.h"

using CefCacheTask = std::function<void(void)>;

class CCefBrowserUI : public CControlUI
{
public:
	CCefBrowserUI();
	virtual ~CCefBrowserUI();

	// Control
	void DoInit();
	void DoPaint(HDC hDC, const RECT& rcPaint);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetVisible(bool bVisible);
	void SetInternVisible(bool bVisible);


	// CefClientHandler�ص��ӿ�
	void OnProcessMessageReceived(CefRefPtr<CefProcessMessage> message);
	void OnAfterCreated(CefRefPtr<CefBrowser> browser);
	void OnLoadStart();
	void OnLoadEnd(int httpStatusCode);
	void OnLoadError(int errorCode, const CefString& errorText, const CefString& failedUrl);


	// �Զ���ӿ�
	void Navigate2(CefString url);
	void RunJs(CefString JsCode);


	// ������Ϣ����
	void SetProcessMessageHandler(CefRefPtr<CProcessMessageHandler> pHandler);

private:
	void resize();

private:
	
	CefRefPtr<CCefClientHandler>		m_pClientHandler;
	CefRefPtr<CefBrowser>				m_pBrowser;
	CefRefPtr<CProcessMessageHandler>	m_pProcessMessageHandler;

	// browser�������ǰ���������
	std::queue<CefCacheTask>	m_AfterCreatedCacheTasks;

	// ҳ��������ǰ���������
	bool m_bLoadFinish;
	std::queue<CefCacheTask>	m_LoadEndCacheTasks;
};