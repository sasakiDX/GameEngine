#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include <ctime>
#include "SceneManager.h"

PlayScene::PlayScene(GameObject* parent)
    :GameObject(parent, "PlayScene"), requestClear_(false)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
    Instantiate<Player>(this);

    static bool seeded = false;
    if (!seeded) {
        seeded = true;
        std::srand((unsigned)std::time(nullptr));
    }

    for (int i = 0; i < 10; i++)
    {
        GameObject* e = Instantiate<Enemy>(this);

        float x = (std::rand() % 200 - 100) * 0.05f;
        float y = (std::rand() % 200 - 100) * 0.05f;
        float z = 30.0f;

        e->SetPosition({ x, y, z });
    }
}

void PlayScene::Update()
{
    if (!requestClear_)
    {
        int enemyCount = 0;
        for (auto c : childList_)
        {
            if (dynamic_cast<Enemy*>(c)) ++enemyCount;
        }

        if (enemyCount == 0)
        {
            requestClear_ = true;
        }
    }
    else
    {
        GameObject* obj = FindObject("SceneManager");
        if (obj)
        {
            SceneManager* sm = static_cast<SceneManager*>(obj);
            sm->ChangeScene(SCENE_ID_CLEAR);
        }
    }
}

void PlayScene::Draw()
{
}


void PlayScene::Release()
{
}
