

#include "GameManager.h"
#include "Scene.h"
#include "DxLib.h"
#include "GameDefine.h"
#include "Animation.h"
#include "InputManager.h"

//メモ GameManager&は戻値の型
//GameManager型の参照を返す関数　という意味

//　GameManager インスタンス
GameManager& GameManager::GetInstance() {

	//　GameManagerの唯一のインスタンスを生成・保持
	static GameManager instance;

	return instance;
}

//　アップデート関数Title
void GameManager::UpdateTitle() {

	switch (currentTitlePhase) {

		//背景のフェードインが終わった直後の処理
	case TitlePhase::PressAny:

		//　まだフェードが開始していない初回だけ初期化する
		if (!startLogofade) {

			//　フェード処理開始フラグを立てる
			startLogofade = true;

			//　それぞれのアルファ値の設定
			logo_Alpha = 0.0f;

			T_Prees_Enter_Alpha = 0.0f;

			Menu_Text_Alpha = 0.0f;

			select_effect_flag = false;

		}
		//ロゴとPressAnyのフェードイン
		if (startLogofade) {

			logo_Alpha += 2.0f;

			T_Prees_Enter_Alpha += 2.0f;

			if (Select_Effect_Alpha < 255.0f) {

				if (logo_Alpha >= 255.0f) {

					logo_Alpha = 255.0f;

					Select_Effect_Alpha += 4.0;

					T_Prees_Enter_Alpha = 255.0f;
				}

				if (Select_Effect_Alpha >= 255.0f) {

					Select_Effect_Alpha = 255.0;

				}
			}
			else
			{

				if (pressBlinkIncreasing) {
					//　明るくしていくフェーズ（αを増やす）
					Select_Effect_Alpha += pressBlinkSpeed;

					if (Select_Effect_Alpha >= 255.0f) {
						//　上限に達したら255で止めて今度は暗くする

						Select_Effect_Alpha = 255.0f;
						pressBlinkIncreasing = false;

					}

				}
				else {

					//　暗くしていくフェーズ（α値を減らす）
					Select_Effect_Alpha -= pressBlinkSpeed;

					if (Select_Effect_Alpha <= 0.0f) {
						//　加減に達したら０で止めて、また明るくするフェーズへ
						Select_Effect_Alpha = 0.0f;
						pressBlinkIncreasing = true;
					}
				}
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
		logo_Alpha -= 5;
		T_Prees_Enter_Alpha -= 5;
		Select_Effect_Alpha -= 5;


		// 透明度の下限チェック

		//　タイトルロゴ
		if (logo_Alpha <= 0) logo_Alpha = 0; 
	
		//　タイトルテキストロゴ
		if (logo_Alpha <= 0) T_Prees_Enter_Alpha = 0;

		//　タイトルエフェクト
		if (logo_Alpha <= 0) Select_Effect_Alpha = 0;

		// 完全に消えたら次のフェーズへ
		if (logo_Alpha == 0&& T_Prees_Enter_Alpha ==0) {

			select_effect_Y = 170;

			currentTitlePhase = TitlePhase::MenuFadein;
			
		}

		break;

	case TitlePhase::MenuFadein:

		Menu_Text_Alpha += 5;

		Select_Effect_Alpha += 5;

		if (Menu_Text_Alpha >= 255) Menu_Text_Alpha = 255;

		if (Select_Effect_Alpha >= 255) Select_Effect_Alpha = 255; 


		if (Select_Effect_Alpha == 255&& Menu_Text_Alpha == 255) {


			currentTitlePhase = TitlePhase::MenuSelect;
		}

		break;

	case TitlePhase::MenuSelect:

		//　キー入力の受付


		//　Sキーが押された時、Select_Effect_Alphaの値を徐々に下げる→Y軸を移動（下）→Select_Effect_Alphaの値を徐々に上げる・これらを行ってエフェクトのY軸移動を行う
		if (InputManager::GetInstance().IsTrigger(KEY_INPUT_S)) {

			currentTitlePhase = TitlePhase::MenuSelect_S;

			select_effect_flag = false;

		}

		//　Wキーが押された時、Select_Effect_Alphaの値を徐々に下げる→Y軸を移動（上）→Select_Effect_Alphaの値を徐々に上げる・これらを行ってエフェクトのY軸移動を行う
		if (InputManager::GetInstance().IsTrigger(KEY_INPUT_W)) {

			currentTitlePhase = TitlePhase::MenuSelect_W;

			select_effect_flag = false;
		}

		break;

	case TitlePhase::MenuSelect_S:


		if (!select_effect_flag) {
			//　effectのalpha値を下げる
			Select_Effect_Alpha -= 20;

		}
		
		//　完全に消えたら
		if (Select_Effect_Alpha <= 0) {

			Select_Effect_Alpha == 0;

			//　エフェクトの表示状態を管理するフラグをTRUEにする
			select_effect_flag = true;

			//　Y軸の移動を行う
			select_effect_Y += 100;
		}

		if (select_effect_flag) {
			//　effectのalpha値を徐々に上げる
			Select_Effect_Alpha += 20;

		}

		//　SelectAlphaの上限管理＆フラグをfalseに戻す
		if (Select_Effect_Alpha >= 255 && select_effect_flag) {

			Select_Effect_Alpha = 255;

			currentTitlePhase = TitlePhase::MenuSelect;

		}

		//　effectの移動可能数値を超えようとした時値の維持
		if (select_effect_Y >= 470) select_effect_Y = 470; 
		break;


	case TitlePhase::MenuSelect_W:


		if (!select_effect_flag) {
			//　effectのalpha値を下げる
			Select_Effect_Alpha -= 20;

		}

		//　完全に消えたら
		if (Select_Effect_Alpha <= 0) {

			Select_Effect_Alpha == 0;

			//　エフェクトの表示状態を管理するフラグをTRUEにする
			select_effect_flag = true;

			//　Y軸の移動を行う
			select_effect_Y -= 100;
		}

		if (select_effect_flag) {
			//　effectのalpha値を徐々に上げる
			Select_Effect_Alpha += 20;

		}

		//　SelectAlphaの上限管理＆フラグをfalseに戻す
		if (Select_Effect_Alpha >= 255 && select_effect_flag) {

			Select_Effect_Alpha = 255;

			currentTitlePhase = TitlePhase::MenuSelect;

		}

		//　effectの移動可能数値を超えようとした時値の維持
		if (select_effect_Y <= 170) select_effect_Y = 170;
	
		break;

	}

}

//　アップデート関数Game
void GameManager::UpdateGame() {





}

//　アップデート関数End
void GameManager::UpdateEnd() {

}

// シーン変更
void GameManager::ChangeScene(SceneType next) {
	currentScene = next;
}

//　TITLE画面のDraw関数
void GameManager::DrawTitle()
{

	//　タイトルのフェーズ状態で描画する物を分ける
	switch (currentTitlePhase) {

		//　PressAny　最初の画面の時
	case TitlePhase::PressAny:

		TitleLogo();

		SelectEffect();

		DrawPressEnterKey();

		DrawTitleAnim();

		break;


		//　キーが押された時のフェードアウト
	case TitlePhase::PressFadeOut:

		TitleLogo();

		SelectEffect();

		DrawPressEnterKey();

		DrawTitleAnim();

	
		break;


		//　キーが押された時のフェードイン
	case TitlePhase::MenuFadein:

		TitleLogo();

		SelectEffect();

		TitleMenuText();

		DrawTitleAnim();


		break;

		//　タイトルメニュー状態の時
	case TitlePhase::MenuSelect:

		TitleLogo();

		SelectEffect();

		TitleMenuText();

		DrawTitleAnim();

		break;


	case TitlePhase::MenuSelect_S:

		TitleLogo();

		SelectEffect();

		TitleMenuText();

		DrawTitleAnim();


		break;


	case TitlePhase::MenuSelect_W:

		TitleLogo();

		SelectEffect();

		TitleMenuText();

		DrawTitleAnim();


		break;

	}

}

// TITLE時の画面描画
void GameManager::TitleLogo() {



	DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, titleBG, TRUE);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)logo_Alpha);



	DrawGraph(700, 40, cloud_2, TRUE);



	DrawGraph(390, -50, keinai, TRUE);

	DrawGraph(390, 150, cloud_1, TRUE);



	DrawGraph(340, 300, title_hund1, TRUE);

	DrawGraph(790, 20, title_hund2, TRUE);


	DrawGraph(340, 450, kusa_1, TRUE);

	DrawGraph(820, 300, kusa_2, TRUE);


	bool isDistort = title_flag || title_flag2;

	if (!isDistort) {
		DrawGraph(445, 10, titleLogo, TRUE);
	}
	else {

		DrawGraph(445, 10, titleLogo2, TRUE);
	}




	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す











	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70); // 透明度50%

	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す




}

