#include	"MaterialBase.h"
#include	"../DX11Device/DX11Device.h"
#include	"../DX11Device/DeviceContext.h"
#include	"../DirectXTex/DXTex.h"

#include <locale>


inline const std::wstring StringToWString(std::string oString) {
	// SJIS → wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str()
		, -1, (wchar_t*) NULL, 0);

	// バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	// SJIS → wstring
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2
		, iBufferSize);

	// stringの生成
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	// バッファの破棄
	delete[] cpUCS2;

	// 変換結果を返す
	return(oRet);
}


MaterialBase::MaterialBase() :
	m_pTexture(nullptr),
	m_isUpdate(FALSE) {
}

MaterialBase::~MaterialBase() {
	SafeDelete(m_pTexture);
}

bool MaterialBase::ApplyMaterial(DeviceContext* context) {
	(void) context;
	return TRUE;
}

bool MaterialBase::CreateMaterial(DX11Device * pDev) {
	(void) pDev;
	return TRUE;
}

bool MaterialBase::UpdateMaterial(DeviceContext* context) {
	(void) context;
	return TRUE;
}

bool MaterialBase::LoadTextureFromFile(DX11Device* pDev) {
	m_pTexture = new Texture2D;
	m_pTexture->SetName(m_textureName);

	// Char To LChar
	setlocale(LC_CTYPE, "jpn");
	wchar_t lChar[255];
	size_t sz;


#ifdef UNICODE

#else
	mbstowcs_s(&sz, lChar, m_name.c_str(), _TRUNCATE);
#endif // UNICODE


	ID3D11ShaderResourceView* pSRV = DXTex::LoadFromFile(pDev->GetDevD3D(), m_textureName.c_str());
	if (pSRV)
		m_pTexture->SetSRV(pSRV);
	else
		return FALSE;

	return TRUE;
}

Texture2D* MaterialBase::GetTexture()const {
	return m_pTexture;
}

bool MaterialBase::SetTexture(Texture2D *pTex) {
	if (m_pTexture)
		return false;
	m_pTexture = pTex;
	return true;
}