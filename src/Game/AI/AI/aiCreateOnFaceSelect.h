#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CreateOnFaceSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CreateOnFaceSelect, ksys::act::ai::Ai)
public:
    explicit CreateOnFaceSelect(const InitArg& arg);
    ~CreateOnFaceSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsCreateOnFace_m{};
};

}  // namespace uking::ai
