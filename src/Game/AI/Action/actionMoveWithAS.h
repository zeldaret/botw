#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveWithAS : public MoveBase {
    SEAD_RTTI_OVERRIDE(MoveWithAS, MoveBase)
public:
    explicit MoveWithAS(const InitArg& arg);
    ~MoveWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
