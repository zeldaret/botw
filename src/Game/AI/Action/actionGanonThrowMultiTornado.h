#pragma once

#include "Game/AI/Action/actionGanonThrowTornado.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonThrowMultiTornado : public GanonThrowTornado {
    SEAD_RTTI_OVERRIDE(GanonThrowMultiTornado, GanonThrowTornado)
public:
    explicit GanonThrowMultiTornado(const InitArg& arg);
    ~GanonThrowMultiTornado() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const sead::Vector3f* mAppearOffset1_s{};
    // dynamic_param at offset 0x98
    sead::SafeString mThrowPartsName1_d{};
};

}  // namespace uking::action
