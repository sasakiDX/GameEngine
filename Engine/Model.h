#pragma once
#include <string>
#include <vector>
#include "fbx.h"
#include "Transform.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;
		std::string filename_;
		int refCount;
	};
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
	void ReleaseHandle(int hModel);
}