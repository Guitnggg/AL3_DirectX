#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <array>

/// <summary>
/// デス演出用パーティクル
/// </summary>
class DeathParticles
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;

	// パーティクルの個数
	static inline const uint32_t kNumParitcles = 8;
	std::array<WorldTransform, kNumParitcles>worldTransforms_;

	static inline const float kDeathParticlesSpeed = 0.1f;
};

