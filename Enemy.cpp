#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/GameObject.h"

Enemy::Enemy(GameObject* parent)
    : GameObject(parent, "Enemy"),
    hModel_(-1),
    speed_(0.05f)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
    hModel_ = Model::Load("oden.fbx");
    transform_.scale_ = { 0.5f, 0.5f, 0.5f };

    SphereCollider* col = new SphereCollider(0.5f);
    AddCollider(col);

    float x = (rand() % 200 - 100) * 0.05f;
    float y = (rand() % 200 - 100) * 0.05f;

    transform_.position_ = { x, y, 20.0f };
}

void Enemy::Update()
{
    transform_.position_.z -= speed_;
}

void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::onCollision(GameObject* other)
{
    if (other && other->GetName() == "Bullet")
    {
        KillMe();
    }
}