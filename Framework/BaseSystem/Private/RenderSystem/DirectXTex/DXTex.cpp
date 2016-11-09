#include	"DXTex.h"
#include	"DirectXTex.h"
#include	"../Utilities/File/File.h"
#include	<stdlib.h>

#ifdef _DEBUG
#pragma comment(lib,"Debug/DirectXTex.lib")
#else
#pragma comment(lib,"Release/DirectXTex.lib")
#endif
using namespace DirectX;

ID3D11ShaderResourceView* DXTex::LoadFromFile(ID3D11Device* pDev, const TCHAR* filename) {
	HRESULT hr;
	UT::FilePathAnalyzer analize = filename;

	ScratchImage image;

	//char to L char
	setlocale(LC_CTYPE, "jpn");
	std::wstring lChar;
	size_t sz;

#ifdef UNICODE
	lChar = filename;
#else
	mbstowcs_s(&sz, lChar, filename, _TRUNCATE);
#endif // UNICODE

	//tgaファイルかどうか
	if (analize.GetExtension() == _T(".tga")) {
		hr = LoadFromTGAFile(lChar.c_str(), 0, image);
	}
	else if (analize.GetExtension() == _T(".dds")) {
		hr = LoadFromDDSFile(lChar.c_str(), DDS_FLAGS_NONE, nullptr, image);
	}
	else {
		hr = LoadFromWICFile(lChar.c_str(), 0, nullptr, image);
	}

	if (FAILED(hr)) {
		//UT::Log("Texture Load Error \n\t %ws \n", filename);
		return nullptr;
	}

	ID3D11ShaderResourceView* resourceView;
	// 画像からシェーダリソースView DirectXTex
	hr = CreateShaderResourceView(pDev,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&resourceView);
	if (FAILED(hr)) {
		//UT::Log("Texture Load Error \n\t %ws \n", filename);
		return nullptr;
	}

	return resourceView;
}

