#define NOMINMAX

#include "Player.h"
#include <cassert>
#include <numbers>
#include <algorithm>
#include "Input.h"
#include "MapChipField.h"
#include "myMath.h"

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
    assert(model);
    model_ = model;
    viewProjection_ = viewProjection;
    worldTransform_.Initialize();
    worldTransform_.translation_ = position;
    worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

}

void Player::Update() {
    worldTransform_.TransferMatrix();

    if (onGround_) {
        Vector3 acceleration = {};
        if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
            if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
                if (velocity_.x < 0.0f) {
                    velocity_.x *= (1.0f - kAttenuation);
                }
                acceleration.x += kAcceleration;
                if (lrDirection_ != LRDirection::kRight) {
                    lrDirection_ = LRDirection::kRight;
                }
                if (turnTimer_ > 0.0f) {
                    turnTimer_ -= 1.0f / 60.0f;
                    float destinationRotationYTable[] = {
                        std::numbers::pi_v<float> / 2.0f,
                        std::numbers::pi_v<float> *3.0f / 2.0f
                    };
                    float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
                    worldTransform_.rotation_.y += (destinationRotationY - worldTransform_.rotation_.y) * (turnTimer_ / 60.0f);
                }
            }
            else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
                if (velocity_.x > 0.0f) {
                    velocity_.x *= (1.0f - kAttenuation);
                }
                acceleration.x -= kAcceleration;
                if (lrDirection_ != LRDirection::kLeft) {
                    lrDirection_ = LRDirection::kLeft;
                }
                if (turnTimer_ > 0.0f) {
                    turnTimer_ -= 1.0f / 60.0f;
                    float destinationRotationYTable[] = {
                        std::numbers::pi_v<float> / 2.0f,
                        std::numbers::pi_v<float> *3.0f / 2.0f
                    };
                    float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
                    worldTransform_.rotation_.y += (destinationRotationY - worldTransform_.rotation_.y) * (turnTimer_ / 60.0f);
                }
            }
            else {
                velocity_.x *= (1.0f - kAcceleration);
            }

            if (Input::GetInstance()->PushKey(DIK_UP)) {
                velocity_ += Vector3{ 0, kJumpAcceleration, 0 };
                if (velocity_.y > 0.0f) {
                    onGround_ = false;
                }
            }

            velocity_ += acceleration;
            velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
        }

        worldTransform_.translation_ += velocity_;
        worldTransform_.UpdateMatrix();
    }
    else {
        velocity_ += Vector3{ 0, -kGravityAcceleration, 0 };
        velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

        bool landing = false;
        if (velocity_.y < 0) {
            if (worldTransform_.translation_.y <= 1.0f) {
                landing = true;
            }
        }

        if (landing) {
            worldTransform_.translation_.y = 1.0f;
            velocity_.y = 0.0f;
            onGround_ = true;
        }
    }
}

void Player::Draw() {
    model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}
