#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetLinkTagBasic : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetLinkTagBasic, ksys::act::ai::Action)
public:
    explicit SetLinkTagBasic(const InitArg& arg);
    ~SetLinkTagBasic() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsOn_s{};
};

}  // namespace uking::action
