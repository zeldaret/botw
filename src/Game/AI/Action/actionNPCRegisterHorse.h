#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCRegisterHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCRegisterHorse, ksys::act::ai::Action)
public:
    explicit NPCRegisterHorse(const InitArg& arg);
    ~NPCRegisterHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
