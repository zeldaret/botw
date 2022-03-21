#pragma once

#include "heap/seadDisposer.h"
#include "random/seadRandom.h"

namespace sead
{
class GlobalRandom : public Random
{
    SEAD_SINGLETON_DISPOSER(GlobalRandom)
    GlobalRandom() = default;
};
}  // namespace sead
