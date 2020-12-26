#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCDyeGoods : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCDyeGoods, ksys::act::ai::Action)
public:
    explicit NPCDyeGoods(const InitArg& arg);
    ~NPCDyeGoods() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
