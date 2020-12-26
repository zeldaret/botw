#pragma once

#include "Game/AI/Action/actionOctarockReloadWigBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OctarockReloadWig : public OctarockReloadWigBase {
    SEAD_RTTI_OVERRIDE(OctarockReloadWig, OctarockReloadWigBase)
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
