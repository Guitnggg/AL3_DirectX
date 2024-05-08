#include "Model.h"
#include "WorldTransform.h"

class Player{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Intialize();

	/// <summary>
	/// 初期化
	/// </summary>
	void Update();

	/// <summary>
	/// 初期化
	/// </summary>
	void Draw();

private:
	// 
	WorldTransform worldTransform_;

	// 
	Model*model=nullptr;

	// 
	uint32_t textureHandle_=0u;
};