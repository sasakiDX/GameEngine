#include "ClearScene.h"
#include "SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

ClearScene::ClearScene(GameObject* parent)
    : GameObject(parent, "ClearScene"), hModel_(-1)
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
    // クリア画面用モデル読み込み
    hModel_ = Model::Load("wa.fbx");

    transform_.position_ = { 0.0f, 0.0f, 0.0f };
    transform_.scale_ = { 1.0f, 1.0f, 1.0f };
    transform_.rotate_ = { 0.0f, 0.0f, 0.0f };
}

void ClearScene::Update()
{
    // SPACEでタイトルへ戻る
    if (Input::IsKeyDown(DIK_SPACE))
    {
        auto* sm = static_cast<SceneManager*>(FindObject("SceneManager"));
        if (sm)
            sm->ChangeScene(SCENE_ID_TITLE);
    }
}

void ClearScene::Draw()
{
    if (hModel_ >= 0)
    {
        Model::SetTransform(hModel_, transform_);
        Model::Draw(hModel_);
    }
}

void ClearScene::Release()
{
    Model::Release();
}