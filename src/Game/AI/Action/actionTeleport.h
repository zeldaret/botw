#pragma once

#include "Game/AI/Action/actionTeleportBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Teleport : public TeleportBase {
    SEAD_RTTI_OVERRIDE(Teleport, TeleportBase)
public:
    explicit Teleport(const InitArg& arg);
    ~Teleport() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const float* mDistXZ_s{};
    // static_param at offset 0x80
    const float* mDistY_s{};
};

}  // namespace uking::action
