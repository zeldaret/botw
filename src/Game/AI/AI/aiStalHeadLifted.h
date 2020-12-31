#pragma once

#include "Game/AI/AI/aiLifted.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalHeadLifted : public Lifted {
    SEAD_RTTI_OVERRIDE(StalHeadLifted, Lifted)
public:
    explicit StalHeadLifted(const InitArg& arg);
    ~StalHeadLifted() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x98
    const float* mEscapeSpeed_s{};
    // static_param at offset 0xa0
    const sead::Vector3f* mEscapeDir_s{};
};

}  // namespace uking::ai
