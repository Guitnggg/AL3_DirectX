#pragma once

#include "Model.h"
#include "WorldTransform.h"

class Player {
public:
    void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

    void Update();
    
    void Draw();

    const WorldTransform& GetWorldTransform() const { return worldTransform_; }
    const Vector3& GetVelocity() const { return velocity_; }

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
};
