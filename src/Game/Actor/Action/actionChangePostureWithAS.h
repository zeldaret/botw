#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChangePostureWithAS : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChangePostureWithAS, ksys::act::ai::Action)
public:
    explicit ChangePostureWithAS(const InitArg& arg);
    ~ChangePostureWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mPosture_d{};
};

}  // namespace uking::action
