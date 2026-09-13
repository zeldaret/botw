#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetUpBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GetUpBase, ksys::act::ai::Action)
public:
    explicit GetUpBase(const InitArg& arg);
    ~GetUpBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x8];
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
    // static_param at offset 0x38
    const sead::Vector3f* mRootOffset_s{};
    // aitree_variable at offset 0x140
    void* mCRBOffsetUnit_a{};
};

}  // namespace uking::action
