#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCBuyHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCBuyHorse, ksys::act::ai::Action)
public:
    explicit NPCBuyHorse(const InitArg& arg);
    ~NPCBuyHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x30];
    // aitree_variable at offset 0x50
    void* mEventBindUnit_a{};
};

}  // namespace uking::action
