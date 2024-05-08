#include "Model.h"
#include "WorldTransform.h"

class Player{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Intialize();

	/// <summary>
	/// ������
	/// </summary>
	void Update();

	/// <summary>
	/// ������
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