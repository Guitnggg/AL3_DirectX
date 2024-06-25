#include "Player.h"
#include <cassert>
#include <numbers>
#include <algorithm>
#include <Input.h>

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const  Vector3& position){
	
	// NULLチェック
	assert(model);

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	// 引数の内容をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;

}

void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	//==========
	// 移動入力
	//==========

	// 左右移動操作
	if (Input::GetInstance()->PushKey(DIK_RIGHT) ||
		Input::GetInstance()->PushKey(DIK_LEFT))
	{
		//==========
		// 左右加速
		//==========

		Vector3 acceleration = {};
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
				worldTransform_.rotation_.y = turnFirstRotationY_;
				turnTimer_ = kTimeTurn;
			}
		}
		else if (Input::GetInstance()->PushKey(DIK_LEFT))
		{
			// 左移動中の右入力
			if (velocity_.x > 0.0f)
			{
				// 速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAttenuation);
			}

			acceleration.x -= kAcceleration;

			if (lrDirection_ != LRDirection::kLeft)
			{
				lrDirection_ = LRDirection::kLeft;
				worldTransform_.rotation_.y = turnFirstRotationY_;
				turnTimer_ = kTimeTurn;
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

	//==========
	// 旋回制御
	//==========
	if(turnTimer_>0.0f)
	{
		turnTimer = 1.0f / 60.0f;

		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] =
		{
			std::numbers::pi_v<float> / 2.0f,
			std::numbers::pi_v<float>*3.0f / 2.0f
		};
		// 状況に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 
		worldTransform_.rotation_.y = destinationRotationY;
	}

	//==========
	// 移動
	//==========

	worldTransform_.translation_ += velocity_;
	
	//==========
	// 行列計算
	//==========

	worldTransform_.UpdateMatrix();
}

void Player::Draw(){

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}