#include "CamaraController.h"
#include "Player.h"
#include <algorithm>

void CamaraController::Initialize()
{
	viewProjection_.Initialize();
}

void CamaraController::Update()
{
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	// 追従対象とオフセットからカメラの座標を計算
	goalPosition = targetWorldTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBias;

	// 座標補間によりゆったり追従
	viewProjection_.translation_ = Lerp(viewProjection_.translation_, goalPosition, kInterPolationRate);

	// 移動範囲制限
	viewProjection_.translation_.x = std::min(viewProjection_.translation_.x, movableArea_.left + majine.left);
	viewProjection_.translation_.x = std::max(viewProjection_.translation_.x, movableArea_.right + majine.right);
	viewProjection_.translation_.y = std::min(viewProjection_.translation_.y, movableArea_.bottom + majine.bottom);
	viewProjection_.translation_.y = std::max(viewProjection_.translation_.y, movableArea_.top+majine.top);

	// 行列を更新する
	viewProjection_.UpdateMatrix();
}

void CamaraController::Reset()
{
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	// 追従対象とオフセットのカメラの座標を計算
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}
