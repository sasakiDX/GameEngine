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
		// ルートだけ衝突処理
		CheckAllCollision();
	}

	transform_.Calculation();
	this->Update();

	RoundRobin(GetRootJob());
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
			it = childList_.erase(it); // ← eraseの戻り値を必ず使う
		}
		else
		{
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

void GameObject::RoundRobin(GameObject* pTarget)
{
	if (this->isDead_) return;
	if (pCollider_ == nullptr) return;
	if (pTarget == nullptr || pTarget->isDead_) return;

	if (pTarget->pCollider_ != nullptr && pTarget->pCollider_ != pCollider_)
	{
		Collision(pTarget);
	}

	// 子は安全な通常イテレータで処理する
	for (auto it = pTarget->childList_.begin(); it != pTarget->childList_.end(); ++it)
	{
		GameObject* child = *it;

		if (child && !child->isDead_)
		{
			RoundRobin(child);
		}
	}
}



void GameObject::CheckAllCollision()
{
	// 全オブジェクトを取得
	std::vector<GameObject*> all;
	std::function<void(GameObject*)> gather = [&](GameObject* obj)
		{
			all.push_back(obj);
			for (auto c : obj->childList_) gather(c);
		};
	gather(GetRootJob());

	// 全組み合わせで衝突チェック
	for (int i = 0; i < all.size(); i++)
	{
		for (int j = i + 1; j < all.size(); j++)
		{
			GameObject* a = all[i];
			GameObject* b = all[j];

			if (!a->pCollider_ || !b->pCollider_) continue;
			if (a->isDead_ || b->isDead_) continue;

			// 判定
			float ar = a->pCollider_->GetRadius();
			float br = b->pCollider_->GetRadius();
			float thr = (ar + br) * (ar + br);

			auto pa = a->transform_.position_;
			auto pb = b->transform_.position_;

			float dist =
				(pa.x - pb.x) * (pa.x - pb.x) +
				(pa.y - pb.y) * (pa.y - pb.y) +
				(pa.z - pb.z) * (pa.z - pb.z);

			if (dist <= thr)
			{
				a->onCollision(b);
				b->onCollision(a);
			}
		}
	}
}