//　TITLE時の項目セレクトエフェクト
void GameManager::SelectEffect() {


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)Select_Effect_Alpha);


	title_effect.Draw(510, select_effect_Y, Select_Effect_Alpha);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す


}

// TITLE時のアニメーション描画
void GameManager::DrawTitleAnim() {


	movenoize.Draw(0, 0, 20);


	hibana.Draw(0, 300, 255);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 15); // 透明度50%



	noize.Draw(0, noiseY, 255);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す

}

//　TITLE時のメニューセレクト関係の描画
void GameManager::TitleMenuText() {


	//　テキスト画像描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)Menu_Text_Alpha);

	//　NewGame
	DrawGraph(510, 200, NewGame, TRUE);

	//　TestPlay
	DrawGraph(510, 300, TestPlay, TRUE);

	// Option 
	DrawGraph(510, 400, Option, TRUE);

	// Exit
	DrawGraph(510, 500, Exit, TRUE);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す

}

//　TITLE時のDrawPressEnterKey描画
void GameManager::DrawPressEnterKey() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)T_Prees_Enter_Alpha);


	DrawGraph(510, 460, PressEnterKey, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す

}

//　ゲーム中のDraw関数
void GameManager::DrawGame() {

}

//　エンディングのDraw関数
void GameManager::DrawEnd() {

}

