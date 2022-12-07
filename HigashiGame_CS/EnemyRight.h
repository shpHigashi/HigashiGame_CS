#pragma once

#include "EnemyBase.h"

// 右から出現する敵用のクラス
class EnemyRight : public EnemyBase
{
public:
	EnemyRight() {}
	virtual ~EnemyRight() {}

	// 敵の出現位置を設定
	virtual Vec2 getRandPos();

	// 敵の更新処理
	virtual void update();
};