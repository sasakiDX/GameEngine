#include "ClearScene.h"
#include "SceneManager.h"
#include "Engine/Input.h"

ClearScene::ClearScene(GameObject* parent)
    : GameObject(parent, "ClearScene")
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
}

void ClearScene::Update()
{
    // SPACE‚Åƒ^ƒCƒgƒ‹‚Ö–ß‚é
    if (Input::IsKeyDown(DIK_SPACE))
    {
        auto* sm = static_cast<SceneManager*>(FindObject("SceneManager"));
        if (sm)
            sm->ChangeScene(SCENE_ID_TITLE);
    }
}

void ClearScene::Draw()
{
}

void ClearScene::Release()
{
}
