#include "DxLib.h"
#include "EnemyBase.h"
#include "game.h"

namespace
{
    // 基本移動速度
    constexpr float kMoveSpeed = 6.0f;
    // 敵の初期化位置
    constexpr float kSetPos = 0.0f;
    // 敵の移動速度の下限、上限
    constexpr int kSpeedLimitMax = 12;
    constexpr int kSpeedLimitMin = 5;
}

EnemyBase::EnemyBase()
{
    m_handle = -1;
    m_height = 0;
    m_width = 0;

    m_angle = 0.0f;

    m_isExist = false;
}

//**************************************
// 初期化
// 敵の移動速度と座標を初期位置に設定
//**************************************
void EnemyBase::init()
{
    m_vec.x = kMoveSpeed;
    m_vec.y = 0.0f;
    
    m_pos.x = kSetPos;
    m_pos.y = kSetPos;

    m_isExist = false;
}

// 画像のセット
void EnemyBase::setHandle(int handle)
{
    m_handle = handle;
    GetGraphSize(m_handle, &m_width, &m_height);
}

//***************************************************************************************
// 敵の出現処理
// 引数 pos : 敵の出現位置を引数として取得しm_posに代入
// 敵が存在しているかを true にし、x座標の移動速度を乱数で取得し m_vec.x に代入
//***************************************************************************************
void EnemyBase::start(Vec2 pos)
{
    m_isExist = true;
    m_pos = pos;
    m_vec.x = static_cast<float>(GetRand(kSpeedLimitMax)) + kSpeedLimitMin;
}

// 敵の更新処理
void EnemyBase::update()
{
    if (!m_isExist) return;
}

// 敵の描画処理
void EnemyBase::draw()
{
    DrawRotaGraphF(getCenterX(), getCenterY(), 1.0, m_angle, m_handle, true, false);
}