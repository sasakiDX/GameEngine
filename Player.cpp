#include "Player.h"
#include "Engine\\Fbx.h"
#include "Engine\\Model.h"
#include "ChildOden.h"
#include "Engine/SphereCollider.h"
#include "Engine\\input.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//pFbx_ = new Fbx;
	////pFbx_がnullptrじゃなかったら。
	//// のチェックを入れた方がいいよ
	//pFbx_->Load("oden.fbx");

	hModel = Model::Load("oden.fbx");
	assert(hModel >= 0);
	//transform_.scale_.x = 0.7f;
	//transform_.scale_.y = 0.7f;
	//transform_.scale_.z = 0.7f;
	//子オブジェクトにChildOdenを追加する
	pRChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pLChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pRChildOden_->SetPosition(2.0f, 1.0f, 0.0f);
	pLChildOden_->SetPosition(-2.0f, 1.0f, 0.0f);

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Player::Update()
{
	static float x = 0.0;
	float tx = sin(x) * 5.0f;
	x += 0.02f;
	//transform_.position_.x = tx;
	transform_.rotate_.y += 1.0f;
	if (Input::IsKey(DIK_SPACE))
	{
		transform_.position_.z += 0.2f;
	}


	//if (transform_.rotate_.y > 720.0f)
	//{
	//	KillMe();
	//}
}

void Player::Draw()
{
	//if (pFbx_)
	//{
	//	pFbx_->Draw(transform_);
	//}
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Player::Release()
{
	//if (pFbx_)
	//{
	//	pFbx_->Release();
	//	delete pFbx_;
	//	pFbx_ = nullptr;
	//}
}