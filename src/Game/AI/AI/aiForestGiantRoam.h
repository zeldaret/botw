#pragma once

#include "Game/AI/AI/aiBokoblinRoam.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantRoam : public BokoblinRoam {
    SEAD_RTTI_OVERRIDE(ForestGiantRoam, BokoblinRoam)
public:
    explicit ForestGiantRoam(const InitArg& arg);
    ~ForestGiantRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const float* mReturnHomeDist_s{};
};

}  // namespace uking::ai
