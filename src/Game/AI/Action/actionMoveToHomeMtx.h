#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveToHomeMtx : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MoveToHomeMtx, ksys::act::ai::Action)
public:
    explicit MoveToHomeMtx(const InitArg& arg);
    ~MoveToHomeMtx() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mToHomeMtxLocal_s{};
    // static_param at offset 0x28
    const bool* mSetEnd_s{};
    // static_param at offset 0x30
    const bool* mDisableModelDraw_s{};
};

}  // namespace uking::action
