#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventOpenGetDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventOpenGetDemo, ksys::act::ai::Action)
public:
    explicit EventOpenGetDemo(const InitArg& arg);
    ~EventOpenGetDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsInvalidOpenPouch_d{};
    bool _28{};
    bool _29{};
};

}  // namespace uking::action
