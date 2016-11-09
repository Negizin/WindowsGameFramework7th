#include "../../../Extren/DirectXTex/DirectXTex.h"
#include "DXTex.h"
#include "../../UT/Debug/DebugLog.h"
#include "../../UT/helper.h"

#ifdef _DEBUG
#pragma comment(lib,"Debug/DirectXTex.lib")
#else
#pragma comment(lib,"Release/DirectXTex.lib")
#endif
using namespace DirectX;

ID3D11ShaderResourceView* DXTex::LoadFromFile(ID3D11Device* pDev, const char* filename)
{
	HRESULT hr;
	UT::FilePathAnalyzer analize = filename;

	ScratchImage image;

	//char to L char
	setlocale(LC_CTYPE, "jpn");
	wchar_t lChar[255];
	size_t sz;

	mbstowcs_s(&sz, lChar, filename, _TRUNCATE);

	//tgaファイルかどうか
	if (analize.GetExtension()==".tga"){
		hr = LoadFromTGAFile(lChar, 0, image);
	}
	else if (analize.GetExtension() == ".dds"){
		hr = LoadFromDDSFile(lChar, DDS_FLAGS_NONE, nullptr, image);
	}
	else{
		hr = LoadFromWICFile(lChar, 0,nullptr, image);
	}
	
	if (FAILED(hr))
	{
		UT::Log("Texture Load Error \n\t %ws \n", filename);
		return nullptr;
	}
	
	ID3D11ShaderResourceView* resourceView;
	// 画像からシェーダリソースView DirectXTex
	hr = CreateShaderResourceView(pDev,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&resourceView);
	if (FAILED(hr))
	{
		UT::Log("Texture Load Error \n\t %ws \n", filename);
		return nullptr;
	}

	return resourceView;
}

