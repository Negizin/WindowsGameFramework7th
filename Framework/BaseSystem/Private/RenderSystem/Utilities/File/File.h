/*! =====================================================================================
@file		File.h
@brief		ファイル操作系ユーティリティ
@author
@date		2016.11.09	最終更新
====================================================================================== */
#pragma once
#include	"../../../../Public/Common/Common.h"
#include	"../../../Common/TCHARString.h"	//なぜかCommon.hの内容が反映されないので
#include	"../../../Common/DebugNew.h"	//なぜかCommon.hの内容が反映されないので
#include	"../../../Common/SafeFunction.h"//なぜかCommon.hの内容が反映されないので
#include <string>
#include <list>

typedef unsigned long long HASH;

namespace UT {
	class FilePathAnalyzer {
	public:
		FilePathAnalyzer(tstring filepass);

		//!ファイルパスを解析する
		bool Analize(tstring str);

		//! ファイル名を取得する
		tstring GetFilePath();

		//! ファイルのフルパスを取得する
		tstring GetFullPath();

		//! ファイルの拡張子を取得する
		tstring GetExtension();

		//! 拡張子を除いたファイル名を取得する
		tstring GetFileName();

		//! ローカルディレクトリを取得する
		tstring GetLocalDirectory();

		//! フルディレクトリを取得する
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

		//! サブフォルダを検索対象に含める？
		// TRUE		含める
		// FALSE	含めない
		void SetSearchSubFolderFlag(bool searchSubFolder);

		//! 検索する拡張子を追加
		bool AddExtension(tstring& extencion);

		//! 検索する拡張子を削除
		bool RemoveExtension(tstring& extencion);

		//! すべてのファイルパスを取得する
		std::list<tstring> GetFileList();
	protected:
		tstring m_directory;
		std::list<tstring> m_extensions;
		bool m_searchSubFolder;
	};

	namespace Resource
	{
		//! リソースファイルが格納されているパスを取得
		inline tstring GetResourceDirectory() {
			return _T("Resource/");
		}

		//! RenderSystemが格納されているパスを取得
		inline tstring GetRenderSystemDirectory() {
			return GetResourceDirectory() + _T("RenderSystem/");
		}

		//! バイナリシェーダが格納されているパスを取得
		inline tstring GetCSODirectory() {
			return GetResourceDirectory() + _T("Shader/");
		}

		//! シェーダパスが格納されているパスを取得
		inline tstring GetShaderPackageDirectory() {
			return GetResourceDirectory() + _T("ShaderPackage/");
		}


		//! シェーダフローが格納されているパスを取得
		inline tstring GetShaderFlowDirectory() {
			return GetResourceDirectory() + _T("ShaderFlow/");
		}

		//! シェーダリソースが格納されているパスを取得
		inline tstring GetShaderResourceDirectory() {
			return GetResourceDirectory() + _T("ShaderResource/");
		}
	}

	//! ファイルパスからファイル名だけを取得
	tstring PassToFileName(tstring str);
	//! フルパスの取得
	tstring LocalToFullPath(tstring localPath);
	//! 拡張子の取得
	tstring FileToExtension(tstring str);
	//! 
	tstring FileToLocalDirectory(tstring str);
	//! 文字列をハッシュ値に変換
	HASH  StringToHash(tstring str);
}