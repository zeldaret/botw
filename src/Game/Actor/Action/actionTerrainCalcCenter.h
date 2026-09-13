#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TerrainCalcCenter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TerrainCalcCenter, ksys::act::ai::Action)
public:
    explicit TerrainCalcCenter(const InitArg& arg);
    ~TerrainCalcCenter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mlevel_d{};
    // dynamic_param at offset 0x28
    int* mtype_d{};
    // dynamic_param at offset 0x30
    int* mmeshReso_d{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mpos_d{};
};

}  // namespace uking::action
