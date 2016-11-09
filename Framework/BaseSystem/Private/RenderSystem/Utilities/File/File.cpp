#include "File.h"
using namespace UT;

namespace {
#define	REGION_FILE_PATH_ANALYZER
#define	REGION_FILE_DIRECTORY
#define	REGION_UT
}


#pragma	region REGION_FILE_PATH_ANALYZER
/*! =====================================================================================
@brief	�R���X�g���N�^
@param	�f�B���N�g��
====================================================================================== */
FilePathAnalyzer::FilePathAnalyzer(tstring filepath) {
	Analize(filepath);
}

//!�t�@�C���p�X����͂���
bool 	FilePathAnalyzer::Analize(tstring filepath) {
	m_filePath = filepath;
	m_extension = FileToExtension(m_filePath);
	m_fullPath = LocalToFullPath(m_filePath);
	m_fileName = PassToFileName(m_filePath);
	m_localDirectory = FileToLocalDirectory(m_filePath);
	m_fullDirectory = LocalToFullPath(m_localDirectory);

	return TRUE;
}

//! �t�@�C�������擾����
tstring 	FilePathAnalyzer::GetFilePath() {
	return m_filePath;
}

//! �t�@�C���̃t���p�X���擾����
tstring 	FilePathAnalyzer::GetFullPath() {
	return m_fullPath;
}

//! �t�@�C���̊g���q���擾����
tstring 	FilePathAnalyzer::GetExtension() {
	return m_extension;
}

//! �g���q���������t�@�C�������擾����
tstring 	FilePathAnalyzer::GetFileName() {
	return m_fileName;
}

//! ���[�J���f�B���N�g�����擾����
tstring FilePathAnalyzer::GetLocalDirectory() {
	return m_localDirectory;
}

//! �t���f�B���N�g�����擾����
tstring FilePathAnalyzer::GetFullDirectory() {
	return m_fullDirectory;
}

#pragma endregion


#pragma	region	REGION_FILE_DIRECTORY
/*! =====================================================================================
@brief	�R���X�g���N�^
@param	�f�B���N�g��
====================================================================================== */
FileDirectory::FileDirectory(tstring directory) :
	m_searchSubFolder(TRUE) {
	if (directory.empty())
		return;
	m_directory = directory;
	if (m_directory[m_directory.size() - 1] != '/' &&
		m_directory[m_directory.size() - 1] != '\\')
		m_directory += '/';
}

void FileDirectory::SetSearchSubFolderFlag(bool searchSubFolder) {
	m_searchSubFolder = searchSubFolder;
}
bool FileDirectory::AddExtension(tstring& extencion) {
	m_extensions.push_back(extencion);
	return TRUE;
}
bool FileDirectory::RemoveExtension(tstring& extencion) {
	m_extensions.remove(extencion);
	return TRUE;
}
std::list<tstring> FileDirectory::GetFileList() {
	std::list<tstring> fileList;
	WIN32_FIND_DATA tFindFileData;
	// �ŏ��Ɉ�v����t�@�C�����擾
	HANDLE hFile = ::FindFirstFile((m_directory + _T("*")).c_str(), &tFindFileData);

	if (INVALID_HANDLE_VALUE == hFile) {
		return fileList;
	}
	do {

		tstring filename = tFindFileData.cFileName;

		//! ���g���Q�Ƃ���Ɩ������[�v�ɂȂ�̂ŉ��
		if (filename == _T(".") || filename == _T(".."))
			continue;

		// �t�H���_���ǂ����𔻒�
		if (tFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			//�T�u�t�H���_�̌���
			if (m_searchSubFolder == FALSE)
				continue;

			FileDirectory subfolder(m_directory + filename);
			subfolder.SetSearchSubFolderFlag(TRUE);
			for each (auto var in m_extensions)
				subfolder.AddExtension(var);

			std::list<tstring>&& subFolderFiles = subfolder.GetFileList();
			for each (auto var in subFolderFiles)
				fileList.push_back(var);
		}
		else {
			tstring extention = UT::FileToExtension(filename);

			// �g���q���ݒ肳��Ă��Ȃ��ꍇ�͑S�Ẵt�@�C�����i�[
			if (m_extensions.empty())
				fileList.push_back(m_directory + filename);
			else {
				//�g���q���ݒ肳��Ă���ꍇ�͎w��̊g���q�̃t�@�C���Ȃ烊�X�g�ɒǉ�
				for each (auto var in m_extensions)
					if (var == extention) {
						fileList.push_back(m_directory + filename);
						break;
					}
			}
		}

		// ���Ɉ�v����t�@�C���̌���
	} while (::FindNextFile(hFile, &tFindFileData));

	// �����n���h�������
	::FindClose(hFile);
	return fileList;
}

#pragma endregion


#pragma	region REGION_UT

//! �t�@�C���p�X����t�@�C�����������擾
tstring	UT::PassToFileName(tstring str) {
	auto index = str.rfind(_T("/"));

	if (index == tstring::npos)
		index = str.rfind(_T("\\"));

	if (index == tstring::npos)
		return str;

	return str.substr(index + 1, str.size() - 1);
}

//! �t���p�X�̎擾
tstring UT::LocalToFullPath(tstring localPath) {
	TCHAR szFullPath[MAX_PATH] = { '\0' };
	TCHAR *szFilePart;

	GetFullPathName(
		localPath.c_str(), /* �t�@�C�����𑊑΃p�X�Ŏw�� */
		sizeof(szFullPath) / sizeof(szFullPath[0]),
		szFullPath,
		&szFilePart);

	return szFullPath;
}

//! �g���q�̎擾
tstring UT::FileToExtension(tstring str) {
	auto index = str.rfind('.');
	if (index == tstring::npos)
		return _T("");
	return str.substr(str.rfind('.'), str.size() - 1);
}

//! 
tstring UT::FileToLocalDirectory(tstring str) {
	auto index = str.rfind(_T("/"));

	if (index == tstring::npos)
		index = str.rfind(_T("\\"));

	if (index == tstring::npos)
		return str;

	return str.substr(0, index + 1);
}

//! ��������n�b�V���l�ɕϊ�
HASH  UT::StringToHash(tstring str) {
	HASH h = 0;
	const TCHAR* val = str.c_str();
	int len = str.length();

	for (int i = 0; i < len; i++) {
		h = 31 * h + val[i];
	}
	return h;
}

#pragma endregion