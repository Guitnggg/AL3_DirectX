#include "Player.h"
#include <cassert>

void Player::Inttialize(Model*model, uint32_t textureHandle, ViewProjection viewProjection_)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する


	// ワールド変換の初期化
	
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