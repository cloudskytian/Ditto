#pragma once
#include "afxpropertygridctrl.h"
#include "DialogResizer.h"
#include <afxcoll.h>

class CAdvGeneral : public CDialogEx
{
	DECLARE_DYNAMIC(CAdvGeneral)

public:
	CAdvGeneral(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdvGeneral();

// Dialog Data
	enum { IDD = IDD_ADV_OPTIONS };

	CDialogResizer m_Resize;
	bool m_mouseDownOnCaption;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void AddTrueFalse(CMFCPropertyGridProperty * pGroupTest, CString desc, BOOL value, int settingId);
	void Search(bool fromSelection);

	CEdit m_editFilter;

	afx_msg void OnEnChangeAdvFilter();

	DECLARE_MESSAGE_MAP()
public:
	CMFCPropertyGridCtrl m_propertyGrid;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtCompactAndRepair();
	afx_msg void OnBnClickedButtonCopyScripts();
	afx_msg void OnBnClickedButtonPasteScripts2();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonNextMatch();
};
