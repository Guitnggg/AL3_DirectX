#include "DeathParticles.h"
#include "mymath.h"
#include <numbers>

void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	// ƒ[ƒ‹ƒh•ÏŠ·‚Ì‰Šú‰»
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
}

void DeathParticles::Update()
{
}

void DeathParticles::Draw()
{
}
