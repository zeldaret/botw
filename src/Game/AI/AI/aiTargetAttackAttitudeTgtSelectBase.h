#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetAttackAttitudeTgtSelectBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetAttackAttitudeTgtSelectBase, ksys::act::ai::Ai)
public:
    explicit TargetAttackAttitudeTgtSelectBase(const InitArg& arg);
    ~TargetAttackAttitudeTgtSelectBase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
