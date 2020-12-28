#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCDyeShopReception : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCDyeShopReception, ksys::act::ai::Action)
public:
    explicit NPCDyeShopReception(const InitArg& arg);
    ~NPCDyeShopReception() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
