#include "Model.h"
#include "Direct3D.h"
#include <cassert>

namespace Model
{
	static std::vector<ModelData*> modelList;
}

int Model::Load(std::string fileName)
{
	for (size_t i = 0; i < modelList.size(); ++i)
	{
		if (modelList[i] && modelList[i]->filename_ == fileName)
		{
			modelList[i]->refCount++;
			return static_cast<int>(i);
		}
	}

	ModelData* pModelData = new ModelData;
	pModelData->filename_ = fileName;
	pModelData->pfbx_ = new Fbx;
	pModelData->pfbx_->Load(fileName.c_str());
	pModelData->transform_ = Transform();
	pModelData->refCount = 1;

	modelList.push_back(pModelData);
	return static_cast<int>(modelList.size() - 1);
}

void Model::SetTransform(int hModel, Transform transform)
{
	if (hModel < 0 || hModel >= static_cast<int>(modelList.size())) return;
	ModelData* md = modelList[hModel];
	if (!md) return;
	md->transform_ = transform;
}

void Model::Draw(int hModel)
{
	if (hModel < 0 || hModel >= static_cast<int>(modelList.size())) return;
	ModelData* md = modelList[hModel];
	if (!md) return;
	if (!md->pfbx_) return;
	md->pfbx_->Draw(md->transform_);
}

void Model::ReleaseHandle(int hModel)
{
	if (hModel < 0 || hModel >= static_cast<int>(modelList.size())) return;
	ModelData* md = modelList[hModel];
	if (!md) return;
	md->refCount--;
	if (md->refCount <= 0)
	{
		SAFE_DELETE(md->pfbx_);
		SAFE_DELETE(md);
		modelList[hModel] = nullptr;
	}
}

void Model::Release()
{
	for (size_t i = 0; i < modelList.size(); ++i)
	{
		if (modelList[i])
		{
			SAFE_DELETE(modelList[i]->pfbx_);
			SAFE_DELETE(modelList[i]);
		}
	}
	modelList.clear();
}