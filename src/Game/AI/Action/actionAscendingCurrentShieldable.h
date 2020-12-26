#pragma once

#include "Game/AI/Action/actionAscendingCurrent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AscendingCurrentShieldable : public AscendingCurrent {
    SEAD_RTTI_OVERRIDE(AscendingCurrentShieldable, AscendingCurrent)
public:
    explicit AscendingCurrentShieldable(const InitArg& arg);
    ~AscendingCurrentShieldable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
