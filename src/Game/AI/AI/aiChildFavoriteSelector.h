#pragma once

#include "Game/AI/AI/aiChildFavoriteSelectorBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChildFavoriteSelector : public ChildFavoriteSelectorBase {
    SEAD_RTTI_OVERRIDE(ChildFavoriteSelector, ChildFavoriteSelectorBase)
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
