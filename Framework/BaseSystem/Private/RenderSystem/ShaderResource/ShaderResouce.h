/*! =====================================================================================
@file		ShaderResource.h
@brief		The class is Shader Resource( Texture,CBuffer...etc) base.
@author		
@date		
====================================================================================== */
#pragma once

class ShaderResource {
public:
	ShaderResource() :m_registerIndex(0) {}

	int GetRegisterIndex() { return m_registerIndex; }
	void  SetRegisterIndex(int registerIndex) { m_registerIndex = registerIndex; }
protected:
	int m_registerIndex;
};