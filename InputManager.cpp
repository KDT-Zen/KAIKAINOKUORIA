#include "InputManager.h"

#include <cstring>


//　シングルトン
InputManager& InputManager::GetInstance()
{
	//　シングルトンのインスタンス作成
	static InputManager instance;

	//　生成したインスタンスを返す
	return instance;

}

//　キー入力の状態を更新する関数
//　押した瞬間の処理
void InputManager::Update()
{
	//　前フレームのキー状態をpreviousKeyにコピーする。差分（押した瞬間）を判定するため
	memcpy(previousKey, currentKey, 256);

	//　現在のキー状態を256子すべてcurrentKeyに取得する
	GetHitKeyStateAll(currentKey);
}

//　押されている間trueを返す
bool InputManager::IsPress(int Key) {

	//　キーが押されて入れば(1)true,押してなければ(0)false
	return currentKey[Key] != 0;

}

//　押した瞬間だけtrue
bool InputManager::IsTrigger(int key)
{
	//今押した＆前は押してなかった→押した瞬間だけtrue
	return currentKey[key] != 0 && previousKey[key] == 0;
}

//　今はなした＆前は押していた→話した瞬間だけtrue
bool InputManager::IsRelease(int key)
{

	return currentKey[key] == 0 && previousKey[key] != 0;

}

