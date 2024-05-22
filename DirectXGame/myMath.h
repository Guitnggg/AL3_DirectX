#include "GameScene.h"

// ƒAƒtƒBƒ“•ÏŠ·s—ñ
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// X²‰ñ“]s—ñ
Matrix4x4 MakeRotateXMatrix(float radian);

// Y²‰ñ“]s—ñ
Matrix4x4 MakeRotateYMatrix(float radian);

// Z²‰ñ“]s—ñ
Matrix4x4 MakeRotateZMatrix(float radian);

// s—ñ‚ÌŠ|‚¯Z
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);