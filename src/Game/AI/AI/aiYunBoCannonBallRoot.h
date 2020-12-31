#pragma once

#include "Game/AI/AI/aiCannonBallRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class YunBoCannonBallRoot : public CannonBallRoot {
    SEAD_RTTI_OVERRIDE(YunBoCannonBallRoot, CannonBallRoot)
public:
    explicit YunBoCannonBallRoot(const InitArg& arg);
    ~YunBoCannonBallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mCannonSpot_m{};
};

}  // namespace uking::ai
