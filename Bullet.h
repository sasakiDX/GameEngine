#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

class Bullet : public GameObject
{
public:
    Bullet(GameObject* parent);
    ~Bullet();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

private:
    int hModel_;
    float speed_;
    float lifeTime_;
};