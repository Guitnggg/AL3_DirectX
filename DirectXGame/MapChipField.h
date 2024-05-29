#include <cstdint>
#include <vector>
#include "Vector3.h"

/// <summary>
/// マップチップフィールド
/// </summary>

enum class MapChipType
{
	kBlank,  // 空白
	kBlock,  // ブロック
};


class MapChipField
{
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string &filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
};


struct MapChipData
{
	std::vector<std::vector<MapChipType>> data;
};
