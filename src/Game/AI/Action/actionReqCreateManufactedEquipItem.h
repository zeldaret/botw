#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ReqCreateManufactedEquipItem : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ReqCreateManufactedEquipItem, ksys::act::ai::Action)
public:
    explicit ReqCreateManufactedEquipItem(const InitArg& arg);
    ~ReqCreateManufactedEquipItem() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
