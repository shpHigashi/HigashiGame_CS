#pragma once

#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneClear.h"

class SceneManager
{
public:
	// シーンの種類定義
	typedef enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
		kSceneKindClear,

		kSceneKindNum
	}SceneKind;

public:
	SceneManager();
	virtual ~SceneManager();

	// 初期化
	void init(SceneKind kind = kSceneKindTitle);
	// 削除
	void end();

	// 更新
	void update();
	// 描画
	void draw();

	// m_isMusicEnd を取得
	bool isGameMusicEnd() { return m_isMusicEnd; }

private:
	// ゲーム終了
	bool m_isMusicEnd;
	
	SceneKind	m_kind;

	SceneTitle	m_title;
	SceneMain	m_main;
	SceneClear	m_clear;

	Player m_player;
};