#pragma once

#include <basis/seadTypes.h>
#include <string_view>
#include "KingSystem/Utils/HashUtil.h"

namespace ksys::act {

/// Actor tag.
class Tag {
public:
    Tag() = default;
    constexpr Tag(u32 hash) : mHash(hash) {}
    constexpr Tag(std::string_view name) : mHash(util::calcCrc32(name)) {}

    constexpr bool operator==(Tag other) const { return mHash == other.mHash; }
    constexpr bool operator!=(Tag other) const { return mHash != other.mHash; }
    constexpr bool operator<(Tag other) const { return mHash < other.mHash; }
    constexpr bool operator>(Tag other) const { return mHash > other.mHash; }
    constexpr bool operator<=(Tag other) const { return mHash <= other.mHash; }
    constexpr bool operator>=(Tag other) const { return mHash >= other.mHash; }

    constexpr operator u32() const { return mHash; }
    constexpr u32 getHash() const { return mHash; }

private:
    u32 mHash;
};

}  // namespace ksys::act
