#include "cube.h"
#include<vector>
using namespace CubeConfig;
namespace {
	static const int size = 500;
}

Cube::Cube(Scene* sc)
	:Object(sc)
	,pos(CubeConfig::SetCube(100,100,100,500))
	,pos2(SetCube2(0,0,0,size))
	,disp{}
	,randNum(0)
	,count(0)
{}
Cube::~Cube(){

}
void Cube::Init(){
	randNum = 2;
}
void Cube::Update(){
	count+=1;
	if (count > 360+180)count = 360-180;
	
	CubePos2 vec;
	VECTOR center;
	center.x=pos2.pos[0].x+(size/2);
	center.y=pos2.pos[0].y+(size/2);
	center.z=pos2.pos[0].z+(size/2);

	for (int i = 0; i < 8; i++) {
		//vec.pos[i].x = pos2.pos[i].x-center.x;
		//vec.pos[i].y = pos2.pos[i].y-center.y;
		//vec.pos[i].z = pos2.pos[i].z-center.z;

		vec.pos[i].x = center.x-pos2.pos[i].x;
		vec.pos[i].y = center.y-pos2.pos[i].y;
		vec.pos[i].z = center.z-pos2.pos[i].z;

		
		vec.pos[i]= VNorm(vec.pos[i]);
	}

	MATRIX rotX = MGetRotX(count *DX_PI/180);
	MATRIX rotY = MGetRotY(count *DX_PI/180);
	MATRIX rotZ = MGetRotZ(count *DX_PI/180);

	int num = (GetRand(5) + 1) * 100;
	for (int i = 0; i < 8; i++) {
		MATRIX mat = MMult(MMult(rotX, rotZ),rotY );
		disp.pos[i] = VTransform(VScale(vec.pos[i],num), mat);

		disp.pos[i] = VAdd(disp.pos[i],VGet(0,0,count*50));
	}




	//
	//pos.pos = VTransform(pos.pos, rotY);
	//
	//for (int i = 0; i < 8; i++) {
	//
	//	MATRIX mat = MMult(MMult(rotX, rotZ),rotY);
	//	pos2.pos[i] = VTransform(pos2.pos[i], mat);
	//}

}
void Cube::Draw(){
	DrawCube(0xffffff);
	DrawCube2(disp);

}
void Cube::DrawCube2(const CubeConfig::CubePos2& cube, unsigned int color) {
	struct line3D {
		int x, y, col;
	};

	std::vector<line3D>index;
	index.reserve(20);

	index.emplace_back(line3D{0,1,0xff5555});
	index.emplace_back(line3D{1,2,0x5555ff});
	index.emplace_back(line3D{2,3,0xff5555});
	index.emplace_back(line3D{3,0,0x5555ff});

	index.emplace_back(line3D{0+4,1+4,0xff5555});
	index.emplace_back(line3D{1+4,2+4,0x5555ff});
	index.emplace_back(line3D{2+4,3+4,0xff5555});
	index.emplace_back(line3D{3+4,0+4,0x5555ff});

	index.emplace_back(line3D{0,0+4,0x55ff55});
	index.emplace_back(line3D{1,1+4,0x55ff55});
	index.emplace_back(line3D{2,2+4,0x55ff55});
	index.emplace_back(line3D{3,3+4,0x55ff55});

	index.shrink_to_fit();
	
	for (const line3D& line : index) {
		DrawLine3D(cube.pos[line.x], cube.pos[line.y],line.col);
	}

	index.clear();
}

void Cube::DrawCube(unsigned int color) {

	//DrawLine3D(pos.pos,pos.size,color);


	VECTOR p[8] = {};
	p[0] = VAdd(pos.pos,VGet(0,0,0));
	p[1] = VAdd(pos.pos,VGet(pos.size.x,0,0));
	p[2] = VAdd(pos.pos,VGet(pos.size.x,0, pos.size.z));
	p[3] = VAdd(pos.pos,VGet(0,0, pos.size.z));

	p[4] = VAdd(p[0],VGet(0,pos.size.y,0));
	p[5] = VAdd(p[1],VGet(0,pos.size.y,0));
	p[6] = VAdd(p[2],VGet(0,pos.size.y,0));
	p[7] = VAdd(p[3],VGet(0,pos.size.y,0));

	//DrawLine3D(p[0],p[1],color);
	//DrawLine3D(p[1],p[2],color);
	//DrawLine3D(p[2],p[3],color);
	//DrawLine3D(p[3],p[0],color);

	//DrawLine3D(p[0+4],p[1+4],color);
	//DrawLine3D(p[1+4],p[2+4],color);
	//DrawLine3D(p[2+4],p[3+4],color);
	//DrawLine3D(p[3+4],p[0+4],color);

	//DrawLine3D(p[0],p[0+4],color);
	//DrawLine3D(p[1],p[1+4],color);
	//DrawLine3D(p[2],p[2+4],color);
	//DrawLine3D(p[3],p[3+4],color);

	std::vector<VECTOR>disp;
	std::vector<VECTOR>disp2;

	disp.emplace_back (p[0]);
	disp2.emplace_back(p[1]);
	disp.emplace_back (p[1]);
	disp2.emplace_back(p[2]);
	disp.emplace_back (p[2]);
	disp2.emplace_back(p[3]);
	disp.emplace_back (p[3]);
	disp2.emplace_back(p[0]);

	disp.emplace_back (p[0+4]);
	disp2.emplace_back(p[1+4]);
	disp.emplace_back (p[1+4]);
	disp2.emplace_back(p[2+4]);
	disp.emplace_back (p[2+4]);
	disp2.emplace_back(p[3+4]);
	disp.emplace_back (p[3+4]);
	disp2.emplace_back(p[0+4]);

	disp.emplace_back (p[0]);
	disp2.emplace_back (p[0+4]);
	disp.emplace_back(p[1]);
	disp2.emplace_back(p[1+4]);
	disp.emplace_back (p[2]);
	disp2.emplace_back (p[2+4]);
	disp.emplace_back(p[3]);
	disp2.emplace_back(p[3+4]);



	for (int i = 0; i < 12; i++) {
		DrawLine3D(disp.at(i),disp2.at(i),color);
	}

}
