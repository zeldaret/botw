#pragma once

#include "Game/AI/Action/actionFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceGetUpFreeze : public Freeze {
    SEAD_RTTI_OVERRIDE(ForceGetUpFreeze, Freeze)
public:
    explicit ForceGetUpFreeze(const InitArg& arg);
    ~ForceGetUpFreeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
