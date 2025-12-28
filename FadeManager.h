#pragma once




class FadeManager {

public:

	void Init();                               // 初期化

	void StartFadeIn(int speed = 5);           // フェードイン開始（黒→透明）

	void StartFadeOut(int speed = 5);          // フェードアウト開始（透明→黒）


	void Update();                             // a値の更新

	void Draw();                               // 黒幕の描画

	bool IsFading() const;                     // フェード中かどうか

	bool IsFadingEnd() const;                 //　画面が真っ暗かどうか


private:

	int alpha;                                 //　現在の透明度（0～255）


	int dir = 0;                               //　フェード順


	int speed = 5;                             //　フェード速度



};