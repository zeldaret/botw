#pragma once

#include "Game/AI/AI/aiCommonPickedItem.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPickedItem : public CommonPickedItem {
    SEAD_RTTI_OVERRIDE(TargetPickedItem, CommonPickedItem)
public:
    explicit TargetPickedItem(const InitArg& arg);
    ~TargetPickedItem() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0xe8
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
