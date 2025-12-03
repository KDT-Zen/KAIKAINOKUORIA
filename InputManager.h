#pragma once




#include "DxLib.h"

class InputManager
{
public:

	//　シングルトン　唯一のインスタンスを返す関数
	static InputManager& GetInstance();

	//　全キー状態を更新する処理
	void Update();

	//　キーが押されている間trueを返す
	bool IsPress(int key);

	//　キーが押された瞬間だけtrueを返す
	bool IsTrigger(int key);

	//　キーが離された瞬間trueを返す
	bool IsRelease(int key);

private:

	//　自動生成を許可して外からnew出来なくする（シングルトン）
	InputManager() = default;


	//　現在のフレームのキーを状態を保持する配列
	char currentKey[256]{};

	//　前フレームのキー状態を保持する配列。前は押してなかった→今は押した　という判定に使う
	char previousKey[256]{};




};