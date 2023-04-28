#if true
#include <DxLib.h>
#include"config.h"
#include"app.h"

void LoadInit() {
	SetOutApplicationLogValidFlag(LOGSET_MODE);//ログの書き出し設定
	ChangeWindowMode(WINDOW_MODE);	//ウィンドウモードにする
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//ウィンドウサイズを設定する
	SetWindowSizeExtendRate(WINDOW_EXTEND);//ウィンドウ拡大率
	//SetWindowSizeChangeEnableFlag(TRUE);//途中大きさ変更あり
	SetWindowStyleMode(WINDOW_STYLE);//ウィンドウの最大化ボタンを機能させる。
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ
	//SetUseIMEFlag(true);// ＩＭＥを使用するかどうかを設定する
	SetWindowText(WINDOW_NAME);

}

//プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LoadInit();
	
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

		
	//SetAlwaysRunFlag(TRUE);//ウィンドウがアクティブではない状態でも動く
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
		

	//最初に１回呼ぶ
	App::Init();

	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		clsDx();
		ClearDrawScreen();	//裏画面の描画を全て消去
		App::Update();
		App::Draw();
		ScreenFlip();		//裏画面と表画面の入替
	}
	App::Delete();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
#else 

	#if false
#include "DxLib.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(WINDOW_MODE);	//ウィンドウモードにする
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//ウィンドウサイズを設定する
	SetOutApplicationLogValidFlag(LOGSET_MODE);//ログの書き出し設定
	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
	{
		// エラーが発生したら直ちに終了
		return -1;
	}

	// デフォルトの設定で３Ｄ空間上に球を描画する
	DrawSphere3D(VGet(160.0f, 200.0f, 0.0f), 80.0f, 32, GetColor(128, 0, 0), GetColor(255, 255, 255), TRUE);

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// Ｚバッファを有効にした状態で再度３Ｄ空間上に球を描画する
	DrawSphere3D(VGet(480.0f, 200.0f, 0.0f), 80.0f, 32, GetColor(128, 0, 0), GetColor(255, 255, 255), TRUE);

	// キー入力待ちをする
	WaitKey();

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}
	#endif
#if false

