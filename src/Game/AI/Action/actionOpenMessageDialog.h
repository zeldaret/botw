#pragma once

#include "Game/AI/Action/actionOpenMessageDialogBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenMessageDialog : public OpenMessageDialogBase {
    SEAD_RTTI_OVERRIDE(OpenMessageDialog, OpenMessageDialogBase)
public:
    explicit OpenMessageDialog(const InitArg& arg);
    ~OpenMessageDialog() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x78
    sead::SafeString mASName_d{};
};

}  // namespace uking::action
