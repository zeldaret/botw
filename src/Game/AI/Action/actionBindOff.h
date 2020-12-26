#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BindOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BindOff, ksys::act::ai::Action)
public:
    explicit BindOff(const InitArg& arg);
    ~BindOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    void* mEventBindUnit_a{};
};

}  // namespace uking::action
