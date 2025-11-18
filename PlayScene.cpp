#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include <ctime>

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
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

    // エネミーを複数（例：10体）生成
    for (int i = 0; i < 10; i++)
    {
        GameObject* e = Instantiate<Enemy>(this);

        // ランダムなX,Yに散らす
        float x = (std::rand() % 200 - 100) * 0.05f;  // -5 ～ +5
        float y = (std::rand() % 200 - 100) * 0.05f;  // -5 ～ +5

        // Z は画面奥に固定（例: 30）
        float z = 30.0f;

        e->SetPosition({ x, y, z });
    }
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
