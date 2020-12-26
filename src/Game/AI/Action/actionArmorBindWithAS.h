#pragma once

#include "Game/AI/Action/actionArmorBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArmorBindWithAS : public ArmorBindAction {
    SEAD_RTTI_OVERRIDE(ArmorBindWithAS, ArmorBindAction)
public:
    explicit ArmorBindWithAS(const InitArg& arg);
    ~ArmorBindWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x30
    sead::SafeString* mASName_d{};
};

}  // namespace uking::action
