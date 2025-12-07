

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

		//背景のフェードインが終わった直後の処理
	case TitlePhase::PressAny:

		if (!startLogofade) {

			startLogofade = true;
			logo_Enter_Alpha = 0.0f;
		
		}

		//ロゴとPressAnyのフェードイン
		if (startLogofade) {
			logo_Enter_Alpha += 0.5f;
		

			if (logo_Enter_Alpha >= 255.0f) {
				logo_Enter_Alpha = 255.0f;
				title_Effect_Alpha += 3.0;
			}


			if (title_Effect_Alpha >= 255.0f) {
				title_Effect_Alpha = 255.0;
			}
	
		}


		//キー入力で次に進む
		if(InputManager::GetInstance().IsTrigger(KEY_INPUT_RETURN)){
			currentTitlePhase = TitlePhase::PressFadeOut;
	/*		startLogofade = false;*/
		}



		break;

	case TitlePhase::PressFadeOut:

		//　ロゴとPressAnyのフェードアウト
		logo_Enter_Alpha -= 5;


		// 透明度の下限チェック
		if (logo_Enter_Alpha <= 0) logo_Enter_Alpha = 0;
	

		// 完全に消えたら次のフェーズへ
		if (logo_Enter_Alpha == 0) {
			currentTitlePhase = TitlePhase::MenuFadein;
		}


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


	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)logo_Enter_Alpha);



	DrawGraph(700, 40, cloud_2, TRUE);



	DrawGraph(390, -50, keinai, TRUE);

	DrawGraph(390, 150, cloud_1, TRUE);



	DrawGraph(340, 300, title_hund1, TRUE);

	DrawGraph(790, 20, title_hund2, TRUE);


	DrawGraph(340, 450, kusa_1, TRUE);

	DrawGraph(820, 300, kusa_2, TRUE);

	
		DrawGraph(445, 10, titleLogo, TRUE);
	

	if (title_flag) {
		DrawGraph(445, 10, titleLogo2, TRUE);

	}
	


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す






	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)logo_Enter_Alpha);


	title_effect.Draw(510, 420, title_Effect_Alpha);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)logo_Enter_Alpha);


	DrawGraph(510, 460, PressEnterKey, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す



	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70); // 透明度50%

	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す



	movenoize.Draw(0, 0,20);


	hibana.Draw(0, 300,255);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90); // 透明度50%



	noize.Draw(0, noiseY,255);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す

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

	movenoize.Init("movenoize", 89, 9, 2, "delay-0.033333333333333s", 6.0f);

	title_effect.Init("title_effect", 89, 5, 2, "delay-0.041666666666667s", 1.1f);

	// タイトルロゴ画像の読み込み
	titleLogo = LoadGraph("TitleLogo/titlelogo.png");

	titleLogo2 = LoadGraph("TitleLogo/titlelogo2.png");

	keinai = LoadGraph("TitleLogo/keinai.png");

	kusa_1 = LoadGraph("TitleLogo/kusa_1.png");

	kusa_2 = LoadGraph("TitleLogo/kusa_2.png");

	title_hund1 = LoadGraph("TitleLogo/title_hund1.png");

	title_hund2 = LoadGraph("TitleLogo/title_hund2.png");

	cloud_1 = LoadGraph("TitleLogo/cloud_1.png");

	cloud_2 = LoadGraph("TitleLogo/cloud_2.png");

	/*titlenoize = LoadGraph("data/titlenoize.png");*/

	// タイトルBGMの読み込みと再生
	titleBGM = LoadSoundMem("data/titlebgm.wav");

	// タイトル背景画像の読み込み
	titleBG = LoadGraph("data/bg.jpg");

	// タイトルメニュー画像の読み込み

	PressEnterKey = LoadGraph("data/pressenterkey.png");

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


	movenoize.Update();

	//項目選択アニメーションの更新
	title_effect.Update();

	// 入力の更新
	InputManager::GetInstance().Update();

	if (fader.IsFading())return;

	//　各シーンの切り替え
	switch (currentScene) {

	case SceneType::TITLE:
		// ノイズ待ち時間を減らす
		noiseTimer--;

		title_flag = false;

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
				title_flag = true;


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

	DeleteGraph(titlenoize);

	DeleteGraph(PressEnterKey);

	DeleteGraph(keinai);

	DeleteGraph(kusa_1);

	DeleteGraph(kusa_2);

	DeleteGraph(title_hund1);

	DeleteGraph(title_hund2);

	DeleteGraph(cloud_1);

	DeleteGraph(cloud_2);

	DeleteGraph(titleLogo2);
	StopSoundMem(titleBGM);


};