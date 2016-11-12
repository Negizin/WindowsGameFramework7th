/*!-----------------------------------------------------------------/
//@brief	MeshFactory.h
//
//  ���b�V���t�@�N�g���[
//
//@Auther   �{���q�j
//@Date     2016/11/08
//-----------------------------------------------------------------*/
#pragma once
#include	"../../../Public/Common/Common.h"

class GeometryObject;
class DX11Device;
class MeshFactory {
public:
	MeshFactory();
	virtual ~MeshFactory();

	bool LoadModelFromFile(DX11Device *pDev, tstring filename, tstring name);
	bool LoadModelFromFile(tstring filename, tstring name);

};