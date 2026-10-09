#pragma once

#include "Game/Actor/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshFly : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshFly, NavMeshMoveBase)
public:
    explicit NavMeshFly(const InitArg& arg);
    ~NavMeshFly() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
