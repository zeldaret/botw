#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceOffMagneGrabbed : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForceOffMagneGrabbed, ksys::act::ai::Action)
public:
    explicit ForceOffMagneGrabbed(const InitArg& arg);
    ~ForceOffMagneGrabbed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
