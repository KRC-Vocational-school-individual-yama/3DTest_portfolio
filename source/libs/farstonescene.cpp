#include "farstonescene.h"
#include"scenemanager.h"

FarstOneScene::FarstOneScene(){
}
FarstOneScene::~FarstOneScene(){
}
void FarstOneScene::Update(){
	SceneManager::ChangeScene("Game");
}
void FarstOneScene::Draw(){
}
