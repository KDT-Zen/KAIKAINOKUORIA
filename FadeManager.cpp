#include "FadeManager.h"
#include "DxLib.h"
#include "GameDefine.h"

void FadeManager::Init() {

	alpha = 0;    //　完全に透明

	dir = 0;      //　止まっている

	speed = 5;
}

void FadeManager::StartFadeIn(int sp) {

	speed = sp;

	alpha = 255;  //最初は真っ黒

	dir = -1;     //黒→　透明　


}

void FadeManager::StartFadeOut(int sp) {

	speed = sp;

	alpha = 0;   //最初は透明

	dir = 1;    //透明→　黒　


}

void FadeManager::Update() {

	if (dir == 0) return; //フェードしていない

	alpha += dir * speed;

	//透明→　黒に向かうとき
	if (alpha >= 255) {

		alpha = 255;

		dir = 0;
	}

	//黒→　透明に向かうとき
	if (alpha <= 0) {

		alpha = 0;

		dir = 0;

	}

}



void FadeManager::Draw() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);


	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);



	//　合成完了

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

//　フェード中かどうか

bool FadeManager::IsFading()const {
	return dir != 0;


}