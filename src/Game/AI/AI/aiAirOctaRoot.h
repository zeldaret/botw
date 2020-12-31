#pragma once

#include "Game/AI/AI/aiFork2AI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AirOctaRoot : public Fork2AI {
    SEAD_RTTI_OVERRIDE(AirOctaRoot, Fork2AI)
public:
    explicit AirOctaRoot(const InitArg& arg);
    ~AirOctaRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mAirOctaDataMgr_a{};
};

}  // namespace uking::ai
