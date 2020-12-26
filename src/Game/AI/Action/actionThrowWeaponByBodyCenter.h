#pragma once

#include "Game/AI/Action/actionThrowWeapon.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrowWeaponByBodyCenter : public ThrowWeapon {
    SEAD_RTTI_OVERRIDE(ThrowWeaponByBodyCenter, ThrowWeapon)
public:
    explicit ThrowWeaponByBodyCenter(const InitArg& arg);
    ~ThrowWeaponByBodyCenter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
