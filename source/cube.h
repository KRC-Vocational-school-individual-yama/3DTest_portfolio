#pragma once
#include"libs/object.h"

namespace CubeConfig {
	struct CubePos {
		VECTOR pos;//¶ãÀ•W
		VECTOR size;//ˆê•Ó‚Ì‘å‚«‚³

	};
	inline CubePos SetCube(float x, float y, float z, float size) { return CubePos{ {x,y,z},{size,size,size} }; }

	struct CubePos2 {
		VECTOR pos[8];

		void GetCubePos2(float* x = nullptr, float* y = nullptr, float* z = nullptr, float* size = nullptr) {
			*x= this->pos[0].x;
			*y= this->pos[0].y;
			*z= this->pos[0].z;
			*size= this->pos[1].x- this->pos[0].x;
		}
	};
	inline CubePos2 SetCube2(float x, float y, float z, float size) {
		CubePos2 ans;

		ans.pos[0] = VAdd(VGet(x,y,z),VGet(0,0,0));
		ans.pos[1] = VAdd(VGet(x,y,z),VGet(size,0,0));
		ans.pos[2] = VAdd(VGet(x,y,z),VGet(size,0, size));
		ans.pos[3] = VAdd(VGet(x,y,z),VGet(0,0,size));

		ans.pos[4] = VAdd(ans.pos[0],VGet(0,size,0));
		ans.pos[5] = VAdd(ans.pos[1],VGet(0,size,0));
		ans.pos[6] = VAdd(ans.pos[2],VGet(0,size,0));
		ans.pos[7] = VAdd(ans.pos[3],VGet(0,size,0));
	
		return ans;
	}
}

class Cube :public Object {
public:
	Cube(Scene* sc);
	~Cube()			override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	CubeConfig::CubePos2& GetTransferCube() { return pos2; }
private:
	void DrawCube(unsigned int color);
	void DrawCube2(const CubeConfig::CubePos2& cube, unsigned int color = 0xffffff);
	CubeConfig::CubePos pos;
	CubeConfig::CubePos2 pos2;
	CubeConfig::CubePos2 disp;
	int randNum;
	int count;
};