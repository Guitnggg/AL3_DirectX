#include "DeathParticles.h"
#include "mymath.h"
#include <numbers>

void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
}

void DeathParticles::Update()
{
	// 行列計算
	worldTransform_.UpdateMatrix();
}

void DeathParticles::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
