#pragma once
#include"libs/object.h"

class Camera :public Object {
public:
	Camera(Scene* sc);
	~Camera()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	const VECTOR& GetPos() { return position; }
private:
	void DispMove();
	void UpDownMove();
	void Movement();


	VECTOR position;
	VECTOR target;
	VECTOR tarPos;
	VECTOR velocity;
	VECTOR rotation;
	Vec2<int>mouse;
	Vec2<int>oldMouse;

};