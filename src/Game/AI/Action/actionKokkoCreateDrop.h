#pragma once

#include "Game/AI/Action/actionKokkoCreateDropBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KokkoCreateDrop : public KokkoCreateDropBase {
    SEAD_RTTI_OVERRIDE(KokkoCreateDrop, KokkoCreateDropBase)
public:
    explicit KokkoCreateDrop(const InitArg& arg);
    ~KokkoCreateDrop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
