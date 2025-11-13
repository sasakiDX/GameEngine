#pragma once
#include <list>
#include <string>
#include <DirectXMath.h>
#include "Transform.h"

using std::string;
using std::list;

class SphereCollider;

class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent, const string& name);
	virtual ~GameObject();

	// 派生クラスで必ず定義する純粋仮想関数
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	// 各種サブ処理
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	// 衝突判定
	void Collision(GameObject* pTarget);
	void RoundRobin(GameObject* pTarget);
	void Collision(); // （再帰衝突処理用）

	// 衝突時に呼ばれる（派生クラスでオーバーライド）
	virtual void OnCollision(GameObject* other) {}

	// 位置関連
	void SetPosition(DirectX::XMFLOAT3 position);
	void SetPosition(float x, float y, float z);

	// オブジェクト破棄
	void KillMe();

	// 階層構造関連
	GameObject* GetRootJob();
	GameObject* FindChildObject(const string& name);
	GameObject* FindObject(const string& name);

	// コライダー追加
	void AddCollider(SphereCollider* pCollider);

	// オブジェクト生成（テンプレート）
	template<class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* obj = new T(parent);
		obj->Initialize();
		childList_.push_back(obj);
		return obj;
	}

protected:
	list<GameObject*>	childList_;		// 子オブジェクト
	Transform			transform_;		// 位置・回転・スケール
	GameObject* pParent_;		// 親
	string				objectName_;	// 名前
	SphereCollider* pCollider_;		// コライダー

private:
	bool isDead_; // 削除フラグ
};