#include "sphere.h"

#include"libs/scene.h"
#include"camera.h"
#include<assert.h>

namespace {
	int hImage = -1;
}

Sphere::Sphere(Scene* sc):Object(sc)
,position(VGet(0,0,0))
,rotation(VGet(0,0,0))
,full(false)
{}
Sphere::~Sphere(){

}
void Sphere::Init(){
	SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP);
	hImage = LoadGraph("オリンピック国立公園 ワシントン州ソルドゥック川.jpg");
	assert(hImage!=-1);
}
void Sphere::Update(){

	Camera* pcamera= GetScene()->Invoke<Camera>();
	if (pcamera == nullptr)return;
	VECTOR cPos= pcamera->GetPos();

	VECTOR pTocVec = VSub(cPos, position);
	VECTOR moveSize =  VScale( VNorm(pTocVec),15);

	float distance= VSize(pTocVec);
	if (distance < 150) {
		full = false;
		return;
	}
	full = true;

	position = VAdd(position,moveSize);
	rotation.y = atan2(moveSize.x,moveSize.z);
}
void Sphere::Draw(){
	MATRIX move = MGetTranslate(VGet(0,-200,0));
	MATRIX rotY = MGetRotY(rotation.y);

	VECTOR pos2 = VTransform(position,MMult(rotY, move)) ;

	DrawLine3D(position,pos2,0xbbbb55);

	for (int i = 0; i < 3; i++) {
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawSphere3D(position, 75, 16, 0xffffff, 0xffffff, full);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	}

	DrawTriangle3D(VGet(0,0,0),VGet(100,0,0),VGet(0,100,0),0xffffff,true);
	DrawTriangle3D(VGet(0,0,100),VGet(100,0,100),VGet(0,100,100),0xffffff,false);

	DrawCapsule3D(VGet(200,0,0),VGet(200,100,0),50,20,0xffffff,0xffffff,true);
	DrawCapsule3D(VGet(200,0,100),VGet(200,100,100),50,20,0xffffff,0xffffff,false);

	
	DrawCone3D(VGet(300,0,0),VGet(300,100,0),50,20,0xffffff,0xffffff,true);
	DrawCone3D(VGet(300,0,100),VGet(300,100,100),50,20,0xffffff,0xffffff,false);

	DrawBillboard3D(VGet(400,0,0),0,0,64,0,hImage, true);
	//DrawBillboard3D(position,0.5f,0.5f,256,0,hImage, true);



	int graphSize = 100;
	VERTEX3D Vertex[6];

        // 画面の中央に幅・高さ100で描画
	Vertex[0].pos = VGet(0, graphSize,-1);
	Vertex[1].pos = VGet(0, graphSize, graphSize-1);
	Vertex[2].pos = VGet(0,0,-1);

	Vertex[3].pos = VGet(0,0, graphSize);
	Vertex[4].pos = VGet(0,0,0);
	Vertex[5].pos = VGet(0, graphSize, graphSize);


	Vertex[0].pos = VGet(-1, graphSize, 0);
	Vertex[1].pos = VGet(-graphSize - 1, graphSize, 0);
	Vertex[2].pos = VGet(-1, 0,0 );

	Vertex[3].pos = VGet(-graphSize, 0, 0);
	Vertex[4].pos = VGet(0, 0, 0);
	Vertex[5].pos = VGet(-graphSize, graphSize, 0);

	for(int i=0;i<6;i++)
	Vertex[i].pos= VAdd(Vertex[i].pos,VGet(600,0,0));

	Vertex[0].norm = VGet(0,0,-1);
	Vertex[1].norm = VGet(0,0,-1);
	Vertex[2].norm = VGet(0,0,-1);
	Vertex[3].norm = VGet(0,0,-1);
	Vertex[4].norm = VGet(0,0,-1);
	Vertex[5].norm = VGet(0,0,-1);

	Vertex[0].u = 0.f;
	Vertex[0].v = 0.f;

	Vertex[1].u = 1.f;
	Vertex[1].v = 0.f;

	Vertex[2].u = 0.f;
	Vertex[2].v = 1.f;

	Vertex[3].u = 1.f;
	Vertex[3].v = 1.f;

	Vertex[4].u = 0.f;
	Vertex[4].v = 1.f;

	Vertex[5].u = 1.f;
	Vertex[5].v = 0.f;


	for (int i = 0; i < 6; i++) {
		Vertex[i].dif = GetColorU8(255, 255, 255, 255);
		Vertex[i].spc = GetColorU8(0,0,0,0);
		Vertex[i].su = 0;
		Vertex[i].sv = 0;
	}

    //// 輝度は全要素100%
    //Vertex.r = Vertex.g = Vertex.b = 255;
    //// a も最大値
    //Vertex.a = 255;
   
	DrawPolygon3D(Vertex,2, hImage,true);
	




	// ２ポリゴン分の頂点のデータをセット
	Vertex[0].pos = VGet(100.0f, 400.0f, 0.0f);
	Vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].pos = VGet(500.0f, 400.0f, 0.0f);
	Vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].pos = VGet(100.0f, 100.0f, 0.0f);
	Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[2].dif = GetColorU8(255, 255, 255, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].pos = VGet(500.0f, 100.0f, 0.0f);
	Vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4].pos = VGet(100.0f, 100.0f, 0.0f);
	Vertex[4].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[4].dif = GetColorU8(255, 255, 255, 255);
	Vertex[4].spc = GetColorU8(0, 0, 0, 0);
	Vertex[4].u = 0.0f;
	Vertex[4].v = 1.0f;
	Vertex[4].su = 0.0f;
	Vertex[4].sv = 0.0f;

	Vertex[5].pos = VGet(500.0f, 400.0f, 0.0f);
	Vertex[5].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[5].dif = GetColorU8(255, 255, 255, 255);
	Vertex[5].spc = GetColorU8(0, 0, 0, 0);
	Vertex[5].u = 1.0f;
	Vertex[5].v = 0.0f;
	Vertex[5].su = 0.0f;
	Vertex[5].sv = 0.0f;

	for(int i=0;i<6;i++)
		Vertex[i].pos=VAdd( Vertex[i].pos, VGet(0,100,0));

	// ２ポリゴンの描画	
	DrawPolygon3D(Vertex, 2, hImage, FALSE);

}
