#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenPouchAddStockNum : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OpenPouchAddStockNum, ksys::act::ai::Action)
public:
    explicit OpenPouchAddStockNum(const InitArg& arg);
    ~OpenPouchAddStockNum() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mType_d{};
};

}  // namespace uking::action
