#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSwapPartsItemFromDropTable : public Fork {
    SEAD_RTTI_OVERRIDE(ForkSwapPartsItemFromDropTable, Fork)
public:
    explicit ForkSwapPartsItemFromDropTable(const InitArg& arg);
    ~ForkSwapPartsItemFromDropTable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    sead::SafeString mPartsKey0_s{};
    // static_param at offset 0x40
    sead::SafeString mPartsKey1_s{};
    // static_param at offset 0x50
    sead::SafeString mPartsKey2_s{};
    // static_param at offset 0x60
    sead::SafeString mPartsKey3_s{};
    // static_param at offset 0x70
    sead::SafeString mPartsKey4_s{};
};

}  // namespace uking::action
