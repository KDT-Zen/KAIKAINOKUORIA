#pragma once


#include "Scene.h"
#include "FadeManager.h"
#include "Animation.h"


// タイトルフェーズ
enum class TitlePhase {

	// タイトルフェーズ
	PressAny,

	// フェードアウト中
	PressFadeOut,

	// フェードイン中
	MenuFadein,

	// メニュー選択中
	MenuSelect,

	//　メニューの項目選択状態の変更　（上）
	MenuSelect_W,


	//　メニューの項目選択状態の変更　（下）
	MenuSelect_S

};


class GameManager {

public:

	// シングルトンインスタンス取得　参照で返す
	static GameManager& GetInstance();

	int fadeDir = 0;

	//　タイトル背景
	int titleBG;

	//　タイトル背景ぼかし
	int titleBG_bokasi;

	//　タイトルロゴ
	int titleLogo;

	//　タイトルロゴ（歪）
	int titleLogo2;

	//　タイトルロゴ境内）
	int keinai;

	//　タイトル（ノイズ演出）
	int titlenoize;

	//　タイトルロゴ（手）
	int title_hund1;

	//　タイトルロゴ（手右上）
	int title_hund2;

	//　タイトルロゴ（左下）
	int cloud_1;

	//　タイトルロゴ（右上）
	int cloud_2;

	//　タイトルロゴ（草）
	int kusa_1;

	//　タイトルロゴ（右上草）
	int kusa_2;

	//　タイトルBGM
	int titleBGM;

	//　タイトル項目
	int NewGame;

	//タイトル項目
	int Option;

	//　タイトル項目
	int Exit;

	//　タイトル項目
	int TestPlay;

	//　タイトル項目
	int PressEnterKey;


	//　タイトルロゴランダム歪用のFlag

	//　歪んでいないタイトルロゴの表示を切り替えるFlag
	bool title_flag = false;

	//　歪んでるタイトルロゴの表示を切り替えるFlag
	bool title_flag2 = false;

	//　タイトルの選択項目のエフェクトの透明度切り替えを管理するFlag
	bool select_effect_flag = false;

	//　歪を管理する変数
	float distortTimer = 0.0f;

	float distortInterval = 0.0f;

	int noiseY = 0;          // ノイズの描画Y位置

	int noiseMoveCounter = 0; // ノイズ移動用のカウンタ

	int noiseTimer = 0;

	//　タイトルの項目選択エフェクトのY軸変数
	int select_effect_Y = 0;



	void GameInit();

	void GameUpdate();

	void GameDraw();

	void GameEnd();

	void ChangeScene(SceneType next);

	void UpdateLogoDistortion();

private:

	//　PressEnterKey 用の点滅アルファ値
	float T_Prees_Enter_Alpha = 0.0f;

	//　今明るくなっている最中かどうか（true =　フェードイン中/　false　= フェードアウト）
	bool pressBlinkIncreasing = true;

	//　点滅の速さ（数値をあげると点滅が早くなる）
	float pressBlinkSpeed = 3.0f;

	// メニュー透明度画像変数
	float menualpha = 0.0f;

	//　タイトル項目透明度変数
	float Select_Effect_Alpha = 0.0f;

	// ロゴ透明度変数
	float logo_Alpha = 0.0f;

	//　タイトルメニュー全体のアルファ値を管理する変数
	float Menu_Text_Alpha = 0.0f;

	//　ぼかし背景のアルファ値管理

	float BG_Bokasi_Alpha = 0.0f;





	////　キー入力待ち画像透明度変数
	//float pressAlpha = 0.0f;

	// ロゴフェード開始フラグ
	bool startLogofade = false;

	//　タイトル
	TitlePhase titlephase;

	//　アニメーション

	Animation hibana;

	Animation noize;

	Animation movenoize;

	Animation title_effect;

	FadeManager fader;

	//	コンストラクタ・デストラクタをデフォルト化
	GameManager() = default;
	~GameManager() = default;

	//	コピーコンストラクタ・代入演算子を削除
	GameManager(const GameManager&) = delete;

	GameManager& operator=(const GameManager&) = delete;

	SceneType currentScene = SceneType::TITLE;

	TitlePhase currentTitlePhase = TitlePhase::PressAny;

	bool prevSpace = false;

	void UpdateTitle();

	void UpdateGame();

	void UpdateEnd();

	void DrawTitle();

	void TitleLogo();

	void SelectEffect();

	void MoveNoizeEffect();

	void DrawPressEnterKey();

	void DrawTitleAnim();

	void DrawFadeOut();

	void DrawFadeIn();

	void TitleMenuText();

	void DrawGame();

	void DrawEnd();





};
