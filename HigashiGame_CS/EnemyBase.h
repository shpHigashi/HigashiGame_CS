#pragma once
#include "Vec2.h"

// 敵基底クラス
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase() {}

	// 初期化
	virtual void init();
	// 画像のセット
	virtual void setHandle(int handle);

	// 敵の出現処理
	virtual void start(Vec2 pos);
	// 敵の更新処理
	virtual void update();
	// 敵の描画処理
	virtual void draw();

	// 敵の中心座標取得
	virtual float getCenterX() { return m_pos.x + (m_width / 2); }
	virtual float getCenterY() { return m_pos.y + (m_height / 2); }

	// 当たり判定用に四方向の座標取得　
	float getLeft()	const { return m_pos.x; }
	float getRight()	const { return m_pos.x + static_cast<float>(m_width); }
	float getTop()	const { return m_pos.y; }
	float getBottom() const { return m_pos.y + static_cast<float>(m_height); }

	// 敵が存在しているか
	bool isExist()const { return m_isExist; }

protected:
	// 画像データ
	int m_handle;

	// 画像サイズ
	int m_height;
	int m_width;

	// 表示位置
	Vec2 m_pos;

	// 移動量
	Vec2 m_vec;

	//存在するか
	bool m_isExist;

	// 画像の角度
	float m_angle;
};