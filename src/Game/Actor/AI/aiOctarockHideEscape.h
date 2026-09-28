#pragma once

#include "Game/Actor/AI/aiOctarockHideEscapeBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockHideEscape : public OctarockHideEscapeBase {
    SEAD_RTTI_OVERRIDE(OctarockHideEscape, OctarockHideEscapeBase)
public:
    explicit OctarockHideEscape(const InitArg& arg);
    ~OctarockHideEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const float* mEscapeDist_s{};
};

}  // namespace uking::ai
