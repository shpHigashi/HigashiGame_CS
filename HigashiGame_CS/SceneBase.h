#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	// 初期化
	virtual void init() {}
	// 削除
	virtual void end() {}
	// 更新
	virtual void update() {}
	// 描画
	virtual void draw() {}

	// シーン終了
	virtual bool isEnd() { return false; }
};