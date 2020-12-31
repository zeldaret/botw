#pragma once

#include "Game/AI/AI/aiAddCarriedBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddNodeNodeCarried : public AddCarriedBase {
    SEAD_RTTI_OVERRIDE(AddNodeNodeCarried, AddCarriedBase)
public:
    explicit AddNodeNodeCarried(const InitArg& arg);
    ~AddNodeNodeCarried() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x138
    sead::SafeString mMyNode_s{};
    // static_param at offset 0x148
    const sead::Vector3f* mNodeRotOffset_s{};
};

}  // namespace uking::ai
