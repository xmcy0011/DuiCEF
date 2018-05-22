#include "stdafx.h"
#include "UICefBrowser.h"

CCefBrowserUI::CCefBrowserUI()
	: m_pProcessMessageHandler(new CProcessMessageHandler)
	, m_pClientHandler(new CCefClientHandler(this))
{
	
}

CCefBrowserUI::~CCefBrowserUI()
{
	m_pClientHandler->Close();

	if (m_pBrowser != nullptr)
	{
		m_pClientHandler->CloseBrowser(m_pBrowser);
	}
}

void CCefBrowserUI::DoInit()
{
	m_pClientHandler->CreateBrowser(m_pManager->GetPaintWindow(), m_rcItem);
}

void CCefBrowserUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
	resize();

	return CControlUI::DoPaint(hDC, rcPaint);
}

void CCefBrowserUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("url")) == 0) Navigate2(pstrValue);
	else return CControlUI::SetAttribute(pstrName, pstrValue);
}

void CCefBrowserUI::SetVisible(bool bVisible)
{
	if (m_pBrowser != nullptr)
	{
		m_pBrowser->GetHost()->SetWindowVisibility(bVisible);
	}
	else
	{
		m_AfterCreatedCacheTasks.push([bVisible, this]{ SetVisible(bVisible); });
	}

	return CControlUI::SetVisible(bVisible);
}

void CCefBrowserUI::SetInternVisible(bool bVisible)
{
	if (m_pBrowser != nullptr)
	{
		m_pBrowser->GetHost()->SetWindowVisibility(bVisible);
	}
	else
	{
		m_AfterCreatedCacheTasks.push([bVisible, this]{ SetInternVisible(bVisible); });
	}

	return CControlUI::SetInternVisible(bVisible);
}

void CCefBrowserUI::SetProcessMessageHandler(CefRefPtr<CProcessMessageHandler> pHandler)
{
	m_pProcessMessageHandler = pHandler;
}

void CCefBrowserUI::OnProcessMessageReceived(CefRefPtr<CefProcessMessage> message)
{
	if (m_pProcessMessageHandler != nullptr)
	{
		m_pProcessMessageHandler->OnProcessMessageReceived(message);
	}
}

void CCefBrowserUI::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	// ִֻ��һ��
	if (m_pBrowser != nullptr)
		return;

	m_pBrowser = browser;

	// ִ�л��������
	CefCacheTask task;
	while (!m_AfterCreatedCacheTasks.empty())
	{
		task = move(m_AfterCreatedCacheTasks.front());
		m_AfterCreatedCacheTasks.pop();

		task();
	}
}

void CCefBrowserUI::Navigate2(CefString url)
{
	if (m_pBrowser != nullptr)
	{
		m_pBrowser->GetMainFrame()->LoadURL(url);
	}
	else
	{
		m_AfterCreatedCacheTasks.push([url, this]
		{
			Navigate2(url);
		});
	}
}

void CCefBrowserUI::RunJs(CefString JsCode)
{
	if (m_pBrowser != nullptr)
	{
		m_pBrowser->GetMainFrame()->ExecuteJavaScript(JsCode, "", 0);
	}
	else
	{
		m_AfterCreatedCacheTasks.push([JsCode, this]{ RunJs(JsCode); });
	}
}

void CCefBrowserUI::resize()
{
	if (m_pBrowser != nullptr)
	{
		POINT pt	= { m_rcItem.left, m_rcItem.top };
		HWND hwnd	= m_pBrowser->GetHost()->GetWindowHandle();

		if (GetWindowStyle(hwnd) & WS_POPUP)
		{
			::ClientToScreen(GetManager()->GetPaintWindow(), &pt);
		}

		::MoveWindow(hwnd
			, pt.x
			, pt.y
			, m_rcItem.right - m_rcItem.left
			, m_rcItem.bottom - m_rcItem.top
			, TRUE);
	}
	else
	{
		m_AfterCreatedCacheTasks.push([this]{ resize(); });
	}
}