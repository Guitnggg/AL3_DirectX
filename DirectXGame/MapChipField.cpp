#include "MapChipField.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>

namespace {
    std::map<std::string, MapChipType> mapChipTable =
    {
        {"0", MapChipType::kBlank},
        {"1", MapChipType::kBlock},
    };
}

uint32_t MapChipField::GetNumBlockVirtical() const
{
    return kNumBlockVirtical;
}

uint32_t MapChipField::GetNumBlockHorizontal() const
{
    return kNumBlockHorizontal;
}

void MapChipField::ResetMapChipData()
{
    // マップチップデータをリセット
    mapChipData_.data.clear();

    mapChipData_.data.resize(kNumBlockVirtical);

    for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data)
    {
        mapChipDataLine.resize(kNumBlockHorizontal);
    }
}

void MapChipField::LoadMapChipCsv(const std::string& filePath)
{
    // マップチップデータをリセット
    ResetMapChipData();

    // ファイルを開く
    std::ifstream file;
    file.open(filePath);

    assert(file.is_open());

    // マップチップCSV
    std::stringstream mapChipCsv;
    // ファイルの内容を文字列ストリームにコピー
    mapChipCsv << file.rdbuf();
    // ファイルを閉じる
    file.close();

    // CSVからマップチップデータを読み込む
    for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
    {
        std::string line;
        getline(mapChipCsv, line);
        // 1行分の文字列をストリームに変換して解析しやすくする
        std::istringstream line_stream(line);

        for (uint32_t j = 0; j < kNumBlockHorizontal; ++j)
        {
            std::string word;
            getline(line_stream, word, ',');

            if (mapChipTable.contains(word))
            {
                mapChipData_.data[i][j] = mapChipTable[word];
            }
        }
    }
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) const
{
    if (xIndex >= kNumBlockHorizontal || yIndex >= kNumBlockVirtical)
    {
        return MapChipType::kBlank;
    }

    return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) const
{
    return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVirtical - 1 - yIndex), 0);
}

MapChipField::IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& position)
{
    IndexSet indexSet = {};
    /*indexSet.xIndex=static_cast<uint32_t>(計算）*/
    /*indexSet.yIndex=kNumBlockVirtical-1-static_cast<uint32_t>(計算）*/
    return IndexSet();
}

MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex)
{
    Rect rect;
   /* rect.left = center.x - kBlockWidth / 2.0f;
    rect.right = center.x + kBlockWidth / 2.0f;
    rect.bottom = center.y - kBlockHeight / 2.0f;
    rect.top = center.y + kBlockHeight / 2.0f;*/
    return Rect();
}
