#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCPurchaseMaterial : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCPurchaseMaterial, ksys::act::ai::Action)
public:
    explicit NPCPurchaseMaterial(const InitArg& arg);
    ~NPCPurchaseMaterial() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
