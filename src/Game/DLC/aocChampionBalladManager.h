#pragma once

#include <array>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>

namespace uking {

enum class BlightType : u32 { Wind, Electric, Fire, Water };

class ChampionBalladManager {
    SEAD_SINGLETON_DISPOSER(ChampionBalladManager)
    ChampionBalladManager() = default;
    virtual ~ChampionBalladManager() = default;

public:
    void init();
    void setBlightRematchCount(s8 count, BlightType blight_type);
    void incrementBlightRematchCount(BlightType blight_type);
    s8 getBlightRematchCount(BlightType blight_type) const;

private:
    sead::SafeArray<u8, 4> mBlightCounts;
};

}  // namespace uking
