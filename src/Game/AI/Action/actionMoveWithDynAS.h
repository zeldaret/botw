#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveWithDynAS : public MoveBase {
    SEAD_RTTI_OVERRIDE(MoveWithDynAS, MoveBase)
public:
    explicit MoveWithDynAS(const InitArg& arg);
    ~MoveWithDynAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xe0
    sead::SafeString mASName_d{};
};

}  // namespace uking::action
