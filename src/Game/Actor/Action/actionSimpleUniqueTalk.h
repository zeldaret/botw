#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SimpleUniqueTalk : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SimpleUniqueTalk, ksys::act::ai::Action)
public:
    explicit SimpleUniqueTalk(const InitArg& arg);
    ~SimpleUniqueTalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mMstxtName_d{};
};

}  // namespace uking::action
