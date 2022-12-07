#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウィンドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲーム終了判定用の変数作成
	int isGameMusicEnd = false;

	SceneManager scene;

	// 画像のロード
	scene.init();

	int backgroundSound = -1;
	backgroundSound = LoadSoundMem(Game::kGameMainMusic);

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面のクリア
		ClearDrawScreen();

		if(!CheckSoundMem(backgroundSound)) PlaySoundMem(backgroundSound, DX_PLAYTYPE_BACK);

		// 現在のシーンの更新
		scene.update();

		// 現在のシーンの描画
		scene.draw();

		// ゲーム終了判定
		isGameMusicEnd = scene.isGameMusicEnd();
		// isGameEndが true の場合BGM停止
		if (isGameMusicEnd)
		{
			StopSoundMem(backgroundSound);
		}

		// 裏画面を表画面と入れ替える
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	// 画像のアンロード
	scene.end();
	DeleteSoundMem(backgroundSound);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}