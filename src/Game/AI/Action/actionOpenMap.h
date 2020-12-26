#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenMap : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OpenMap, ksys::act::ai::Action)
public:
    explicit OpenMap(const InitArg& arg);
    ~OpenMap() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mScaleLevel_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mWorldPos_d{};
};

}  // namespace uking::action
