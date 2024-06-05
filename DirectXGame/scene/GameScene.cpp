#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() 
{
	// 3Dモデルデータの解放
	delete model_;
	delete modelBlock_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_)
	{
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine)
	    {
		    delete worldTransformBlock;
	    }
	}
	worldTransformBlocks_.clear();

	// デバックカメラの解放
	delete debugCamera_;

	// マップチップフィールドの解放
	delete mapChipField_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();
	modelBlock_ = Model::Create();

	// 
	viewProjection_.Initialize();

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// マップチップフィールド
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/map.csv");

	GemerateBlocks();

	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBloackVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	
	// ブロック１個分の横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;
	
	// 要素数を変更する
	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i)
	{
		// １列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i)
	{
		for (uint32_t j = 0; j < numBlockHorizontal; ++j)
		{
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock)
			{
				WorldTransform * worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_=mapChipField_->GetMapChipPositionByIndex(j,i);			
			}
		}
	}
}

void GameScene::Update() 
{
	// ブロック更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_)
	{
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine)
		{
			if (!worldTransformBlock)
				continue;
			
			// アフィン変換行列
		    worldTransformBlock->UpdateMatrix();

		    // 定数バッファに転送する
		    worldTransformBlock->TransferMatrix();
		}
	}

	// デバックカメラの更新
	debugCamera_->Update();

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE))
	{
		if (isDebugCameraActive_ == true)
			isDebugCameraActive_ = false;
		else 
			isDebugCameraActive_ = true;
	}
	#endif

	// カメラの処理
	if (isDebugCameraActive_)
	{
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	}
	else
	{
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
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
	for (uint32_t i = 0; i < worldTransformBlocks_.size(); ++i)
    {
        for (uint32_t j = 0; j < worldTransformBlocks_[i].size(); ++j)
        {
            WorldTransform* worldTransformBlock = worldTransformBlocks_[i][j];
            if (!worldTransformBlock)
                continue;

            // 条件に応じてブロックを描画しない
            if ((i + j) % 2 == 0) 
                continue;

            modelBlock_->Draw(*worldTransformBlock, viewProjection_);
        }
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
