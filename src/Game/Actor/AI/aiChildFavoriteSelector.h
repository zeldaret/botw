#pragma once

#include "Game/Actor/AI/aiChildSelector.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChildFavoriteSelector : public ChildSelector {
    SEAD_RTTI_OVERRIDE(ChildFavoriteSelector, ChildSelector)
public:
    explicit ChildFavoriteSelector(const InitArg& arg);
    ~ChildFavoriteSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
