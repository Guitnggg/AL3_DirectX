#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "myMath.h"

/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;
	
	Player* player_ = nullptr;


	Vector3 velocity_ = {};
	static inline const float kAcceleration = 1.0f;
	static inline const float kAttenuation = 1.0f;
	static inline const float kLimitRunSpeed = 30.0f;
	static inline const float kTimeTurn = 0.3f;

	enum class LRDirection
	{
		kRight,
		kLeft
	};

	LRDirection lrDirection_ = LRDirection::kRight;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;

};

