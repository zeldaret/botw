#pragma once

#include "Game/AI/Action/actionSimpleGrabWithASBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SimpleGrabWithAS : public SimpleGrabWithASBase {
    SEAD_RTTI_OVERRIDE(SimpleGrabWithAS, SimpleGrabWithASBase)
public:
    explicit SimpleGrabWithAS(const InitArg& arg);
    ~SimpleGrabWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
