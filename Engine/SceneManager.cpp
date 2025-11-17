#include "Direct3D.h"
#include "SceneManager.h"
#include "..\\PlayScene.h"
#include "..\\TitleScene.h"
#include "..\\ClearScene.h"
#include "..\\TestScene.h"
#include "Model.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		if (!childList_.empty())
		{
			auto scene = childList_.front();
			scene->ReleaseSub();
			delete scene;
			childList_.clear();
		}

		if (nextSceneID_ == SCENE_ID_TITLE)
		{
			Instantiate<TitleScene>(this);
		}
		else if (nextSceneID_ == SCENE_ID_PLAY)
		{
			Instantiate<PlayScene>(this);
		}
		else if (nextSceneID_ == SCENE_ID_CLEAR)
		{
			Instantiate<ClearScene>(this);
		}
		else if (nextSceneID_ == SCENE_ID_TEST)
		{
			Instantiate<TestScene>(this);
		}

		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID _nextScene)
{
	nextSceneID_ = _nextScene;
}