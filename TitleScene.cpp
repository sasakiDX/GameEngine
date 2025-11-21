#include "TitleScene.h"
#include "SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene"), hModel_(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
    hModel_ = Model::Load("Title.fbx");

    // モデルが中心にくるように
    transform_.position_ = { 0.0f, 0.0f, 0.0f };
    transform_.scale_ = { 1.0f, 1.0f, 1.0f };
    transform_.rotate_ = { 0.0f, 0.0f, 0.0f };
}

void TitleScene::Update()
{
    // スペースでゲーム開始
    if (Input::IsKeyDown(DIK_SPACE))
    {
        auto* sm = static_cast<SceneManager*>(FindObject("SceneManager"));
        if (sm)
            sm->ChangeScene(SCENE_ID_PLAY);
    }
}

void TitleScene::Draw()
{
    if (hModel_ >= 0)
    {
        Model::SetTransform(hModel_, transform_);
        Model::Draw(hModel_);
    }
}

void TitleScene::Release()
{
    Model::Release();
}