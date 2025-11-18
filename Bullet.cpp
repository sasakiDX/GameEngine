#include "Bullet.h"
#include "Engine/SphereCollider.h"

Bullet::Bullet(GameObject* parent)
    : GameObject(parent, "Bullet"), hModel_(-1),
    speed_(0.5f), lifeTime_(100.0f)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
    hModel_ = Model::Load("oden.fbx");
    transform_.scale_ = { 0.2f, 0.2f, 0.2f };

    AddCollider(new SphereCollider(0.5f));
}

void Bullet::Update()
{
    transform_.position_.z += speed_;

    lifeTime_ -= 1.0f;

    if (lifeTime_ <= 0)
    {
        KillMe();
    }
}

void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Bullet::Release()
{
}

void Bullet::onCollision(GameObject* other)
{
    KillMe();
}