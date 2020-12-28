#pragma once

#include "Game/AI/Action/actionGetItem.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetRupee : public GetItem {
    SEAD_RTTI_OVERRIDE(GetRupee, GetItem)
public:
    explicit GetRupee(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
