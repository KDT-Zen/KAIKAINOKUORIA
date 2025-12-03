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
	MenuSelect

};


class GameManager {

public:

	// シングルトンインスタンス取得　参照で返す
	static GameManager& GetInstance();

	int fadeDir = 0;

	int titleBG;

	int titleLogo;

	int titleBGM;

	int NewGame;

	int Option;

	int Exit;

	int TestPlay;

	int PressAnyButton;

	int noiseY = 0;          // ノイズの描画Y位置
	int noiseMoveCounter = 0; // ノイズ移動用のカウンタ

	int noiseTimer = 0;


	void GameInit();

	void GameUpdate();

	void GameDraw();

	void GameEnd();

	void ChangeScene(SceneType next);



private:

	// メニュー透明度画像変数
	float menualpha = 0.0f;


	//　キー入力待ち画像透明度変数
	float pressAlpha = 0.0f;


	TitlePhase titlephase;

	Animation hibana;

	Animation noize;

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

	void DrawGame();

	void DrawEnd();





};
