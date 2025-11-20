#include "TitleScene.h"
#include "SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene")
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
}

void TitleScene::Update()
{
    if (Input::IsKeyDown(DIK_SPACE))
    {
        auto* sm = static_cast<SceneManager*>(FindObject("SceneManager"));
        if (sm)
            sm->ChangeScene(SCENE_ID_PLAY);
    }
}

void TitleScene::Draw()
{
}

void TitleScene::Release()
{
}