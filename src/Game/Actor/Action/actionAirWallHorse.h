#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirWallHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirWallHorse, ksys::act::ai::Action)
public:
    explicit AirWallHorse(const InitArg& arg);
    ~AirWallHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
