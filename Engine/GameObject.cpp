#include "GameObject.h"
#include "SphereCollider.h"
#include <Windows.h>
#include <vector>
#include <functional>

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	: pParent_(parent), objectName_(name), isDead_(false)
{
	if (pParent_ != nullptr)
	{
		transform_.pParent_ = &(pParent_->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();

	for (auto child : childList_)
	{
		child->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	transform_.Calculation();
	this->Update();

	if (pParent_ == nullptr)
	{
		CheckAllCollision();
	}

	for (auto child : childList_)
	{
		child->UpdateSub();
	}

	for (auto it = childList_.begin(); it != childList_.end(); )
	{
		if ((*it)->isDead_)
		{
			(*it)->ReleaseSub();
			delete (*it);
			it = childList_.erase(it);
		}
		else {
			++it;
		}
	}
}


void GameObject::ReleaseSub()
{
	this->Release();
	for (auto child : childList_)
	{
		child->ReleaseSub();
		delete child;
	}

}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;

}

void GameObject::SetPosition(float x, float y, float z)
{
	transform_.position_ = { x,y,z };
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;
	}
	else
	{
		return pParent_->GetRootJob();
	}
}

GameObject* GameObject::FindChildObject(const std::string& name)
{
	if (this->objectName_ == name)
	{
		return this;
	}
	else
	{
		for (auto child : childList_)
		{
			GameObject* result = child->FindChildObject(name);
			if (result != nullptr)
			{
				return result;
			}
		}
	}
	return nullptr;
}

GameObject* GameObject::FindObject(const std::string& name)
{
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(name);
	return result;


}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	//this->pCollider_->CheckCollision(pTarget->pCollider_)がぶつかっているか
	//お互いの半径+半径
	float thisR = this->pCollider_->GetRadius();
	float tgtR = pTarget->pCollider_->GetRadius();
	float thre = (thisR + tgtR) * (thisR + tgtR);

	//2つのコライダーの距離計さん
	XMFLOAT3 thisPos = this->transform_.position_;
	XMFLOAT3 tgtPos = pTarget->transform_.position_;
	float dist = (thisPos.x - tgtPos.x) * (thisPos.x - tgtPos.x) +
		(thisPos.y - tgtPos.y) * (thisPos.y - tgtPos.y) +
		(thisPos.z - tgtPos.z) * (thisPos.z - tgtPos.z);

	//コライダー同士が交差していたら
	if (dist <= thre)
	{
		//なんかする
		/*MessageBoxA(NULL, "本当にぶつかったの？", "当たったかどうか", MB_OK);*/
		this->onCollision(pTarget);
		pTarget->onCollision(this);
	}


}


void GameObject::CheckAllCollision()
{
	std::vector<GameObject*> all;
	all.reserve(256);
	std::function<void(GameObject*)> gather = [&](GameObject* node)
		{
			if (!node) return;
			all.push_back(node);
			for (auto child : node->childList_)
			{
				gather(child);
			}
		};

	gather(GetRootJob());

	const size_t n = all.size();
	for (size_t i = 0; i < n; ++i)
	{
		GameObject* a = all[i];
		if (!a) continue;

		if (!a->pCollider_) continue;
		if (a->isDead_) continue;

		for (size_t j = i + 1; j < n; ++j)
		{
			GameObject* b = all[j];
			if (!b) continue;
			if (!b->pCollider_) continue;
			if (b->isDead_) continue;

			float ar = a->pCollider_->GetRadius();
			float br = b->pCollider_->GetRadius();
			float thr = (ar + br) * (ar + br);

			auto pa = a->transform_.position_;
			auto pb = b->transform_.position_;

			float dx = pa.x - pb.x;
			float dy = pa.y - pb.y;
			float dz = pa.z - pb.z;
			float dist2 = dx * dx + dy * dy + dz * dz;

			if (dist2 <= thr)
			{
				a->onCollision(b);
				b->onCollision(a);
			}
		}
	}
}