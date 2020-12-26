#pragma once

#include "Game/AI/Action/actionAscendingCurrent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AscendingCurrentFixedSize : public AscendingCurrent {
    SEAD_RTTI_OVERRIDE(AscendingCurrentFixedSize, AscendingCurrent)
public:
    explicit AscendingCurrentFixedSize(const InitArg& arg);
    ~AscendingCurrentFixedSize() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    const bool* mDisableInDemo_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mSize_s{};
};

}  // namespace uking::action
