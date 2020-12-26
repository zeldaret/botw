#pragma once

#include "Game/AI/Action/actionFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceRagdollOffFreeze : public Freeze {
    SEAD_RTTI_OVERRIDE(ForceRagdollOffFreeze, Freeze)
public:
    explicit ForceRagdollOffFreeze(const InitArg& arg);
    ~ForceRagdollOffFreeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x78
    void* mCRBOffsetUnit_a{};
};

}  // namespace uking::action
