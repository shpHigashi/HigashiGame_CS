#include "SceneManager.h"
#include <cassert>

SceneManager::SceneManager()
{
	// タイトルのシーンから表示
	m_kind = kSceneKindTitle;

	// ゲーム終了
	m_isMusicEnd = false;
}
SceneManager::~SceneManager()
{

}

// 初期化
void SceneManager::init(SceneKind kind)
{	
	// 各シーンの初期化
	m_kind = kind;
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_title.init();	// シーンタイトルの初期化
		break;
	case SceneManager::kSceneKindMain:
		m_main.init();	// シーンメインの初期化
		break;
	case SceneManager::kSceneKindClear:
		m_clear.init();	// シーンクリアの初期化
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// 削除
void SceneManager::end()
{
	// 各シーンのデータ削除
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_title.end();	// シーンタイトルのデータ削除
		break;
	case SceneManager::kSceneKindMain:
		m_main.end();	// シーンメインのデータ削除
		break;
	case SceneManager::kSceneKindClear:
		m_clear.end();	// シーンクリアのデータ削除
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// 更新
void SceneManager::update()
{
	// 現在のシーンの更新処理を実行する
	bool isEnd = false;
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_title.update();	// シーンタイトルの更新
		isEnd = m_title.isEnd();
		break;
	case SceneManager::kSceneKindMain:
		m_main.update();	// シーンメインの更新
		isEnd = m_main.isEnd();
		break;
	case SceneManager::kSceneKindClear:
		m_clear.update();	// シーンクリアの更新
		isEnd = m_clear.isEnd();
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}

	// isEnd が true のとき、各シーンの初期化とデータ削除を行う
	if (isEnd)
	{
		switch (m_kind)
		{
		case SceneManager::kSceneKindTitle:
			m_title.end();	// シーンタイトルのデータ削除
			m_main.init();	// シーンメインの初期化
			m_kind = kSceneKindMain;
			break;
		case SceneManager::kSceneKindMain:
			// m_isGameClear が true の場合、ゲームクリアのシーンを初期化し選択
			if (m_main.isGameClear())
			{
				m_isMusicEnd = true;
				m_main.end();	// シーンメインのデータ削除
				m_clear.init();	// シーンクリアの初期化
				m_kind = kSceneKindClear;
				break;
			}
			else // それ以外の場合、タイトルのシーンを初期化し選択
			{
				m_main.end();	// シーンメインのデータ削除
				m_title.init();	// シーンタイトルの初期化
				m_kind = kSceneKindTitle;
				break;
			}
		case SceneManager::kSceneKindClear:	// シーンがゲームクリアの場合、ゲーム終了
			m_isMusicEnd = false;
			m_clear.end();	// シーンクリアのデータ削除
			m_title.init();	// シーンタイトルの初期化
			m_kind = kSceneKindTitle;
			break;
		case SceneManager::kSceneKindNum:
		default:
			assert(false);
			break;
		}
	}
}

// 描画
void SceneManager::draw()
{
	// 現在のシーンの描画処理を行う
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_title.draw();	// シーンタイトルの描画
		break;
	case SceneManager::kSceneKindMain:
		m_main.draw();	// シーンメインの描画
		break;
	case SceneManager::kSceneKindClear:
		m_clear.draw();	// シーンクリアの描画
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}