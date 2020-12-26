#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCArmorProcessing : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCArmorProcessing, ksys::act::ai::Action)
public:
    explicit NPCArmorProcessing(const InitArg& arg);
    ~NPCArmorProcessing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mArmorProcessingRank_d{};
};

}  // namespace uking::action
