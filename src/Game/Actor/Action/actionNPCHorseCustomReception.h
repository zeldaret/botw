#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCHorseCustomReception : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCHorseCustomReception, ksys::act::ai::Action)
public:
    explicit NPCHorseCustomReception(const InitArg& arg);
    ~NPCHorseCustomReception() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mCustomItemType_d{};
};

}  // namespace uking::action
