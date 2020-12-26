#pragma once

#include "Game/AI/Action/actionExplode.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OctarockBulletLExplode : public Explode {
    SEAD_RTTI_OVERRIDE(OctarockBulletLExplode, Explode)
public:
    explicit OctarockBulletLExplode(const InitArg& arg);
    ~OctarockBulletLExplode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
