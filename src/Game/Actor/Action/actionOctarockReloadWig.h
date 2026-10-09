#pragma once

#include "Game/Actor/Action/actionIgniteActorReloadBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OctarockReloadWig : public IgniteActorReloadBase {
    SEAD_RTTI_OVERRIDE(OctarockReloadWig, IgniteActorReloadBase)
public:
    explicit OctarockReloadWig(const InitArg& arg);
    ~OctarockReloadWig() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x88
    void* mOctarockFormChangeUnit_a{};
};

}  // namespace uking::action
