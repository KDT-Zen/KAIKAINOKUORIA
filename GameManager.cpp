

#include "GameManager.h"
#include "Scene.h"
#include "DxLib.h"
#include "GameDefine.h"
#include "Animation.h"
#include "InputManager.h"


//メモ GameManager&は戻値の型
//GameManager型の参照を返す関数　という意味


GameManager& GameManager::GetInstance() {

	//　GameManagerの唯一のインスタンスを生成・保持
	static GameManager instance;

	return instance;
}

void GameManager::UpdateTitle() {

	switch (currentTitlePhase) {

	case TitlePhase::PressAny:
		break;

	case TitlePhase::PressFadeOut:
		break;

	case TitlePhase::MenuFadein:
		break;

	case TitlePhase::MenuSelect:
		break;


	}

}


void GameManager::UpdateGame() {





}

void GameManager::UpdateEnd() {

}


// シーン変更
void GameManager::ChangeScene(SceneType next) {
	currentScene = next;
}




void GameManager::DrawTitle()
{
	DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, titleBG, TRUE);

	DrawGraph(200, 100, titleLogo, TRUE);

	hibana.Draw(0, 300);



	noize.Draw(0, noiseY);



}

void GameManager::DrawGame() {

}

void GameManager::DrawEnd() {

}



void GameManager::GameInit() {


	// フェードの初期化
	fader.Init();

	// フェードイン開始
	fader.StartFadeIn(6);


	// アニメーションの初期化
	hibana.Init("titlehibana", 99, 3, 3, "delay-0.04s", 2.3f);

	noize.Init("titlenoize", 88, 2, 2, "delay-0.033333333333333s", 6.0f);

	// タイトルロゴ画像の読み込み
	titleLogo = LoadGraph("data/logo.png");

	// タイトルBGMの読み込みと再生
	titleBGM = LoadSoundMem("data/titlebgm.wav");

	// タイトル背景画像の読み込み
	titleBG = LoadGraph("data/bg.jpg");

	// タイトルメニュー画像の読み込み

	PressAnyButton = LoadGraph("data/pressanybutton.png");

	NewGame = LoadGraph("data/newgame.png");

	Option = LoadGraph("data/option.png");

	Exit = LoadGraph("data/exit.png");

	TestPlay = LoadGraph("data/testplay.png");







	// タイトルBGMの再生
	PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP);


	ChangeVolumeSoundMem(90, titleBGM);  // 1フレームで音量180にする

	//　タイトルメニュー画像の透明度変数

	pressAlpha = 255.0f;

	menualpha = 0.0f;



}

void GameManager::GameUpdate() {

	// フェードの更新
	fader.Update();

	// アニメーションの更新
	hibana.Update();

	// ノイズアニメーションの更新
	noize.Update();

	// 入力の更新
	InputManager::GetInstance().Update();

	if (fader.IsFading())return;

	//　各シーンの切り替え
	switch (currentScene) {

	case SceneType::TITLE:
		// ノイズ待ち時間を減らす
		noiseTimer--;

		// 0以下になったら動く
		if (noiseTimer <= 0)
		{
			// ノイズのY位置をランダム量だけ動かす
			int dy = GetRand(5) + 1;
			noiseY += dy;

			// 次に動くまでの待ち時間をランダムに設定
			noiseTimer = GetRand(8) + 2;

			//  画面の下まで行ったら上にワープさせる
			if (noiseY > WINDOW_HEIGHT)
			{
				noiseY = -200;  // ノイズが自然に上から降ってくるように見える
			}
		}

		GameManager::UpdateTitle();

		break;

	case SceneType::GAME:

		// 本編（ADV文章進行）の更新処理

		GameManager::UpdateGame();

		break;

	case SceneType::ENDING:

		// エンディングの更新処理

		GameManager::UpdateEnd();

		break;

	}

}

void GameManager::GameDraw() {


	switch (currentScene) {

	case SceneType::TITLE:

		// タイトルの描画処理
		GameManager::DrawTitle();

		break;

	case SceneType::GAME:
		// 本編（ADV文章進行）の描画処理

		GameManager::DrawGame();

		break;

	case SceneType::ENDING:
		// エンディングの描画処理

		GameManager::DrawEnd();

		break;

	}

	fader.Draw();
}

void GameManager::GameEnd() {

	DeleteGraph(titleBG);

	DeleteGraph(titleLogo);


};