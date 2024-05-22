#include "GameScene.h"

// �A�t�B���ϊ��s��
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// X����]�s��
Matrix4x4 MakeRotateXMatrix(float radian);

// Y����]�s��
Matrix4x4 MakeRotateYMatrix(float radian);

// Z����]�s��
Matrix4x4 MakeRotateZMatrix(float radian);

// �s��̊|���Z
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);