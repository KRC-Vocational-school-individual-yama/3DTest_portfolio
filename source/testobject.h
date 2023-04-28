#pragma once
#include"libs/object.h"

class TestObject :public Object {
public:
	TestObject(Scene* sc);
	~TestObject()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:

};