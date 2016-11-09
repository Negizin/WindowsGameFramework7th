#include "File.h"
using namespace UT;

namespace {
#define	REGION_FILE_PATH_ANALYZER
#define	REGION_FILE_DIRECTORY
#define	REGION_UT
}


#pragma	region REGION_FILE_PATH_ANALYZER
/*! =====================================================================================
@brief	コンストラクタ
@param	ディレクトリ
====================================================================================== */
FilePathAnalyzer::FilePathAnalyzer(tstring filepath) {
	Analize(filepath);
}

//!ファイルパスを解析する
bool 	FilePathAnalyzer::Analize(tstring filepath) {
	m_filePath = filepath;
	m_extension = FileToExtension(m_filePath);
	m_fullPath = LocalToFullPath(m_filePath);
	m_fileName = PassToFileName(m_filePath);
	m_localDirectory = FileToLocalDirectory(m_filePath);
	m_fullDirectory = LocalToFullPath(m_localDirectory);

	return TRUE;
}

//! ファイル名を取得する
tstring 	FilePathAnalyzer::GetFilePath() {
	return m_filePath;
}

//! ファイルのフルパスを取得する
tstring 	FilePathAnalyzer::GetFullPath() {
	return m_fullPath;
}

//! ファイルの拡張子を取得する
tstring 	FilePathAnalyzer::GetExtension() {
	return m_extension;
}

//! 拡張子を除いたファイル名を取得する
tstring 	FilePathAnalyzer::GetFileName() {
	return m_fileName;
}

//! ローカルディレクトリを取得する
tstring FilePathAnalyzer::GetLocalDirectory() {
	return m_localDirectory;
}

//! フルディレクトリを取得する
tstring FilePathAnalyzer::GetFullDirectory() {
	return m_fullDirectory;
}

#pragma endregion


#pragma	region	REGION_FILE_DIRECTORY
/*! =====================================================================================
@brief	コンストラクタ
@param	ディレクトリ
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
	// 最初に一致するファイルを取得
	HANDLE hFile = ::FindFirstFile((m_directory + _T("*")).c_str(), &tFindFileData);

	if (INVALID_HANDLE_VALUE == hFile) {
		return fileList;
	}
	do {

		tstring filename = tFindFileData.cFileName;

		//! 自身を参照すると無限ループになるので回避
		if (filename == _T(".") || filename == _T(".."))
			continue;

		// フォルダかどうかを判定
		if (tFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			//サブフォルダの検索
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

			// 拡張子が設定されていない場合は全てのファイルを格納
			if (m_extensions.empty())
				fileList.push_back(m_directory + filename);
			else {
				//拡張子が設定されている場合は指定の拡張子のファイルならリストに追加
				for each (auto var in m_extensions)
					if (var == extention) {
						fileList.push_back(m_directory + filename);
						break;
					}
			}
		}

		// 次に一致するファイルの検索
	} while (::FindNextFile(hFile, &tFindFileData));

	// 検索ハンドルを閉じる
	::FindClose(hFile);
	return fileList;
}

#pragma endregion


#pragma	region REGION_UT

//! ファイルパスからファイル名だけを取得
tstring	UT::PassToFileName(tstring str) {
	auto index = str.rfind(_T("/"));

	if (index == tstring::npos)
		index = str.rfind(_T("\\"));

	if (index == tstring::npos)
		return str;

	return str.substr(index + 1, str.size() - 1);
}

//! フルパスの取得
tstring UT::LocalToFullPath(tstring localPath) {
	TCHAR szFullPath[MAX_PATH] = { '\0' };
	TCHAR *szFilePart;

	GetFullPathName(
		localPath.c_str(), /* ファイル名を相対パスで指定 */
		sizeof(szFullPath) / sizeof(szFullPath[0]),
		szFullPath,
		&szFilePart);

	return szFullPath;
}

//! 拡張子の取得
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

//! 文字列をハッシュ値に変換
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