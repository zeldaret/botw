#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SystemHide : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SystemHide, ksys::act::ai::Action)
public:
    explicit SystemHide(const InitArg& arg);
    ~SystemHide() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsOnAttention_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
