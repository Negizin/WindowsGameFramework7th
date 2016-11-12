/*!-----------------------------------------------------------------/
//@brief	Vertex.h
//
//  ’¸“_’è‹`
//
//@Auther   ‹{Œ´•qŽj
//@Date     2016/10/22
//-----------------------------------------------------------------*/
#pragma once

#include	"../../../../Utilities/Math/Math.h"
#include <array>

// default Vertex
struct VertexDefault {
	Vector3 pos;
	Vector2 uv;
	Vector3 normal;
};

// SkinMesh Vertex
struct VertexSkin {
	Vector3 pos;
	Vector2 uv;
	Vector3 normal;
	Vector4 weight;
	std::array<int, 4>boneIndex;
	int weighttype;
};

//	ScreenSpace Vertex
struct VertexScreenSpace {
	Vector4 data;
};
