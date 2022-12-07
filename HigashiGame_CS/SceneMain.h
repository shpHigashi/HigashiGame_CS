#pragma once

#include "player.h"
#include "EnemyRight.h"
#include "EnemyLeft.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	void init();
	// 終了処理
	void end();

	// 毎フレームの処理
	void update();
	// 毎フレームの描画
	void draw();
	// 当たり判定チェック処理
	void checkCollision();

	// 敵の生成
	void createEnemyRight();
	void createEnemyLeft();

	// m_isGameClearを取得
	virtual bool isGameClear() { return m_isGameClear; }
	// m_isEndを取得
	virtual bool isEnd() { return m_isEnd; }

private:
	// 片側の敵の最大出現数
	static constexpr int kEnemyMax = 10;

private:
	// 音データ
	int m_revSound;
	int m_deathSound;
	// 一度だけ再生
	bool m_playOnceOnly;
	
	// 背景のグラフィックハンドル
	int m_hBackgroundGraphic;
	// キャラクターのグラフィックハンドル
	int m_hPlayerGraphic;
	int m_hPlayerDeadGraphic;
	// 敵のグラフィックハンドル
	int m_hEnemyGraphic;

	// フォントサイズ
	int m_fontSize;

	// ゲームの制限時間
	int m_gameTimeRemaining;
	// ゲームオーバー時の遅延時間
	int m_GameOverDelay;
	// 敵の出現遅延
	int m_spawnDelay;

	// ゲームクリア
	bool m_isGameClear;

	// シーン終了
	bool m_isEnd;

	// プレイヤー
	Player m_player;

	// 敵
	EnemyRight m_EnemyRight[kEnemyMax];
	EnemyLeft m_EnemyLeft[kEnemyMax];
};