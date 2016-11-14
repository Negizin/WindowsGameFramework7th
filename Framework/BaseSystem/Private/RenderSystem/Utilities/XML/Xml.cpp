#include <sstream>
#include <functional>
#include "XML.h"
namespace XmlUT
{
	//========================================================================================
	// string データから　数値の配列を取得します。
	//
	//	型とデータがマッチングしない場合は不正な結果が返ります、
	//
	//　例　Int の配列を取得するときに 0.0などの値が含まれていると不正な結果になり得ます
	//
	//========================================================================================
	template<typename Array>
	static Array ValueToArray4Type(tstring value) {
		Array data;
#ifdef UNICODE
		std::wstringstream	ss(value);
#else
		std::stringstream	ss(value);
#endif // UNICODE
		ss >> data[0] >>
			data[1] >>
			data[2] >>
			data[3];
		return data;
	}

	MyXMLElement* ElementSearchFromChildren(MyXMLElement* elm, tstring name) {
		if (elm == nullptr)
			return nullptr;

		if (elm->GetName() == name)
			return elm;
		auto child = elm->GetFirstChild();
		auto subling = elm->Next();

		if (child) {
			auto res = ElementSearchFromChildren(child, name);
			if (res)return res;
		}

		if (subling) {
			auto res = ElementSearchFromChildren(subling, name);
			if (res)return res;
		}

		return (MyXMLElement*)nullptr;
	};
}

MyXMLAttribute::MyXMLAttribute() :
	m_attribute(nullptr) {

};

//==============================================
//  MyXMLAttribute::GetInt4Value()
//	値をint4つとして解釈し取得します
//==============================================
std::array<int, 4> MyXMLAttribute::GetInt4Value() {
	if (m_attribute == nullptr)
		return std::array<int, 4>();
	return XmlUT::ValueToArray4Type<std::array<int, 4>>(GetStringValue());
}

//==============================================
//  MyXMLAttribute::GetInt3Value()
//	値をint3つとして解釈し取得します
//==============================================
std::array<int, 3> MyXMLAttribute::GetInt3Value() {
	if (m_attribute == nullptr)
		return std::array<int, 3>();
	std::array<int, 4> w(XmlUT::ValueToArray4Type<std::array<int, 4>>(GetStringValue()));

	return std::array<int, 3>() = { { w[0] ,w[1],w[2] } };
}

//==============================================
//  MyXMLAttribute::GetInt2Value()
//	値をint2つとして解釈し取得します
//==============================================
std::array<int, 2> MyXMLAttribute::GetInt2Value() {
	if (m_attribute == nullptr)
		return std::array<int, 2>();
	std::array<int, 4> w(XmlUT::ValueToArray4Type<std::array<int, 4>>(GetStringValue()));

	return std::array<int, 2>() = { { w[0], w[1] } };
}

//==============================================
//  MyXMLAttribute::GetIntValue()
//	値をintとして解釈し取得します
//==============================================
int  MyXMLAttribute::GetIntValue() {
	if (m_attribute == nullptr)
		return 0;
	std::array<int, 4> w(XmlUT::ValueToArray4Type<std::array<int, 4>>(GetStringValue()));

	return w[0];
}

//==============================================
//  MyXMLAttribute::GetFloat4Value()
//	値をFloat4つとして解釈し取得します
//==============================================
std::array<float, 4> MyXMLAttribute::GetFloat4Value() {
	if (m_attribute == nullptr)
		return std::array<float, 4>();
	return XmlUT::ValueToArray4Type<std::array<float, 4>>(GetStringValue());
}

//==============================================
//  MyXMLAttribute::GetFloat3Value()
//	値をFloat3つとして解釈し取得します
//==============================================
std::array<float, 3> MyXMLAttribute::GetFloat3Value() {
	if (m_attribute == nullptr)
		return std::array<float, 3>();

	std::array<float, 4> w(XmlUT::ValueToArray4Type<std::array<float, 4>>(GetStringValue()));

	return std::array<float, 3>() = { {w[0],w[1],w[2]} };
}

//==============================================
//  MyXMLAttribute::GetFloat2Value()
//	値をFloat2つとして解釈し取得します
//==============================================
std::array<float, 2> MyXMLAttribute::GetFloat2Value() {
	if (m_attribute == nullptr)
		return std::array<float, 2>();
	std::array<float, 4> w(XmlUT::ValueToArray4Type<std::array<float, 4>>(GetStringValue()));

	return std::array<float, 2>() = { {w[0],w[1]} };
}

//==============================================
//  MyXMLAttribute::GetFloatValue()
//	値をFloatとして解釈し取得します
//==============================================
float	 MyXMLAttribute::GetFloatValue() {
	if (m_attribute == nullptr)
		return 0;

	std::array<float, 4> w(XmlUT::ValueToArray4Type<std::array<float, 4>>(GetStringValue()));

	return w[0];
}

//==============================================
//  MyXMLAttribute::GetStringValue()
//	値をStringとして解釈し取得します
//==============================================
tstring MyXMLAttribute::GetStringValue() {
	if (m_attribute == nullptr)
		return _T("nullptr");

#ifdef UNICODE
	return StringToWString(m_attribute->Value());
#else
	return m_attribute->Value();
#endif	//UNICODE
}

//==============================================
//  MyXMLAttribute::GetBoolValue()
//	値をBoolとして解釈し取得します
//==============================================
bool MyXMLAttribute::GetBoolValue() {
	if (m_attribute == nullptr)
		return false;
	return m_attribute->BoolValue();
}

MyXMLElement::MyXMLElement() :
	m_element(nullptr),
	m_firstChild(nullptr),
	m_pParent(nullptr),
	m_subling(nullptr) {
	m_attributeList.reserve(32);
};

