#pragma once

namespace Game
{
	// ウィンドウモード設定
	constexpr bool kWindowMode = true;
	// ウィンドウ名
	const char* const kTitleText = "セキュリティを回避しろ！";
	// ウィンドウサイズ
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;

	const char* const kGameMainMusic = "sounddata/The Moon Theme.mp3";

	// ゲームのステージサイズ
	constexpr int kStageUpperLimit = 100;
	constexpr int kStageLowerLimit = 620;

	// カラーモード
	constexpr int kColorDepth = 32;

	// 背景用画像
	const char* const kBackgroundGraph = "imagedata/StageBackground.png";
	const char* const kPlayerGraph = "imagedata/virus_s.png";
	
	// 基準のフォントサイズ
	constexpr int kFontSize = 60;
}