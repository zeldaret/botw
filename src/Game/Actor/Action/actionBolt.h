#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Bolt : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Bolt, ksys::act::ai::Action)
public:
    explicit Bolt(const InitArg& arg);
    ~Bolt() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const bool* mIsNoBindAlive_m{};
};

}  // namespace uking::action
