#include "gamescene.h"

#include"libs/scenemanager.h"
#include<DxLib.h>
#include"camera.h"
#include"testobject.h"
#include"sphere.h"
#include"cube.h"
#include"cubeRota.h"

GameScene::GameScene(){
	Create<Camera>();
	Create<TestObject>();
	Create<Sphere>();
	Create<Cube>();
	//Create<CubeRota>();
}
GameScene::~GameScene(){

}

void GameScene::Update(){
	Scene::Update();
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::ChangeScene("Title");
	}
}

void GameScene::Draw(){
	Scene::Draw();
	printfDx("\n");
}

