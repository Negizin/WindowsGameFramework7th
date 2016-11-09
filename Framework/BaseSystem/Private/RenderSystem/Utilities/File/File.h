/*! =====================================================================================
@file		File.h
@brief		�t�@�C������n���[�e�B���e�B
@author
@date		2016.11.09	�ŏI�X�V
====================================================================================== */
#pragma once
#include	"../../../../Public/Common/Common.h"
#include <string>
#include <list>

typedef unsigned long long HASH;

namespace UT {
	class FilePathAnalyzer {
	public:
		FilePathAnalyzer(tstring filepass);

		//!�t�@�C���p�X����͂���
		bool Analize(tstring str);

		//! �t�@�C�������擾����
		tstring GetFilePath();

		//! �t�@�C���̃t���p�X���擾����
		tstring GetFullPath();

		//! �t�@�C���̊g���q���擾����
		tstring GetExtension();

		//! �g���q���������t�@�C�������擾����
		tstring GetFileName();

		//! ���[�J���f�B���N�g�����擾����
		tstring GetLocalDirectory();

		//! �t���f�B���N�g�����擾����
		tstring GetFullDirectory();
	protected:
		tstring m_filePath;
		tstring m_fullPath;
		tstring m_extension;
		tstring m_fileName;
		tstring m_localDirectory;
		tstring m_fullDirectory;
	};

	class FileDirectory {
	public:
		//! Constructor
		FileDirectory(tstring directory);

		//! �T�u�t�H���_�������ΏۂɊ܂߂�H
		// TRUE		�܂߂�
		// FALSE	�܂߂Ȃ�
		void SetSearchSubFolderFlag(bool searchSubFolder);

		//! ��������g���q��ǉ�
		bool AddExtension(tstring& extencion);

		//! ��������g���q���폜
		bool RemoveExtension(tstring& extencion);

		//! ���ׂẴt�@�C���p�X���擾����
		std::list<tstring> GetFileList();
	protected:
		tstring m_directory;
		std::list<tstring> m_extensions;
		bool m_searchSubFolder;
	};

	namespace Resource
	{
		//! ���\�[�X�t�@�C�����i�[����Ă���p�X���擾
		inline tstring GetResourceDirectory() {
			return _T("Resource/");
		}

		//! RenderSystem���i�[����Ă���p�X���擾
		inline tstring GetRenderSystemDirectory() {
			return GetResourceDirectory() + _T("RenderSystem/");
		}

		//! �o�C�i���V�F�[�_���i�[����Ă���p�X���擾
		inline tstring GetCSODirectory() {
			return GetResourceDirectory() + _T("Shader/");
		}

		//! �V�F�[�_�p�X���i�[����Ă���p�X���擾
		inline tstring GetShaderPackageDirectory() {
			return GetResourceDirectory() + _T("ShaderPackage/");
		}


		//! �V�F�[�_�t���[���i�[����Ă���p�X���擾
		inline tstring GetShaderFlowDirectory() {
			return GetResourceDirectory() + _T("ShaderFlow/");
		}

		//! �V�F�[�_���\�[�X���i�[����Ă���p�X���擾
		inline tstring GetShaderResourceDirectory() {
			return GetResourceDirectory() + _T("ShaderResource/");
		}
	}

	//! �t�@�C���p�X����t�@�C�����������擾
	tstring PassToFileName(tstring str);
	//! �t���p�X�̎擾
	tstring LocalToFullPath(tstring localPath);
	//! �g���q�̎擾
	tstring FileToExtension(tstring str);
	//! 
	tstring FileToLocalDirectory(tstring str);
	//! ��������n�b�V���l�ɕϊ�
	HASH  StringToHash(tstring str);
}