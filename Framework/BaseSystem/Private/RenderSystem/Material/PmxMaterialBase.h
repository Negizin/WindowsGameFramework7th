#pragma once

#include <array>
#include "MaterialBase.h"
class PmxMaterialBase : public MaterialBase
{
public:
	PmxMaterialBase();
	virtual ~PmxMaterialBase();
	struct PmxBase
	{
		std::array<float, 4>	diffuse;
		std::array<float, 4>	specular;	///< ���ʔ��˂̐���(a:�X�y�L�������x�j
		std::array<float, 3>	emissive;	///< ���Ȕ����̐���
		PmxBase()
		{
			std::array<float, 4> _diffuse{ { 1, 1, 1, 1 } };
			diffuse = _diffuse;
		}
	};

	bool SetDiffuse(std::array<float, 4> color);
	bool SetSpecular(std::array<float, 4> specular);
	bool SetEmissive(std::array<float, 3> emissive);
	virtual bool ApplyMaterial(DeviceContext*) override;
	virtual bool CreateMaterial(DX11Device*) override;
	virtual bool UpdateMaterial(DeviceContext*)override;

	void SetMaterialMeshCount(int cnt){
		materialMeshCnt = cnt;
	}
	int GetMaterialMeshCount()
	{
		return materialMeshCnt;
	}
	int materialMeshCnt;
	PmxBase m_material;
};