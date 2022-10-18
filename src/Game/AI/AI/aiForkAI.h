#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForkAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ForkAI, ksys::act::ai::Ai)
public:
    explicit ForkAI(const InitArg& arg);
    ~ForkAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool reenter(ActionBase* other, const sead::SafeString& context) override;
    void calc() override;
    void leave_() override;
    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override;
    bool handleMessage_(const ksys::Message& message) override;
    bool handleAck_(const ksys::MessageAck& message) override;
    void getCurrentName(sead::BufferedSafeString* name, ActionBase* last) const override;
    void getNames(sead::BufferedSafeString* out) const override;
};

}  // namespace uking::ai
