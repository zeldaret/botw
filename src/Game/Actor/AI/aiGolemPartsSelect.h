#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemPartsSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolemPartsSelect, ksys::act::ai::Ai)
public:
    explicit GolemPartsSelect(const InitArg& arg);
    ~GolemPartsSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mArmRModelMatrialName_s{};
    // static_param at offset 0x48
    sead::SafeString mArmLModelMatrialName_s{};
};

}  // namespace uking::ai
