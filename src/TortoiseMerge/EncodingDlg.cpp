// TortoiseGitMerge - a Diff/Patch program

// Copyright (C) 2013 - TortoiseSVN

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#include "stdafx.h"
#include "EncodingDlg.h"


static CFileTextLines::UnicodeType uctArray[] =
{
	CFileTextLines::ASCII,
	CFileTextLines::UTF16_LE,
	CFileTextLines::UTF16_BE,
	CFileTextLines::UTF32_LE,
	CFileTextLines::UTF32_BE,
	CFileTextLines::UTF8,
	CFileTextLines::UTF8BOM
};

static EOL eolArray[] =
{
	EOL_AUTOLINE,
	EOL_CRLF,
	EOL_LF,
	EOL_CR,
	EOL_LFCR,
	EOL_VT,
	EOL_FF,
	EOL_NEL,
	EOL_LS,
	EOL_PS
};

// CFindDlg dialog

IMPLEMENT_DYNAMIC(CEncodingDlg, CDialog)

CEncodingDlg::CEncodingDlg(CWnd* pParent)
	: CDialog(CEncodingDlg::IDD, pParent)
{
}

CEncodingDlg::~CEncodingDlg()
{
}

void CEncodingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ENCODING, m_Encoding);
	DDX_Control(pDX, IDC_COMBO_EOL, m_EOL);
}


BEGIN_MESSAGE_MAP(CEncodingDlg, CDialog)
END_MESSAGE_MAP()


// CFindDlg message handlers

void CEncodingDlg::OnCancel()
{
	__super::OnCancel();
}

void CEncodingDlg::OnOK()
{
	UpdateData();
	texttype = uctArray[m_Encoding.GetCurSel()];
	lineendings = eolArray[m_EOL.GetCurSel()];
	__super::OnOK();
}

BOOL CEncodingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString sTitle;
	GetWindowText(sTitle);
	sTitle = view + sTitle;
	SetWindowText(sTitle);
	SetDlgItemText(IDC_VIEW, view);

	m_Encoding.AddString(_T("ASCII"));
	m_Encoding.AddString(_T("UTF-16LE"));
	m_Encoding.AddString(_T("UTF-16BE"));
	m_Encoding.AddString(_T("UTF-32LE"));
	m_Encoding.AddString(_T("UTF-32BE"));
	m_Encoding.AddString(_T("UTF-8"));
	m_Encoding.AddString(_T("UTF-8 BOM"));
	int idxtexttype = 0;
	for (int i = 0; i < _countof(uctArray); i++)
	{
		if (texttype == uctArray[i])
		{
			idxtexttype = i;
			break;
		}
	}
	m_Encoding.SetCurSel(idxtexttype);

	m_EOL.AddString(_T("*"));
	m_EOL.AddString(_T("CRLF"));
	m_EOL.AddString(_T("LF"));
	m_EOL.AddString(_T("CR"));
	m_EOL.AddString(_T("LFCR"));
	m_EOL.AddString(_T("VT"));
	m_EOL.AddString(_T("FF"));
	m_EOL.AddString(_T("NEL"));
	m_EOL.AddString(_T("LS"));
	m_EOL.AddString(_T("PS"));
	int idxlineendings = 0;
	for (int i = 0; i < _countof(eolArray); i++)
	{
		if (lineendings == eolArray[i])
		{
			idxlineendings = i;
			break;
		}
	}
	m_EOL.SetCurSel(idxlineendings);

	return FALSE;
}
