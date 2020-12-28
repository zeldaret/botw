#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventEquipLastSetItem : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventEquipLastSetItem, ksys::act::ai::Action)
public:
    explicit EventEquipLastSetItem(const InitArg& arg);
    ~EventEquipLastSetItem() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
