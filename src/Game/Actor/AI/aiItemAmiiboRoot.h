#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ItemAmiiboRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ItemAmiiboRoot, ksys::act::ai::Ai)
public:
    explicit ItemAmiiboRoot(const InitArg& arg);
    ~ItemAmiiboRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mAmiiboCharacterId_m{};
    // map_unit_param at offset 0x40
    const int* mAmiiboNumberingId_m{};
};

}  // namespace uking::ai
