#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act::ai {

class ForkAI : public Ai {
    SEAD_RTTI_OVERRIDE(ForkAI, Ai)
public:
    explicit ForkAI(const InitArg& arg);
    ~ForkAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(InlineParamPack* params) override;
    bool reenter(ActionBase* other, const sead::SafeString& context) override;
    void calc() override;
    void leave_() override;
    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override;
    bool handleMessage_(const Message& message) override;
    bool handleAck_(const MessageAck& message) override;
    void getCurrentName(sead::BufferedSafeString* name, ActionBase* last) const override;
    void getNames(sead::BufferedSafeString* out) const override;
};

}  // namespace ksys::act::ai
