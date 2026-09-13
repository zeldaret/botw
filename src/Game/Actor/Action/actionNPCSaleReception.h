#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCSaleReception : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCSaleReception, ksys::act::ai::Action)
public:
    explicit NPCSaleReception(const InitArg& arg);
    ~NPCSaleReception() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mTableName_d{};
};

}  // namespace uking::action