#include <DxLib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    int GrHandle;
    float Z, ZAdd;
    VERTEX_3D Vertex[6];    // ポリゴン２枚なので、頂点は６個

    ChangeWindowMode(TRUE);

    // ＤＸライブラリ初期化処理
    if (DxLib_Init() == -1)
        return -1;    // エラーが起きたら直ちに終了

   // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // テクスチャの読み込み
    GrHandle = LoadGraph("オリンピック国立公園 ワシントン州ソルドゥック川.jpg");

    // Ｚ値の初期化
    Z = 0.0F;

    // Ｚ値の加算値を初期化(最初は近づける)
    ZAdd = -1.0F;

    // 何かキーが押されるまでループ
    while (CheckHitKeyAll() == 0)
    {
        // メッセージ処理
        if (ProcessMessage() != 0) break;

        // 画面の初期化
        ClearDrawScreen();

        // Ｚ値の処理
        Z += ZAdd;

        // 一定のラインを越えていたら進行方向を反転する
        if (Z < -300.0F || Z > 300.0F) ZAdd = -ZAdd;

        // 頂点情報のセット
        {
            // 画面の中央に幅・高さ100で描画
            Vertex[0].pos.x = 320.0F - 50.0F;    Vertex[0].pos.y = 240.0F + 50.0F;    Vertex[0].pos.z = Z;
            Vertex[0].u = 0.0F;
            Vertex[0].v = 0.0F;

            Vertex[1].pos.x = 320.0F + 50.0F;    Vertex[1].pos.y = 240.0F + 50.0F;    Vertex[1].pos.z = Z;
            Vertex[1].u = 1.0F;
            Vertex[1].v = 0.0F;

            Vertex[2].pos.x = 320.0F - 50.0F;    Vertex[2].pos.y = 240.0F - 50.0F;    Vertex[2].pos.z = Z;
            Vertex[2].u = 0.0F;
            Vertex[2].v = 1.0F;

            Vertex[3].pos.x = 320.0F + 50.0F;    Vertex[3].pos.y = 240.0F - 50.0F;    Vertex[3].pos.z = Z;
            Vertex[3].u = 1.0F;
            Vertex[3].v = 1.0F;

            Vertex[4].pos.x = 320.0F - 50.0F;    Vertex[4].pos.y = 240.0F - 50.0F;    Vertex[4].pos.z = Z;
            Vertex[4].u = 0.0F;
            Vertex[4].v = 1.0F;

            Vertex[5].pos.x = 320.0F + 50.0F;    Vertex[5].pos.y = 240.0F + 50.0F;    Vertex[5].pos.z = Z;
            Vertex[5].u = 1.0F;
            Vertex[5].v = 0.0F;

            // 輝度は全要素100%
            Vertex[0].r = Vertex[0].g = Vertex[0].b = 255;
            Vertex[1].r = Vertex[1].g = Vertex[1].b = 255;
            Vertex[2].r = Vertex[2].g = Vertex[2].b = 255;
            Vertex[3].r = Vertex[3].g = Vertex[3].b = 255;
            Vertex[4].r = Vertex[4].g = Vertex[4].b = 255;
            Vertex[5].r = Vertex[5].g = Vertex[5].b = 255;

            // a も最大値
            Vertex[0].a = 255;
            Vertex[1].a = 255;
            Vertex[2].a = 255;
            Vertex[3].a = 255;
            Vertex[4].a = 255;
            Vertex[5].a = 255;
        }

        // ポリゴンを透過色無しで２枚描画
        DrawPolygon3D(Vertex, 2, GrHandle, TRUE);

        // 裏画面の内容を表画面に反映
        ScreenFlip();
    }

    // ＤＸライブラリ使用の終了処理
    DxLib_End();

    // ソフトの終了
    return 0;
}

#endif

#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int grhandle, pshandle, vshandle;
	VERTEX3DSHADER Vert[6] = { 0.0f };

	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
		return -1;

	// 画像の読み込み
	grhandle = LoadGraph("Texture0.bmp");

	// 頂点シェーダーバイナリコードの読み込み
	vshandle = LoadVertexShader("ShaderPolygon3DTestVS.vso");

	// ピクセルシェーダーバイナリコードの読み込み
	pshandle = LoadPixelShader("ShaderPolygon3DTestPS.pso");

	// 頂点データの準備
	Vert[0].pos = VGet(100.0f, 356.0f, 0.0f);
	Vert[1].pos = VGet(356.0f, 356.0f, 0.0f);
	Vert[2].pos = VGet(100.0f, 100.0f, 0.0f);
	Vert[3].pos = VGet(356.0f, 100.0f, 0.0f);
	Vert[0].dif = GetColorU8(255, 255, 255, 255);
	Vert[1].dif = GetColorU8(255, 255, 255, 255);
	Vert[2].dif = GetColorU8(255, 255, 255, 255);
	Vert[3].dif = GetColorU8(255, 255, 255, 255);
	Vert[0].u = 0.0f; Vert[0].v = 0.0f;
	Vert[1].u = 1.0f; Vert[1].v = 0.0f;
	Vert[2].u = 0.0f; Vert[3].v = 1.0f;
	Vert[3].u = 1.0f; Vert[2].v = 1.0f;
	Vert[4] = Vert[2];
	Vert[5] = Vert[1];

	// 使用するテクスチャをセット
	SetUseTextureToShader(0, grhandle);

	// 使用する頂点シェーダーをセット
	SetUseVertexShader(vshandle);

	// 使用するピクセルシェーダーをセット
	SetUsePixelShader(pshandle);

	// 描画
	DrawPolygon3DToShader(Vert, 2);

	// キー入力待ち
	WaitKey();

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}


#endif