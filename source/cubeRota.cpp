#include "cubeRota.h"
#include"libs/scene.h"

CubeRota::CubeRota(Scene* sc):Object(sc)
,cube(nullptr)
{}
CubeRota::~CubeRota(){

}
void CubeRota::Init(){
	cube = GetScene()->Invoke<Cube>();
}
void CubeRota::Update(){
	CubeConfig::CubePos2& cPos= cube->GetTransferCube();

	if (CheckHitKey(KEY_INPUT_I)) {
		cPos.pos[0]=VAdd(cPos.pos[0],VGet(100,100,100));
	}
	


	float x, y, z, size;
	cPos.GetCubePos2(&x, &y, &z, &size);
	cPos = CubeConfig::SetCube2(x,y,z,size);
	//ì‡êœ
}
void CubeRota::Draw(){

}
