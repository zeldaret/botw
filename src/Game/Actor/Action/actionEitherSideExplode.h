#pragma once

#include "Game/Actor/Action/actionExplode.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EitherSideExplode : public Explode {
    SEAD_RTTI_OVERRIDE(EitherSideExplode, Explode)
public:
    explicit EitherSideExplode(const InitArg& arg);
    ~EitherSideExplode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x80
    bool* mIsPlayerAttack_d{};
};

}  // namespace uking::action
