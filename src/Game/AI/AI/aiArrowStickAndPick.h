#pragma once

#include "Game/AI/AI/aiCommonPickedItem.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ArrowStickAndPick : public CommonPickedItem {
    SEAD_RTTI_OVERRIDE(ArrowStickAndPick, CommonPickedItem)
public:
    explicit ArrowStickAndPick(const InitArg& arg);
    ~ArrowStickAndPick() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0xe8
    sead::Vector3f* mStickPos_d{};
    // dynamic_param at offset 0xf0
    sead::Vector3f* mStickPosDiv_d{};
    // dynamic_param at offset 0xf8
    ksys::act::BaseProcLink* mStickActor_d{};
    // dynamic_param at offset 0x100
    sead::SafeString* mStickBodyName_d{};
};

}  // namespace uking::ai
