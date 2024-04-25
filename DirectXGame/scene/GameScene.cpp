#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを呼び出す
	textureHandle_=TextureManager::Load("mario.jpg");
	// スプライトの生成
	sprite_=Sprite::Create(textureHandle_, {100, 50});

	// 3Dモデルの生成
	model_=Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewPrejection_.Initialize();

	// サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");

	// 音声再生（第二引数でループするか指定できる）
	audio_->PlayWave(soundDataHandle_, true);

	// ライン描画が参照するビュープロジェクションを指定する
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewPrejection_);

	// デバックカメラの生成
	debugCamera_=new DebugCamera(1280,720);

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {

	// スプライトの今の座標を取得
	Vector2 position=sprite_->GetPosition();
	// 座標を｛２，１｝移動
	position.x += 2.0f;
	position.y += 1.0f;
	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);

	// スペースキーを押したら
	if (input_->TriggerKey(DIK_SPACE)) {
		// 音声停止
		audio_->StopWave(soundDataHandle_);
	}

	// デバックテキストの表示
	ImGui::Begin("Debug1");
	ImGui::Text("Kamata Tarou %d.%d.%d",2050,12,31);
	ImGui::End();
	
	// デバックカメラの更新
	debugCamera_->Update();
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

	// 3Dモデル描画
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	// ラインを描画する
	PrimitiveDrawer::GetInstance()->DrawLine3d({0,0,0},{0,10,0},{1.0f,0.0f,0.0f,1.0f});

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	/*sprite_->Draw();*/

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
