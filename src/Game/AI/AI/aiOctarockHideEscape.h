#pragma once

#include "Game/AI/AI/aiOctarockEscape.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockHideEscape : public OctarockEscape {
    SEAD_RTTI_OVERRIDE(OctarockHideEscape, OctarockEscape)
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
