#pragma once

#include "Game/AI/AI/aiPreyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SunazarashiNormal : public PreyNormal {
    SEAD_RTTI_OVERRIDE(SunazarashiNormal, PreyNormal)
public:
    explicit SunazarashiNormal(const InitArg& arg);
    ~SunazarashiNormal() override;

protected:
};

}  // namespace uking::ai
