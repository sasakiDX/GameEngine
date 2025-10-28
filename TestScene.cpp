#include "TestScene.h"
#include "SceneManager.h"
#include "Engine\\Input.h"
#include "Player.h"
#include "Engine\\Model.h"

TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene"), hModel_(-1)
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	// TestSceneでモデルを読み込み・表示
	hModel_ = Model::Load("wa.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = { 0.5f, 0.5f, 0.5f };
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
}

void TestScene::Update()
{
	transform_.rotate_.y += 0.5f;

	// スペースキーでPlaySceneへ遷移
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject* obj = FindObject("SceneManager");
		if (obj)
		{
			SceneManager* sm = static_cast<SceneManager*>(obj);
			sm->ChangeScene(SCENE_ID_PLAY);
		}
	}
}

void TestScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestScene::Release()
{
	Model::Release();
}