#include "GameScene.h"
#include "Matrix4x4.h"
#include "Vector3.h"

// アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

// 行列の掛け算
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);