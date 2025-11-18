#include "Player.h"
#include "Engine/Input.h"
#include "Bullet.h"

Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
    hModel_ = Model::Load("oden.fbx");
    transform_.position_ = { 0, 0, 0 };
    transform_.scale_ = { 0.5f, 0.5f, 0.5f };
}

void Player::Update()
{
    float speed = 0.2f;

    if (Input::IsKey(DIK_LEFT))  transform_.position_.x -= speed;
    if (Input::IsKey(DIK_RIGHT)) transform_.position_.x += speed;
    if (Input::IsKey(DIK_UP))    transform_.position_.y += speed;
    if (Input::IsKey(DIK_DOWN))  transform_.position_.y -= speed;

    if (Input::IsKeyDown(DIK_SPACE))
    {
        GameObject* root = GetRootJob();
        GameObject* bullet = root->Instantiate<Bullet>(root);
        bullet->SetPosition(transform_.position_);
    }
}

void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Player::Release()
{
    Model::Release();
}
