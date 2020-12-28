#pragma once

#include "Game/AI/Action/actionSimpleGrabWithASBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SimpleGrabWithAS : public SimpleGrabWithASBase {
    SEAD_RTTI_OVERRIDE(SimpleGrabWithAS, SimpleGrabWithASBase)
public:
    explicit SimpleGrabWithAS(const InitArg& arg);
    ~SimpleGrabWithAS() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