MyXMLElement::~MyXMLElement() {
	SafeDelete(m_subling);
	SafeDelete(m_firstChild);

	for (auto it : m_attributeList)
		SafeDelete(it);
}



//==============================================
//  MyXMLElement::GetTextData()
//	エレメントをテキストとしてすべて取得します
//==============================================
tstring MyXMLElement::GetTextData() {
	if (m_element == nullptr)
		return _T("nullptr");
#ifdef UNICODE
	return StringToWString(m_element->GetText());
#else
	return m_element->GetText();
#endif	//UNICODE
}

//==============================================
//  MyXMLElement::GetName()
//	エレメントの名前を取得します
//==============================================
tstring MyXMLElement::GetName() {
	return m_name;
}

//==============================================
//  子エレメントを取得します。
//	無い場合はnullが返ります。
//==============================================
MyXMLElement* MyXMLElement::GetFirstChild() {
	if (m_element == nullptr)
		return nullptr;
	return m_firstChild;
}

bool MyXMLElement::SetElement(tinyxml2::XMLElement* elm) {
	m_element = elm;

#ifdef UNICODE
	m_name = StringToWString(elm->Name());
	std::string _work = elm->GetText() != nullptr ? elm->GetText() : "";
	m_data = StringToWString(_work);
#else
	m_name = elm->Name();
	m_data = elm->GetText() != nullptr ? elm->GetText() : "";
#endif //UNICODE

	auto attribute = m_element->FirstAttribute();

	while (attribute != nullptr) {
		MyXMLAttribute* a = new MyXMLAttribute;
		a->m_attribute = (tinyxml2::XMLAttribute*)attribute;
		m_attributeList.push_back(a);
		attribute = attribute->Next();
	}

	return true;
}

//==============================================
//  子エレメントを名前で取得
//==============================================
MyXMLElement* MyXMLElement::FindChild(const tstring& name) {
	return XmlUT::ElementSearchFromChildren(m_firstChild, name);
}

MyXMLElement* MyXMLElement::FindChildForAttribute(const tstring& attribute, tstring value) {

	std::function<MyXMLElement*(MyXMLElement*, tstring)>  Search = [&](MyXMLElement* elm, tstring name) {
		auto at = elm->GetAttribute(attribute);

		if (at != nullptr && at->GetStringValue() == name) {
			return elm;
		}
		if (at) {
			tstring atc;
			atc = at->GetStringValue();
		}

		auto child = elm->GetFirstChild();
		auto subling = elm->Next();

		if (child) {
			auto res = Search(child, name);
			if (res)return res;
		}

		if (subling) {
			auto res = Search(subling, name);
			if (res)return res;
		}

		return (MyXMLElement*)nullptr;
	};

	return Search(this, value);
}

//==============================================
//  attributeを取得
//==============================================
MyXMLAttribute* MyXMLElement::GetAttribute(const tstring& name) {
	for each (auto var in m_attributeList) {
#ifdef UNICODE
		if (name == StringToWString(var->m_attribute->Name()))
			return var;
#else
		if (name == var->m_attribute->Name())
			return var;
#endif
	}
	return nullptr;
}


//==============================================
//  同階層の次のエレメントを取得します。
//	無い場合はnullが返ります。
//==============================================
MyXMLElement* MyXMLElement::Next() {
	return m_subling;
}

//==============================================
//  MyXMLElement::TsXML()
//	constructor
//==============================================
XML::XML()
	:m_rootNode(nullptr) {

};

XML::XML(const tstring& filename) {
	XML::XML();
	LoadXML(filename);
}

bool XML::LoadXML(const tstring& filename) {

#ifdef UNICODE
	if (m_docment.LoadFile(WStringToString(filename.c_str()).c_str()) != tinyxml2::XMLError::XML_SUCCESS)
		return false;
#else
	if (m_docment.LoadFile(filename.c_str()) != tinyxml2::XMLError::XML_SUCCESS)
		return false;
#endif

	m_rootNode = new MyXMLElement;
	m_rootNode->SetElement(m_docment.RootElement());

	std::function<void(MyXMLElement*)> CreateTree = [&](MyXMLElement* tselm) {
		if (tselm == nullptr || tselm->m_element == nullptr)
			return;

		tinyxml2::XMLElement* child = tselm->m_element->FirstChildElement();
		if (child != nullptr) {
			tselm->m_firstChild = new MyXMLElement;
			tselm->m_firstChild->SetElement(child);
			tselm->m_firstChild->m_pParent = tselm;
			CreateTree(tselm->m_firstChild);
		}

		tinyxml2::XMLElement* sub = tselm->m_element->NextSiblingElement();
		if (sub != nullptr) {
			tselm->m_subling = new MyXMLElement;
			tselm->m_subling->SetElement(sub);
			CreateTree(tselm->m_subling);
		}
	};
	CreateTree(m_rootNode);

	return true;
}

XML::~XML() {
	SafeDelete(m_rootNode);
}

MyXMLElement* XML::GetRootNode() {
	return m_rootNode;
}

MyXMLElement* XML::FindFirst(const tstring& name) {
	return XmlUT::ElementSearchFromChildren(m_rootNode, name);
}

bool XML::SaveXml(const tstring& filename) {

#ifdef UNICODE
	if (m_docment.SaveFile(WStringToString(filename.c_str()).c_str(), true) != tinyxml2::XMLError::XML_SUCCESS) {
		//DebugLog("%s.xmlファイルの書き出しに失敗\n", filename.c_str());
		return false;
	}
#else
	if (m_docment.SaveFile(filename.c_str(), true) != tinyxml2::XMLError::XML_SUCCESS) {
		//DebugLog("%s.xmlファイルの書き出しに失敗\n", filename.c_str());
		return false;
	}
#endif
	return true;
}