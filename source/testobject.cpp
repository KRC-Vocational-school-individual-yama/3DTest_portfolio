#include "testobject.h"

TestObject::TestObject(Scene* sc)
	:Object(sc)
{}
TestObject::~TestObject(){

}
void TestObject::Init(){


}
void TestObject::Update(){

}
void TestObject::Draw(){
	for (int i = 0; i < 100; i++) {
		int offset = i * 100;
		DrawLine3D(VGet(0-1000,0,0+offset)	,VGet(0+1000,0,0+offset)	,0x22222ff);
		DrawLine3D(VGet(offset,0,0-1000)	,VGet(offset,0,0+1000)		,0xff22222);
		DrawLine3D(VGet(-200,offset,0-1000)	,VGet(-200,offset,0+1000)	,0x00ff55);

		DrawLine3D(VGet(0,0,1000), VGet(1000,0,0), 0xffdd00);

	}
}
