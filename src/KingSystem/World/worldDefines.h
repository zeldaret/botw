#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>

namespace ksys::world {

SEAD_ENUM(DungeonSize, S,M,L,XL)
SEAD_ENUM(DungeonType, Gimmick,Enemy,Treasure)

enum class CalcType {
    _0 = 0,
    _1 = 1,
    _2 = 2,
    Invalid = 3,
};

enum class RemainsType {
    Wind,
    Electric,
    Fire,
    Water,
    FinalTrial,
};

enum class FieldType {
    MainField = 0,
    AocField = 1,
};

enum class ScalingMode {
    Enabled = 0,
    Disabled = 1,
};

enum class WeatherType {
    Bluesky,
    Cloudy,
    Rain,
    HeavyRain,
    Snow,
    HeavySnow,
    ThunderStorm,
    ThunderRain,
    BlueskyRain,
    Invalid = 0xff,
};
constexpr u32 NumWeatherTypes = 9;

enum class Climate {
    HyrulePlainClimate,
    NorthHyrulePlainClimate,
    HebraFrostClimate,
    TabantaAridClimate,
    FrostClimate,
    GerudoDesertClimate,
    GerudoPlateauClimate,
    EldinClimateLv0,
    TamourPlainClimate,
    ZoraTemperateClimate,
    HateruPlainClimate,
    FiloneSubtropicalClimate,
    SouthHateruHumidTemperateClimate,
    EldinClimateLv1,
    EldinClimateLv2,
    // sic
    DarkWoodsClimat,
    LostWoodClimate,
    GerudoFrostClimate,
    KorogForest,
    GerudoDesertClimateLv2,
};
constexpr u32 NumClimates = 20;

}  // namespace ksys::world
