#include "stdafx.h"
#include "ChaiScriptXml.h"
#include "tinyxml\tinyxml.h"
#include "..\Shared\TextConvert.h"
#include "Misc.h"
#include "ActionEnums.h"


CChaiScriptXml::CChaiScriptXml()
{
	m_assignedGuidOnLoad = false;
}


CChaiScriptXml::~CChaiScriptXml()
{
}

CString CChaiScriptXml::GetScript(CString name, BOOL &active)
{
	CString script;
	for (auto & listItem : m_list)
	{
		if (listItem.m_name == name)
		{
			active = listItem.m_active;
			script = listItem.m_name;
			break;
		}
	}

	return script;
}

void CChaiScriptXml::Load(CString values)
{
	m_assignedGuidOnLoad = false;
	m_list.clear();
	
	TiXmlDocument doc;
	CStringA xmlA = CTextConvert::UnicodeToUTF8(values);
	doc.Parse(xmlA);

	TiXmlElement *ItemHeader = doc.FirstChildElement("ChaiScripts");

	if (ItemHeader != NULL)
	{
		TiXmlElement *ItemElement = ItemHeader->FirstChildElement();

		while (ItemElement)
		{
			CDittoChaiScriptXmlItem array_item;
			ItemElement->Attribute("active", &array_item.m_active);
			array_item.m_name = ItemElement->Attribute("name");
			array_item.m_description = ItemElement->Attribute("description");
			array_item.m_script = ItemElement->Attribute("script");
			array_item.m_guid = ItemElement->Attribute("guid");
			array_item.m_version = ItemElement->Attribute("vesion");

			if (array_item.m_guid == "")
			{
				array_item.m_guid = NewGuidString();
				m_assignedGuidOnLoad = true;
			}

			m_list.push_back(array_item);

			ItemElement = ItemElement->NextSiblingElement();
		}
	}
}

CString CChaiScriptXml::Save()
{
	m_assignedGuidOnLoad = false;
	TiXmlDocument doc;

	TiXmlElement* friendOuter = new TiXmlElement("ChaiScripts");
	doc.LinkEndChild(friendOuter);

	for (auto & listItem : m_list)
	{
		TiXmlElement* friendElement = new TiXmlElement("ChaiScriptItem");

		friendElement->SetAttribute("active", listItem.m_active);

		CStringA name = CTextConvert::UnicodeToUTF8(listItem.m_name);
		friendElement->SetAttribute("name", name);

		CStringA desc = CTextConvert::UnicodeToUTF8(listItem.m_description);
		friendElement->SetAttribute("description", desc);

		CStringA script = CTextConvert::UnicodeToUTF8(listItem.m_script);
		friendElement->SetAttribute("script", script);

		CStringA guid = CTextConvert::UnicodeToUTF8(listItem.m_guid);
		friendElement->SetAttribute("guid", guid);

		CStringA version = CTextConvert::UnicodeToUTF8(listItem.m_version);
		friendElement->SetAttribute("version", version);

		friendOuter->LinkEndChild(friendElement);
	}

	TiXmlPrinter printer;
	printer.SetLineBreak("");
	doc.Accept(&printer);
	CString cs = printer.CStr();

	return cs;
}

void CChaiScriptXml::AddToMenu(CMenu *pMenu, CAccels *actions)
{
	if (m_list.size() > 0)
	{
		pMenu->AppendMenu(MF_SEPARATOR);

		bool addedItem = false;
		int id = 0;
		for (auto & element : m_list)
		{
			if (addedItem == false)
			{
				addedItem = true;
			}

			CString cs;
			if (element.m_description != _T(""))
			{
				cs.Format(_T("(%s) - %s"), element.m_name, element.m_description);
			}
			else
			{
				cs.Format(_T("%s"), element.m_name);
			}

			if (actions != NULL)
			{
				CString shortcutText = actions->GetCmdKeyText(ActionEnums::PASTE_SCRIPT, element.m_guid);
				if (shortcutText != _T(""))
				{
					cs += "\t";
					cs += shortcutText;
				}
			}

			pMenu->AppendMenuW(MF_STRING, (ChaiScriptMenuStartId + id), cs);
			id++;

			if (id > MaxChaiScripts)
			{
				break;
			}
		}
	}
}