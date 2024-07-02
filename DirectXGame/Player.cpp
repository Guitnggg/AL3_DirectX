#include "Player.h"
#include <cassert>
#include <numbers>

void Player::Inttialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	// NULLポインタチェック
	assert(model);

	model_ = model;
	/*textureHandle_ = textureHandle;*/
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update()
{
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}