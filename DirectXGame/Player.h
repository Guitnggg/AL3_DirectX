#include "Model.h"
#include "WorldTransform.h"

class Player{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Intialize();

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Update();

	/// <summary>
	/// ‰Šú‰»
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