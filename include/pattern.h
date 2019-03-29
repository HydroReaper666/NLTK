#pragma once

#ifndef PATTERN_H
#define PATTERN_H

#include <3ds.h>
#include <string>
#include <array>
#include <vector>
#include "save.h"

class Player;

// TODO: Research the 1-7 design types
enum class DesignType : u8 {
    DressLongSleeve = 0,
    DressShortSleeve = 1,
    DressSleeveless = 2,
    ShirtLongSleeve = 3,
    ShirtShortSleeve = 4,
    ShirtSleeveless = 5,
    HornedHat = 6,
    KnitHat = 7,
    PhotoBoard = 8,
    Pattern = 9
};

class Pattern {
public:
    Pattern(Player *player, u32 id);
    ~Pattern();

    void TakeOwnership(Player *player);
    void Write();
    
    std::u16string              Name;
    u16							CreatorId;
    std::u16string              CreatorName;
    u16                         CreatorGender; // technically only a u8, but this allows us to ensure the following byte is always 0
    u16                         OriginatingTownId;
    std::u16string              OriginatingTownName;
    std::array<u8, 16>          Palette; // only the first 15 colors are valid
    DesignType                  Type;
    std::array<u8, 0x800>       PatternData;

    const u32                   Index;
    std::vector<u32 *>          ImageData;
    C2D_Image                   Images[4];

    const u32                   Offset;

private:
    void Decompress(void);
    void Compress(void);
};

#endif