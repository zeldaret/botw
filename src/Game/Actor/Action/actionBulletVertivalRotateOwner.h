#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BulletVertivalRotateOwner : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BulletVertivalRotateOwner, ksys::act::ai::Action)
public:
    explicit BulletVertivalRotateOwner(const InitArg& arg);
    ~BulletVertivalRotateOwner() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpdAccRatio_s{};
    // static_param at offset 0x30
    const float* mOffsetY_s{};
};

}  // namespace uking::action
