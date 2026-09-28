#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/aiFork2AI.h"

namespace uking::ai {

class AirOctaRoot : public ksys::act::ai::Fork2AI {
    SEAD_RTTI_OVERRIDE(AirOctaRoot, ksys::act::ai::Fork2AI)
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
