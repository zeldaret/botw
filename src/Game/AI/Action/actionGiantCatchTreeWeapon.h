#pragma once

#include "Game/AI/Action/actionCatch.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantCatchTreeWeapon : public Catch {
    SEAD_RTTI_OVERRIDE(GiantCatchTreeWeapon, Catch)
public:
    explicit GiantCatchTreeWeapon(const InitArg& arg);
    ~GiantCatchTreeWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    const sead::Vector3f* mCatchPosOffset_s{};
};

}  // namespace uking::action
