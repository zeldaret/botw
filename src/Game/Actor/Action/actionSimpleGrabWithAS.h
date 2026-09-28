#pragma once

#include "Game/Actor/Action/actionSimpleGrabBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SimpleGrabWithAS : public SimpleGrabBase {
    SEAD_RTTI_OVERRIDE(SimpleGrabWithAS, SimpleGrabBase)
public:
    explicit SimpleGrabWithAS(const InitArg& arg);
    ~SimpleGrabWithAS() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
