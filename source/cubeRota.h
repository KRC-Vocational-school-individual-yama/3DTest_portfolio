#pragma once

#include"libs/object.h"
#include"cube.h"
class Cube;

class CubeRota :public Object {
public:
	CubeRota(Scene* sc);
	~CubeRota()		;
	void Init()		;
	void Update()	;
	void Draw()		;
private:
	Cube* cube;
	CubeConfig::CubePos2 pos;
};