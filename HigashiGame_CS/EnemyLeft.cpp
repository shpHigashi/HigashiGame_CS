#include "EnemyLeft.h"
#include "game.h"
#include "DxLib.h"

namespace
{
    // 画像の回転速度
    constexpr float kRotaSpeed = 0.3f;
}

//************************************************************************
// 敵の出現位置を設定
// x座標 : 画面左端の座標(0.0f)を代入
// y座標 : ステージ範囲内でランダムに座標を取得しfloat型に変換し代入
//************************************************************************
Vec2 EnemyLeft::getRandPos()
{
    m_pos.x = 0.0f;
    m_pos.y = static_cast<float>(GetRand((Game::kStageLowerLimit - m_height) - Game::kStageUpperLimit) + Game::kStageUpperLimit);

    return m_pos;
}

// 敵の更新処理
void EnemyLeft::update()
{
    // 現在の座標に移動量を代入
    m_pos += m_vec;

    // 画像の回転用
    m_angle += kRotaSpeed;
    
    // 画面右端まで行くと敵の存在を false にする
    if (m_pos.x > Game::kScreenWidth)
    {
        m_isExist = false;
    }
}