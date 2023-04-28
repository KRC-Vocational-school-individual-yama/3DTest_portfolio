#pragma once

#include"libs/object.h"

class Sphere :public Object {
public:
	Sphere(Scene* sc);
	~Sphere()		override;
	void Init()		override;	
	void Update()	override;
	void Draw()		override;

private:
	VECTOR position;
	VECTOR rotation;
	bool full;
};