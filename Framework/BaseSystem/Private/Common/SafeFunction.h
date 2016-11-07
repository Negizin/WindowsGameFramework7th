/*! =====================================================================================
@file		SafeFunction.h
@brief		解放系フールプルーフ関数
@author		Takuya Kawakami
@date		2016.03.14	新規作成
====================================================================================== */
#pragma once

template <typename T>
inline void SafeRelease(T& ptr) {
	if (ptr) {
		ptr->Release();
		ptr = nullptr;
	}
}
#define SAFE_RELEASE SafeRelease 

template <typename T>
inline void SafeDelete(T& ptr) {
	if (ptr) {
		delete ptr;
		ptr = nullptr;
	}
}
#define SAFE_DELETE SafeDelete  

template <typename T>
inline void SafeDeleteArray(T& ptr) {
	if (ptr) {
		delete[] ptr;
		ptr = nullptr;
	}
}
#define SAFE_DELETE_ARRAY SafeDeleteArray