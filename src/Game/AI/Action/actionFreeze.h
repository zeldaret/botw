#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Freeze : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(Freeze, ActionWithPosAngReduce)
public:
    explicit Freeze(const InitArg& arg);
    ~Freeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x40
    sead::SafeString mTransBoneKey_s{};
    // static_param at offset 0x50
    const bool* mIsChangeInAir_s{};
    // aitree_variable at offset 0x58
    bool* mIsKeepFreeze_a{};
    // aitree_variable at offset 0x60
    void* mCRBOffsetUnit_a{};
};

}  // namespace uking::action
