#pragma once

#include "Game/AI/Action/actionForkASTrgDelete.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgDeleteChild : public ForkASTrgDelete {
    SEAD_RTTI_OVERRIDE(ForkASTrgDeleteChild, ForkASTrgDelete)
public:
    explicit ForkASTrgDeleteChild(const InitArg& arg);
    ~ForkASTrgDeleteChild() override;

protected:
};

}  // namespace uking::action