// ゲームの初期化
void GameManager::GameInit() {


	// フェードの初期化
	fader.Init();

	// フェードイン開始
	fader.StartFadeIn(6);



	/// <summary>
	/// ////////////////////////////////////////////////////////////////////////////////////
	/// 
	/// 画像の読み込み
	/// 
	/// </summary>
	// アニメーションの初期化
	hibana.Init("titlehibana", 99, 1, 3, "delay-0.04s", 2.3f);

	noize.Init("titlenoize", 88, 2, 1, "delay-0.033333333333333s", 6.0f);

	movenoize.Init("movenoize", 89, 3, 2, "delay-0.033333333333333s", 6.0f);

	title_effect.Init("title_effect", 89, 2, 2, "delay-0.041666666666667s", 1.1f);

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


	/// <summary>
	/// ////////////////////////////////////////////////////////////////////////////////////////
	/// 
	/// 画像の読み込み
	/// 
	/// </summary>


	// タイトルBGMの再生
	PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP);


	ChangeVolumeSoundMem(160, titleBGM);  // 1フレームで音量180にする

	//　タイトルメニュー画像の透明度変数


	menualpha = 0.0f;

	select_effect_Y = 430;



}

//ゲームの更新
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


		UpdateLogoDistortion();

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
				title_flag = true;


				noiseY = -200;  // ノイズが自然に上から降ってくるように見える
			}
			else {
				title_flag = false;
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

// ゲームの描画
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

// ゲームの終了処理
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

// ロゴの歪み更新
void GameManager::UpdateLogoDistortion()
{

	//　歪み中

	if (title_flag2) {

		distortTimer -= 1;



		if (distortTimer <= 0.0f) {

			title_flag2 = false;


			distortInterval = GetRand(120) + 30;

		}
	}
	else
	{
		distortInterval -= 1;

		if (distortInterval <= 0.0f)
		{


			title_flag2 = true;


			distortTimer = GetRand(10) + 2;
		}


	}


}
