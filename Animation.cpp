#include "Animation.h"

Animation::Animation()
{

	frameCount = 0;

	current = 0;

	wait = 0;

	counter = 0;

}


Animation::~Animation()
{
	// 読み込んだ画像を解放

	for (int h : frames) {


		if (h != -1) {
			DeleteGraph(h);
		}
	}
}

void Animation::Init(const std::string& floderPath, int frameCount, int wait, int digit, const std::string& delayStr, float scale)
{

	this->frameCount = frameCount;

	this->wait = wait;

	this->counter = 0;

	this->current = 0;

	this->folderPath = folderPath;      // フォルダ名

	this->digit = digit;                // 桁数（2 or 3）

	this->delayStr = delayStr;          // delay 部分（文字列）

	this->scale = scale;

	frames.resize(frameCount);


	// 画像の読み込み

	for (int i = 0; i < frameCount; i++) {

		//char path[256];

		//sprintf_s(path, "%s/frame_%03d_delay-0.04s.png", floderPath.c_str(), i);


		char format[128];
		char path[256];

		// ★ digit に合わせて、2桁でも3桁でも対応できるフォーマットを生成
		// 例) digit = 2 → "%s/frame_%02d.png"
		//     digit = 3 → "%s/frame_%03d.png"
		sprintf_s(format, "%%s/frame_%%0%dd_%s.png", digit, delayStr.c_str());

		// ★ 実際のパスを生成
		sprintf_s(path, format, floderPath.c_str(), i);

		frames[i] = LoadGraph(path);





	}
}

void Animation::Update() {

	counter++;

	if (counter >= wait) {

		counter = 0;

		current++;

		if (current >= frameCount) {

			current = 0;

		}

	}

}

void Animation::Draw(int x, int y,int alpha) {

	int w, h;
	GetGraphSize(frames[current], &w, &h);


	int dw = (int)(w * scale);

	int dh = (int)(h * scale);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawExtendGraph(x, y, x + dw, y + dh, frames[current], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
