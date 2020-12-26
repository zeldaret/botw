#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCManufactItem : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCManufactItem, ksys::act::ai::Action)
public:
    explicit NPCManufactItem(const InitArg& arg);
    ~NPCManufactItem() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
