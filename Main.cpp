

#include "DxLib.h"
#include "Game.h"
#include "GameManager.h"
#include "GameDefine.h"
#include "Animation.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);


	SetWaitVSyncFlag(TRUE);


	// DXライブラリの初期化
	if (DxLib_Init() == -1) {

		return -1; // 初期化に失敗した場合は終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	SetBackgroundColor(50, 50, 70);  // 暗めの青背景

	GameManager::GetInstance().GameInit();

	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);

	// メインループ
	while (ProcessMessage() == 0) {


		SetWaitVSyncFlag(TRUE);

		WaitTimer(16);       

		// 画面をクリア
		ClearDrawScreen();

		// ゲームの更新と描画
		GameManager::GetInstance().GameUpdate();
		GameManager::GetInstance().GameDraw();


		// 画面を更新
		ScreenFlip();

	}

	// DXライブラリの終了処理
	DxLib_End();

	return 0;
}