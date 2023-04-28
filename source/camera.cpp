#include "camera.h"

Camera::Camera(Scene* sc)
	:Object(sc)
	, position(VGet(0,0,0))
	,target(VGet(0,0,1))
	,tarPos(VGet(0, 300, -500))
	, rotation(VGet(0,0,0))
	, velocity(VGet(0,0,0))
	,mouse({0,0})
	,oldMouse({0,0})
{}
Camera::~Camera(){


}
void Camera::Init(){

	MATRIX matrix = MGetTranslate(VGet(0, 300, -500));
	position = VTransform(position, matrix);
	SetCameraPositionAndTarget_UpVecY(position, target);

}
void Camera::Update(){
	GetMousePoint(&mouse.x,&mouse.y);

	UpDownMove();


	DispMove();
	
	//MATRIX rotY = MGetRotY(rotation.y);
	//VECTOR offset = VGet(0, 300, -500);
	//offset = VTransform(offset, rotY);
	//position=VAdd(velocity, offset);

	Movement();

	//pos Resset
	if (CheckHitKey(KEY_INPUT_LCONTROL)) {

		position = VGet(0, 0, 0)		;
		target=VGet(0, 0, 1)		;
		tarPos=VGet(0, 300, -500)	;
		rotation=VGet(0, 0, 0)		;
		velocity=VGet(0, 0, 0)		;

		Init();
	}


	//printfDx("mVecX = %d\n",mVec.x);
	//printfDx("mVecY = %d\n",mVec.y);
	printfDx("rotation.x = %f\n",rotation.x/DX_PI_F*180);
	printfDx("rotation.y = %f\n",rotation.y/DX_PI_F*180);

	oldMouse = mouse;
}
void Camera::Draw(){

	////MATRIX matrix = MGetTranslate(VGet(0, 300, -500));
	//MATRIX matrix = MGetTranslate(VGet(0, 0,0));
	//VECTOR pos = VTransform(position, matrix);
	////SetCameraPositionAndTarget_UpVecY(pos, target);

	MATRIX rotY = MGetRotY(rotation.y);
	//MATRIX move = MGetTranslate(VGet(0,300,-500));
	MATRIX move = MGetTranslate(tarPos);
	MATRIX rotX = MGetRotX(rotation.x);
	//MATRIX ans= MMult(move,rotY);
	VECTOR tar = VTransform(target,MMult(MMult(rotX, rotY), move));
	//MATRIX ans = MMult(rotX,rotY);
	//MATRIX ans2 = MMult(ans,move);
	//VECTOR tar = VTransform(target,ans2);

	SetCameraPositionAndTarget_UpVecY(VAdd(position,velocity),VAdd(tar,velocity));
	DrawSphere3D(VGet(0,100,500),20,16,0xffffff,0xffffff,true);

	DrawSphere3D(tar,20,16,0xffffff,0xffffff,true);

	//MATRIX MGetTranslate( VECTOR Trans ) ;
	//https://dxlib.xsrv.jp/function/dxfunc_3d_math.html#R11N16
	//VECTOR VTransform( VECTOR InV, MATRIX InM ) ;
	//https://dxlib.xsrv.jp/function/dxfunc_3d_math.html#R11N12


}

void Camera::DispMove(){
Vec2<int> mVec = { mouse.x - oldMouse.x,oldMouse.y - mouse.y };

	float num = mVec.x*0.01;
	rotation.y += num;
	num = (mVec.y *0.9)* DX_PI_F / 180.0f;
	rotation.x += -num;


if (CheckHitKey(KEY_INPUT_LEFT)) {
		rotation.y -= 10 * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) ){
		rotation.y += 10 * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		rotation.x -= 10 * DX_PI_F / 180.0f;
	}
	if ( CheckHitKey(KEY_INPUT_DOWN)) {
		rotation.x += 10 * DX_PI_F / 180.0f;
	}
	if (rotation.x < -85* DX_PI_F / 180.0f)rotation.x = -85 * DX_PI_F / 180.0f;
	if (rotation.x > 85 *DX_PI_F / 180.0f)rotation.x = 85 * DX_PI_F / 180.0f;
	
}

void Camera::UpDownMove(){
	const int NUM = 20;

bool upKey = CheckHitKey(KEY_INPUT_SPACE);
	bool downKey = CheckHitKey(KEY_INPUT_LSHIFT);
	if (upKey) {
		velocity.y += NUM;
	}
	if (downKey) {
		velocity.y += -NUM;
	}

}

void Camera::Movement() {
	static const float MOVE_SPEED = 25.5f;
	
	bool wKey = CheckHitKey(KEY_INPUT_W);
	bool sKey = CheckHitKey(KEY_INPUT_S);
	bool aKey = CheckHitKey(KEY_INPUT_A);
	bool dKey = CheckHitKey(KEY_INPUT_D);
	
	Vec2<int> vec = {0,0};
	
	if (wKey) {
		vec.y = 1;
	}
	if (sKey) {
		vec.y = -1;

	}

	if (dKey) {
		vec.x = 1;

	}
	if (aKey) {
		vec.x = -1;

	}

	if (vec.x == 0 && vec.y == 0)
		return;

	float inputAngle = atan2(vec.x,vec.y);//ì¸óÕÇÃäpìx
	MATRIX rotY = MGetRotY(inputAngle+rotation.y);	//Yé≤ÇÃâÒì]çsóÒ
	VECTOR move = VGet(0, 0, MOVE_SPEED);//âÒì]ÇµÇƒÇ»Ç¢Ç∆Ç´ÇÃà⁄ìÆÉxÉNÉgÉã

	tarPos = VAdd(position, VTransform(move, rotY));
	position = VAdd(position, VTransform(move, rotY));
}
