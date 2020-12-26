#pragma once

#include "Game/AI/Action/actionKnockBackShock.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmKnockBackShock : public KnockBackShock {
    SEAD_RTTI_OVERRIDE(AnmKnockBackShock, KnockBackShock)
public:
    explicit AnmKnockBackShock(const InitArg& arg);
    ~AnmKnockBackShock() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
