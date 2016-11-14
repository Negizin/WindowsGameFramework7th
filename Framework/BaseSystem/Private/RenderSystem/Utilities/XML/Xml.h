/*! =====================================================================================
@file		Xml.h
@brief		XmlPerser��Lapper
@author
@date		2016.11.09	�ŏI�X�V
====================================================================================== */
#pragma once
#include	"../../../../Public/Common/Common.h"
#include	 "tiny\tinyxml2.h"
#include	 <string>
#include	 <array>
#include	 <vector>

//==================================================
//! xml �A�g���r���[�g
//==================================================
class MyXMLAttribute {
	friend class MyXMLElement;
public:
	MyXMLAttribute();
	//==================================================
	//	�e�L�X�g�f�[�^��K���ȃf�[�^�ɕϊ����擾���܂��B
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
//! xml �G�������g
//==================================================
class MyXMLElement {
	friend class XML;
public:

	//! �R���X�g���N�^
	MyXMLElement();
	//! �f�X�g���N�^
	virtual ~MyXMLElement();

	//! �e�L�X�g�u���b�N���擾
	tstring	  GetTextData();
	//! �G�������g�̖��O���擾
	tstring	  GetName();

	//! ���̃G�������g���擾
	MyXMLElement* Next();

	//! ���q�̃G�������g���擾
	MyXMLElement* GetFirstChild();

	//! �G�������g�𖼑O�Ō������A�擾����
	MyXMLElement* FindChild(const tstring& name);

	//! �q�G�������g����������
	//  �w�肳�ꂽ�A�g�����r���[�g�������G�������g�����݂����̃f�[�^�v�f��value�ł���
	//	�q�G�������g���擾����
	MyXMLElement* FindChildForAttribute(const tstring& attributeName, tstring value);

	//! �w�肳�ꂽ���O�����A�g���r���[�g���擾����
	MyXMLAttribute* GetAttribute(const tstring& name);
private:
	tstring m_name;							//! �G�������g�̖��O
	tstring m_data;							//! �G�������g����������e�L�X�g�f�[�^
	std::vector<MyXMLAttribute*> m_attributeList;	//! �A�g���r���[�g�̃��X�g

	MyXMLElement*		  m_pParent;				//! �e�G�������g
	MyXMLElement*		  m_subling;			//! �Z��G�������g
	MyXMLElement*		  m_firstChild;			//! ���q�G�������g

	tinyxml2::XMLElement* m_element;			//! tinyxml2�̖{��
private:
	bool SetElement(tinyxml2::XMLElement*);	//! tinyxml2�̃f�[�^��ݒ肷��
};

//==================================================
//! xml �t�@�C���f�[�^
//==================================================
class XML {
	friend class MyXMLElement;
public:
	//! �R���X�g���N�^
	XML();
	XML(const tstring&  filename);

	//�f�X�g���N�^
	virtual ~XML();

	//! XML��ǂݍ���
	bool LoadXML(const tstring& filename);

	//! ���[�g�̃G�������g���擾����
	MyXMLElement* GetRootNode();

	//! ���O�Ō������ŏ��Ɍ��������G�������g���擾����
	MyXMLElement* FindFirst(const tstring& name);

	//! XML�f�[�^��ۑ�����B
	//  todo ������
	bool SaveXml(const tstring& filename);

private:
	tinyxml2::XMLDocument m_docment;	// tinyxml2�̖{��
	MyXMLElement* m_rootNode;			// ���[�g�G�������g
};
