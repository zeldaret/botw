#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetAttackAttitudeTgt : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetAttackAttitudeTgt, ksys::act::ai::Ai)
public:
    explicit TargetAttackAttitudeTgt(const InitArg& arg);
    ~TargetAttackAttitudeTgt() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
