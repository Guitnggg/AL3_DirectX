#include <cstdint>
#include <vector>
#include <string>
#include "Vector3.h"

/// <summary>
/// マップチップフィールド
/// </summary>

enum class MapChipType
{
    kBlank,  // 空白
    kBlock,  // ブロック
};

struct MapChipData
{
    std::vector<std::vector<MapChipType>> data;
};

class MapChipField
{
public:
    // マップチップデータの読み込み
    void LoadMapChipCsv(const std::string& filePath);

    // ブロックの個数を取得
    uint32_t GetNumBlockVirtical() const;
    uint32_t GetNumBlockHorizontal() const;

    // 指定したインデックスのマップチップタイプを取得
    MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) const;

    // 指定したインデックスのマップチップの位置を取得
    Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) const;

private:
    // 1ブロックのサイズ
    static inline const float kBlockWidth = 1.0f;
    static inline const float kBlockHeight = 1.0f;

    // ブロックの個数
    static inline const uint32_t kNumBlockVirtical = 20;
    static inline const uint32_t kNumBlockHorizontal = 100;

    MapChipData mapChipData_;

    // マップチップデータをリセット
    void ResetMapChipData();
};