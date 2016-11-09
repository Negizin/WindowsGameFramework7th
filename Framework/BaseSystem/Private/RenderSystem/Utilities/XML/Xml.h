/*! =====================================================================================
@file		Xml.h
@brief		XmlPerserのLapper
@author
@date		2016.11.09	最終更新
====================================================================================== */
#pragma once
#include	"../../../../Public/Common/Common.h"
#include	 "tiny\tinyxml2.h"
#include	 <string>
#include	 <array>
#include	 <vector>

//==================================================
//! xml アトリビュート
//==================================================
class MyXMLAttribute {
	friend class MyXMLElement;
public:
	MyXMLAttribute();
	//==================================================
	//	テキストデータを適正なデータに変換し取得します。
	//==================================================
	std::array<int, 4> GetInt4Value();
	std::array<int, 3> GetInt3Value();
	std::array<int, 2> GetInt2Value();
	int  GetIntValue();

	std::array<float, 4> GetFloat4Value();
	std::array<float, 3> GetFloat3Value();
	std::array<float, 2> GetFloat2Value();
	float	 GetFloatValue();
	bool	 GetBoolValue();

	tstring GetStringValue();
private:
	tinyxml2::XMLAttribute* m_attribute;
};

//==================================================
//! xml エレメント
//==================================================
class MyXMLElement {
	friend class XML;
public:

	//! コンストラクタ
	MyXMLElement();
	//! デストラクタ
	virtual ~MyXMLElement();

	//! テキストブロックを取得
	tstring	  GetTextData();
	//! エレメントの名前を取得
	tstring	  GetName();

	//! 次のエレメントを取得
	MyXMLElement* Next();

	//! 第一子のエレメントを取得
	MyXMLElement* GetFirstChild();

	//! エレメントを名前で検索し、取得する
	MyXMLElement* FindChild(const tstring& name);

	//! 子エレメントを検索する
	//  指定されたアトリュビュート名を持つエレメントが存在しそのデータ要素がvalueである
	//	子エレメントを取得する
	MyXMLElement* FindChildForAttribute(const tstring& attributeName, tstring value);

	//! 指定された名前を持つアトリビュートを取得する
	MyXMLAttribute* GetAttribute(const tstring& name);
private:
	tstring m_name;							//! エレメントの名前
	tstring m_data;							//! エレメントが所持するテキストデータ
	std::vector<MyXMLAttribute*> m_attributeList;	//! アトリビュートのリスト

	MyXMLElement*		  m_parent;				//! 親エレメント
	MyXMLElement*		  m_subling;			//! 兄弟エレメント
	MyXMLElement*		  m_firstChild;			//! 第一子エレメント

	tinyxml2::XMLElement* m_element;			//! tinyxml2の本体
private:
	bool SetElement(tinyxml2::XMLElement*);	//! tinyxml2のデータを設定する
};

//==================================================
//! xml ファイルデータ
//==================================================
class XML {
	friend class MyXMLElement;
public:
	//! コンストラクタ
	XML();
	XML(const tstring&  filename);

	//デストラクタ
	virtual ~XML();

	//! XMLを読み込む
	bool LoadXML(const tstring& filename);

	//! ルートのエレメントを取得する
	MyXMLElement* GetRootNode();

	//! 名前で検索し最初に見つかったエレメントを取得する
	MyXMLElement* FindFirst(const tstring& name);

	//! XMLデータを保存する。
	//  todo 未実装
	bool SaveXml(const tstring& filename);

private:
	tinyxml2::XMLDocument m_docment;	// tinyxml2の本体
	MyXMLElement* m_rootNode;			// ルートエレメント
};
