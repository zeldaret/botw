#pragma once

#include "Game/AI/AI/aiDungeonRotateTagInOrder.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTagCont : public DungeonRotateTagInOrder {
    SEAD_RTTI_OVERRIDE(DungeonRotateTagCont, DungeonRotateTagInOrder)
public:
    explicit DungeonRotateTagCont(const InitArg& arg);
    ~DungeonRotateTagCont() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x48
    bool* mIsContinueRotateOrMove_a{};
};

}  // namespace uking::ai
