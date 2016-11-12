#pragma once

#include <array>
#include "MaterialBase.h"
class LambertMatrial : public MaterialBase
{
public:
	LambertMatrial();
	virtual ~LambertMatrial();
	struct LambertMat
	{
		std::array<float,4> diffuse;
		float	 ambient;
		LambertMat()
		{
			std::array<float, 4> _diffuse{ { 1,1,1,1 } };
			diffuse = _diffuse;
			ambient = 0.2f;
		}
	};

	bool SetColor(std::array<float, 4> color);
	virtual bool ApplyMaterial(DeviceContext*) override;
	virtual bool CreateMaterial(DX11Device*) override;
	virtual bool UpdateMaterial(DeviceContext*)override;
protected:
	LambertMat m_material;
};