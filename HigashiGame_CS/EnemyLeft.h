#pragma once

#include "EnemyBase.h"

// 左から出現する敵用のクラス
class EnemyLeft : public EnemyBase
{
public:
	EnemyLeft() {}
	virtual ~EnemyLeft() {}

	// 敵の出現位置を設定
	virtual Vec2 getRandPos();

	// 敵の更新更新
	virtual void update();
};