#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SimpleMessageDialogCtrl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SimpleMessageDialogCtrl, ksys::act::ai::Action)
public:
    explicit SimpleMessageDialogCtrl(const InitArg& arg);
    ~SimpleMessageDialogCtrl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    void* mSimpleDialogUnit_a{};
};

}  // namespace uking::action
