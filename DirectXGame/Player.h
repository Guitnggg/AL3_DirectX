#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

// 前方宣言
class MapChipField;

class Player {
public:

    //左右
    enum class LRDirection
    {
        kRight,
        kLeft,
    };

    // 角
    enum Corner
    {
        kRightBottom,  // 右下
        kLeftBottom,   // 左下
        kRightTop,     // 右上
        kLeftTop,      // 左上

        kNumCorner  // 要素数
    };


    void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

    void Update();
    
    void Draw();

    void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
   
    const WorldTransform& GetWorldTransform() const { return worldTransform_; }
    const Vector3& GetVelocity() const { return velocity_; }

private:
   
    Model* model_ = nullptr;
    WorldTransform worldTransform_;
    ViewProjection* viewProjection_ = nullptr;
    Vector3 velocity_ = {};
    bool onGround_ = true;
    LRDirection lrDirection_ = LRDirection::kRight;
    float turnFirstRotationY_ = 0.0f;
    float turnTimer_ = 0.0f;
    // マップチップによるフィールド
    MapChipField* mapChipField_ = nullptr;   


    static inline const float kAcceleration = 0.1f;
    static inline const float kAttenuation = 0.2f;
    static inline const float kLimitRunSpeed = 5.0f;
    static inline const float kTimeTurn = 0.3f;
  
    static inline const float kGravityAcceleration = 0.98f;
    static inline const float kLimitFallSpeed = 1.0f;
    static inline const float kJumpAcceleration = 20.0f;

    // キャラクターの当たり判定サイズ
    static inline const float kWidth = 0.8f;
    static inline const float kHeight = 0.8f;

    static inline const float kBlank = 0.04f;
    static inline const float kGroundSearchHeight = 0.06f;
    static inline const float kAttenuationWall = 0.2f;
    static inline const float kAttenuationLanding = 0.0f;

    struct CollisionMapInfo
    {
        bool isCelling = false;
        bool isGrounding = false;
        bool isHitWall = false;
        Vector3 move;
    };

    void InputMove();

    void MapCollision(CollisionMapInfo& info);
    void MapCollisionUp(CollisionMapInfo& info);
    void MapCollisionDown(CollisionMapInfo& info);
    void MapCollisionRight(CollisionMapInfo& info);
    void MapCollisionLeft(CollisionMapInfo& info);

    void UpdateOnGround(const CollisionMapInfo& info);
    void AnimateTurn();

    Vector3 CornerPosition(const Vector3& center, Corner corner);
};
