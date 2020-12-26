#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IceBroken : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IceBroken, ksys::act::ai::Action)
public:
    explicit IceBroken(const InitArg& arg);
    ~IceBroken() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
