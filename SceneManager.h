#pragma once
#include "Engine/GameObject.h"

enum SCENE_ID
{
    SCENE_ID_TEST,
    SCENE_ID_PLAY,
};

class SceneManager : public GameObject
{
public:
    SceneManager(GameObject* parent);
    ~SceneManager();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void ChangeScene(SCENE_ID nextScene);

private:
    SCENE_ID currentSceneID_;
    SCENE_ID nextSceneID_;
};