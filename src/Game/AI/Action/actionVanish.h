#pragma once

#include "Game/AI/Action/actionTimeredASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Vanish : public TimeredASPlay {
    SEAD_RTTI_OVERRIDE(Vanish, TimeredASPlay)
public:
    explicit Vanish(const InitArg& arg);
    ~Vanish() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const int* mDieType_s{};
    // static_param at offset 0x68
    const bool* mNoDrop_s{};
};

}  // namespace uking::action
