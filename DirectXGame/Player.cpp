#include "Player.h"
#include <cassert>

void Player::Inttialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection)
{
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
	
	worldTransform_.Initialize();	
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