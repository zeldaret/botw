#pragma once

#include "Game/AI/Action/actionSleep.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantSleep : public Sleep {
    SEAD_RTTI_OVERRIDE(GiantSleep, Sleep)
public:
    explicit GiantSleep(const InitArg& arg);
    ~GiantSleep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    sead::SafeString mRidableRigidBodyName_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
