#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponThrowerSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponThrowerSelector, ksys::act::ai::Ai)
public:
    explicit WeaponThrowerSelector(const InitArg& arg);
    ~WeaponThrowerSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
