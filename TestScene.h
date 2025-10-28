#pragma once
#include "Engine\\GameObject.h"

// TestSceneクラス：FBXモデル(wa.fbx)を読み込み・回転表示し、スペースキーでPlaySceneへ遷移
class TestScene : public GameObject
{
public:
	TestScene(GameObject* parent);
	~TestScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hModel_; // モデルハンドル（wa.fbx用）
};
