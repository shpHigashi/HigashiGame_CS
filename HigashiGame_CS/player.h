#pragma once
#include "Vec2.h"

// プレイヤークラス
class Player
{
public:
	Player();
	virtual ~Player() {}

	// プレイヤーの初期化
	virtual void init();
	// プレイヤーの画像セット
	virtual void setHandle(int playerHandle, int playerDeadHandle);
	// プレイヤーの音データセット
	virtual void setSound(int revSound);
	// プレイヤーの座標設定
	virtual void setPos(float x, float y);

	// プレイヤーの更新処理
	virtual void update();
	// プレイヤーの描画処理
	virtual void draw();

	// プレイヤーの中心座標取得
	virtual float getCenterX(){ return m_pos.x + (m_width / 2); }
	virtual float getCenterY(){ return m_pos.y + (m_height / 2); }

	// m_isDead を true にする
	virtual void setDead() { m_isDead = true; }
	// m_isDead を取得
	virtual bool isDead() { return m_isDead; }

	// 当たり判定用に四方向の座標取得　
	float getLeft()	const { return m_pos.x; }
	float getRight()	const { return m_pos.x + static_cast<float>(m_width); }
	float getTop()	const { return m_pos.y; }
	float getBottom() const { return m_pos.y + static_cast<float>(m_height); }
	
	// プレイヤーの座標取得
	Vec2 getPos() const { return m_pos; }

private:
	// 音データ
	int m_revSound;
	int m_deathSound;
	
	// 画像データ
	int m_aliveHandle;	// 生

	// 画像サイズ
	int m_height;
	int m_width;

	// 表示位置
	Vec2 m_pos;

	// 移動量
	Vec2 m_vec;

	// 画像反転判定
	bool m_isReverseSide;
	bool m_isReverseLength;

	// 死亡判定
	bool m_isDead;
};