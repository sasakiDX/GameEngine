#include "GameObject.h"
#include "SphereCollider.h"
#include <Windows.h>

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

void GameObject::KillMe()
{
	isDead_ = true;
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
		this->OnCollision(pTarget);
		pTarget->OnCollision(this);
	}


}

void GameObject::RoundRobin(GameObject* pTarget)
{
	//自分にコライダーがなかったらreturn
	if (pCollider_ == nullptr)
	{
		return;
	}


	//自分とターゲット自体のコライダーの当たり判定
	if (pTarget->pCollider_ != nullptr && pTarget->pCollider_ != pCollider_)
		Collision(pTarget);


	//再帰的な奴でターゲットの子オブジェクトを当たり判定にしていく
	for (auto itr : pTarget->childList_)
	{
		RoundRobin(itr);
	}
}
