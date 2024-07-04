#define NOMINMAX

#include "Player.h"
#include <cassert>
#include <numbers>
#include <algorithm>
#include "Input.h"
#include "myMath.h"

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position)
{
    assert(model);
    model_ = Model::CreateFromOBJ("Resources/player/player.obj");
    model_ = model;
    textureHandle_ = textureHandle;
    viewProjection_ = viewProjection;
    worldTransform_.Initialize();
    worldTransform_.translation_ = position;
    worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

}

void Player::Update() 
{
    worldTransform_.TransferMatrix();

    if (onGround_) 
    {
        Vector3 acceleration = {};
        if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT))
        {
            // 左右加速
            if (Input::GetInstance()->PushKey(DIK_RIGHT)) 
            {
                // 左移動中の右入力
                if (velocity_.x < 0.0f)
                {
                    // 速度と逆方向に入力中は急ブレーキ
                    velocity_.x *= (1.0f - kAttenuation);
                }
                acceleration.x += kAcceleration;

                if (lrDirection_ != LRDirection::kRight) 
                {
                    lrDirection_ = LRDirection::kRight;
                    //旋回開始時の角度を記録する
                    //旋回タイマーに時間を設定する
                }

                // 旋回制御
                if (turnTimer_ > 0.0f) 
                {
                    turnTimer_ -= 1.0f / 60.0f;
                    // 左右の自キャラ角度テーブル
                    float destinationRotationYTable[] = 
                    {
                        std::numbers::pi_v<float> / 2.0f,
                        std::numbers::pi_v<float> *3.0f / 2.0f
                    };
                    // 状態に応じた目標角度を記録する
                    float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
                    // 自キャラの角度を設定する
                    worldTransform_.rotation_.y += (destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);
                }
            }
            else if (Input::GetInstance()->PushKey(DIK_LEFT))
            {
                // 右移動中の左入力
                if (velocity_.x > 0.0f) 
                {
                    // 速度と逆方向に入力中は急ブレーキ
                    velocity_.x *= (1.0f - kAttenuation);
                }
                acceleration.x -= kAcceleration;

                if (lrDirection_ != LRDirection::kLeft)
                {
                    lrDirection_ = LRDirection::kLeft;
                    //旋回開始時の角度を記録する
                    //旋回タイマーに時間を設定する
                }

                // 旋回制御
                if (turnTimer_ > 0.0f) 
                {
                    turnTimer_ -= 1.0f / 60.0f;
                    // 左右の自キャラ角度テーブル
                    float destinationRotationYTable[] =
                    {
                        std::numbers::pi_v<float> / 2.0f,
                        std::numbers::pi_v<float> *3.0f / 2.0f
                    };
                    // 状態に応じた目標角度を記録する
                    float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
                    // 自キャラの角度を設定する
                    worldTransform_.rotation_.y += (destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);
                }
            }
            // 加速/減速
            velocity_ += acceleration;
            // 最大速度制限
            velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
        }
        else
        {
            // 非入力時は移動減衰をかける
            velocity_.x *= (1.0f - kAttenuation);
        }

        if (Input::GetInstance()->PushKey(DIK_UP))
        {
            velocity_ += Vector3{ 0, kJumpAcceleration, 0 };
        }

        worldTransform_.translation_ += velocity_;
        worldTransform_.UpdateMatrix();
    }

    //==========
    // 空中
    //==========
    else 
    {
        // 落下速度
        velocity_ += Vector3{ 0, -kGravityAcceleration, 0 };
        // 落下速度制限
        velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

        // 着地フラグ
        bool landing = false;

        // 地面との当たり判定
        // 降下中？
        if (velocity_.y < 0) 
        {
            // y座標が地面以下になったら着地
            if (worldTransform_.translation_.y <= 1.0f)
            {
                landing = true;
            }
        }

        // 着地
        if (landing) 
        {
            // めり込み排斥
            worldTransform_.translation_.y = 1.0f;
            // 摩擦で横方向速度が減衰する
            velocity_.x *= (1.0f - kAttenuation);
            // 下方向速度をリセット
            velocity_.y = 0.0f;
            // 接地状態に移行
            onGround_ = true;
        }
    }
}

void Player::Draw() {
    model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}
