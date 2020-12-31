#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossLswordTornadoRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossLswordTornadoRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossLswordTornadoRoot(const InitArg& arg);
    ~SiteBossLswordTornadoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mDestPos_d{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
