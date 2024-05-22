#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() 
{
	// 3Dモデルデータの解放
	delete model_;
	delete modelBlock_;

	for (WorldTransform* worldTransformBlock : worldTransformBlocks_)
	{
		delete worldTransformBlock;
	}
	worldTransformBlocks_.clear();

	// デバックカメラの解放
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();
	modelBlock_ = Model::Create();

	// 
	viewProjection_ = 

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 要素数
	//const uint32_t kNumBlockVirtical=10;
	const uint32_t kNumBlockHorizontal = 20;
	// ブロック１個分の横幅
	const float kBlockWidth = 2.0f;
	//const float kBlockHeight = 2.0f;
	// 要素数を変更する
	/*worldTransformBlocks_.resize(kNumBlockvirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	{

	}*/

	worldTransformBlocks_.resize(kNumBlockHorizontal);

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockHorizontal; ++i)
	{
		worldTransformBlocks_[i] = new WorldTransform();
		worldTransformBlocks_[i]->Initialize();
		worldTransformBlocks_[i]->translation_.x = kBlockWidth * i;
		worldTransformBlocks_[i]->translation_.y = 0.0f;
	}
}

void GameScene::Update() {

	// ブロック更新
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_)
	{
		//==========
		// アフィン変換行列
		//==========

		worldTransformBlock->UpdateMatrix();

		// 定数バッファに転送する
		worldTransformBlock->TransferMatrix();
	}

	// デバックカメラの更新
	debugCamera_->Update();

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE))
	{
		isDebugCameraActive_ = true;
	}
	#endif

	// カメラの処理
	//if (isDebugCameraActive_)
	//{
	//	debugCamera_->Update();
	//	viewProjection_.matView　=　デバッグカメラのビュー行列
	//	viewProjection_.matProjection　=　デバックカメラのプロジェクション行列
	//	// ビュープロジェクション行列の転送
	//	viewProjection_.TransferMatrix();
	//}
	//else
	//{
	//	// ビュープロジェクション行列の更新と転送
	//	viewProjection_.UpdateMatrix();
	//}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// ブロックの描画
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_)
	{
		modelBlock_->Draw(*worldTransformBlock,viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
