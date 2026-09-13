#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArmorBindNodeAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ArmorBindNodeAction, ksys::act::ai::Action)
public:
    explicit ArmorBindNodeAction(const InitArg& arg);
    ~ArmorBindNodeAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mBoneName_d{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mPosOffset_d{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mRotOffsetXyz_d{};
};

}  // namespace uking::action
