#pragma once

#include "Game/AI/Action/actionGetItem.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetItemIntoBag : public GetItem {
    SEAD_RTTI_OVERRIDE(GetItemIntoBag, GetItem)
public:
    explicit GetItemIntoBag(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
