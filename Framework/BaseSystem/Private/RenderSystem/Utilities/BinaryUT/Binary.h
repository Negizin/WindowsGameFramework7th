//!*******************************************************
//!	TsBinaryFile.h
//!
//!	Binary Loader.
//!

#pragma once
#include	"../NameObject/NameObject.h"

class Binary : public NameObject
{
public:

	//! Constructor
	Binary();
	Binary(const Binary& bin);
	Binary(tstring filename);

	//! Destructor
	virtual~Binary();

	//=================================================
	// Load
	// バイナリファイルを読み込む
	// @pram filename	読み込み対象のバイナリのファイルパス
	// @return true is Success
	bool Load(tstring filename);

	//=================================================
	// UnLoad
	// バイナリファイルを開放する。このメソッドは明示的に呼ぶ
	//　必要はない。
	// @pram filename	読み込み対象のバイナリのファイルパス
	// @return true is Success
	void UnLoad();

	//=================================================
	// GetBinary
	// バイナリソースデータを取得する
	// @return Binary Pointer
	unsigned char* GetBinary()const;

	//=================================================
	// GetBinary
	// バイナリソースデータを取得する
	// @return Binary Pointer
	int	GetSize()const;

	//=================================================
	// コピーを行う際は新たなメモリの確保が行われる。
	Binary operator = (const Binary& bin);
protected:
	unsigned char * m_bin;
	int    m_size;
};