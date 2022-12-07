#pragma once
#include "SceneBase.h"
#include "TitleChara.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle()
	{
		m_TextPosY = 0;
		m_TextVecY = 0;

		m_isEnd = false;

		m_hCharaGraphic = -1;
		m_hBackgroundGraphic = -1;

		m_width = 0;
		m_height = 0;
	}
	virtual ~SceneTitle() {}

	// 初期化
	virtual void init();
	
	// 終了処理
	void end();

	// 更新処理
	virtual void update();
	// 描画
	virtual void draw();

	// m_isEnd を取得
	virtual bool isEnd() { return m_isEnd; }
private:	
	// テキスト表示位置変更
	int m_TextPosY;
	int m_TextVecY;

	// タイトル表示を終えるかどうか
	bool m_isEnd;

	// 画像データ
	int m_hCharaGraphic;
	int m_hBackgroundGraphic;
	// 画像サイズ
	int m_width;
	int m_height;

	// プレイヤー
	TitleChara m_tChara;
};