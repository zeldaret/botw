#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetDynamic : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetDynamic, ksys::act::ai::Action)
public:
    explicit EventSetDynamic(const InitArg& arg);
    ~EventSetDynamic() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    bool* mIsChangeToFixedInDemo_a{};
};

}  // namespace uking::action
