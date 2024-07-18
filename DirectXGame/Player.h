#pragma once

#include "Model.h"
#include "WorldTransform.h"

// 前方宣言
class MapChipField;

class Player {
public:
    void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

    void Update();
    
    void Draw();

    void InputMove();

    const WorldTransform& GetWorldTransform() const { return worldTransform_; }
    const Vector3& GetVelocity() const { return velocity_; }

    void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

    struct CollisionMapInfo
    {
        bool isCelling = false;
        bool isGrounding = false;
        bool isHitWall = false;
        Vector3 move;
    };

private:
    WorldTransform worldTransform_;
    Model* model_ = nullptr;
    uint32_t textureHandle_ = 0u;
    ViewProjection* viewProjection_ = nullptr;
  
    Vector3 velocity_ = {};
    
    enum class LRDirection { kRight, kLeft };
    
    float turnFirstRotationY_ = 0.0f;
   
    float turnTimer_ = 0.0f;
   
    static inline const float kAcceleration = 0.1f;
    static inline const float kAttenuation = 0.2f;
    static inline const float kLimitRunSpeed = 5.0f;
    static inline const float kTimeTurn = 0.3f;
   
    LRDirection lrDirection_ = LRDirection::kRight;
  
    bool onGround_ = true;
  
    static inline const float kGravityAcceleration = 0.8f;
    static inline const float kLimitFallSpeed = 1.0f;
    static inline const float kJumpAcceleration = 5.0f;

    // マップチップによるフィールド
    MapChipField* mapChipField_ = nullptr;

    // キャラクターの当たり判定サイズ
    static inline const float kWidth = 0.8f;
    static inline const float kHeight = 0.8f;
};
