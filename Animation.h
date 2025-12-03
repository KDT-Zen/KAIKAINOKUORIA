#pragma once



#include "DxLib.h"

#include<vector>

#include <string>

class Animation {

public:
	Animation();
	~Animation();


	// アニメーション初期化 フォルダーパス、フレーム数、待機時間
	void Init(const std::string& floderPath, int frameCount, int wait, int digit, const std::string& delayStr, float scale = 1.0f);

	//更新と描画

	void Update();

	void Draw(int x, int y);

	int GetFrame(int index) const { return frames[index]; }

private:
	std::vector<int>frames; // 読み込んだ画像のハンドルを格納する配列

	int frameCount; // フレーム数

	int current;    // 現在のフレーム

	int wait;       // 待機時間

	int counter;     // 待機時間用カウンター

	float scale;


	int digit;                      // ★ 桁数（2桁 or 3桁）
	std::string delayStr;           // ★ delay の文字列（例: "delay-0.033333333333s"）
	std::string folderPath;         // ★ 画像フォルダ名（Load 用）
};