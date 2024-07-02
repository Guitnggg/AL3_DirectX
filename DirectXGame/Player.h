#include "Model.h"
#include "WorldTransform.h"

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Inttialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 初期化
	/// </summary>
	void Update();

	/// <summary>
	/// 初期化
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
};