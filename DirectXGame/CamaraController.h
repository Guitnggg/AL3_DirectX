#pragma once

#include "ViewProjection.h"
#include "myMath.h"

// 前方宣言
class Player;

/// <summary>
/// カメラコントローラー
/// </summary>

class CamaraController
{
public:

	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	// 矩形
	struct Rect
	{
		float left = 0.0f;    // 左端
		float right = 1.0f;   // 右端
		float bottom = 0.0f;  // 下端
		float top = 1.0f;     // 上端
	};

	// カメラ移動範囲
	Rect movableArea_ = { 0,100,0,100 };

	void SetMovableArea(const Rect& area) { movableArea_ = area; }

	const ViewProjection& GetViewProjection()const { return viewProjection_; }

	const Vector3& targetVelocity = target_->GetVelocity();

private:

	// ビュープロジェクション
	ViewProjection viewProjection_;

	Player* target_ = nullptr;

	// 追従対象とカメラの座標の差
	Vector3 targetOffset_ = { 0,0,-15.0f };

	// カメラの目標座標
	Vector3 goalPosition;

	// 座標補間割合
	static inline const float kInterPolationRate = 1.5f;
	
	// 速度掛け率
	static inline const float kVelocityBias = 1.0f;

	// 追従対象の各方向へのカメラ移動範囲
	static inline const Rect majine={50,50,50,50};
};

