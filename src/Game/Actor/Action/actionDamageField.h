#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DamageField : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DamageField, ksys::act::ai::Action)
public:
    explicit DamageField(const InitArg& arg);
    ~DamageField() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mFieldType_s{};
    // static_param at offset 0x28
    const int* mRigidSetName_s{};
    // static_param at offset 0x30
    const bool* mIsChangeRigidWorldMode_s{};
    // static_param at offset 0x38
    const bool* mIsUseCollisionInfo_s{};
    // static_param at offset 0x40
    sead::SafeString mRigidBodyName_s{};
    // static_param at offset 0x50
    sead::SafeString mCollisionInfoName_s{};
};

}  // namespace uking::action
