#pragma once

#include "Game/AI/Action/actionMoveByAnimeDriven.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveByAnimeDrivenDynAS : public MoveByAnimeDriven {
    SEAD_RTTI_OVERRIDE(MoveByAnimeDrivenDynAS, MoveByAnimeDriven)
public:
    explicit MoveByAnimeDrivenDynAS(const InitArg& arg);
    ~MoveByAnimeDrivenDynAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x58
    sead::SafeString mDynASKeyName_d{};
};

}  // namespace uking::action
