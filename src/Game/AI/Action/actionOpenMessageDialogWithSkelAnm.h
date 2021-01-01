#pragma once

#include "Game/AI/Action/actionOpenMessageDialogBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenMessageDialogWithSkelAnm : public OpenMessageDialogBase {
    SEAD_RTTI_OVERRIDE(OpenMessageDialogWithSkelAnm, OpenMessageDialogBase)
public:
    explicit OpenMessageDialogWithSkelAnm(const InitArg& arg);
    ~OpenMessageDialogWithSkelAnm() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x78
    sead::SafeString mAnimName_d{};
};

}  // namespace uking::action
