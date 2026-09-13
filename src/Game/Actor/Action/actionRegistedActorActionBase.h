#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RegistedActorActionBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RegistedActorActionBase, ksys::act::ai::Action)
public:
    explicit RegistedActorActionBase(const InitArg& arg);
    ~RegistedActorActionBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x3e0];
    // static_param at offset 0x400
    const bool* mTeachSelfRegistedActor_s{};
};

}  // namespace uking::action
