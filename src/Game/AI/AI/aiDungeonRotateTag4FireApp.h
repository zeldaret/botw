#pragma once

#include "Game/AI/AI/aiWholeDungeonRotateTag.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTag4FireApp : public WholeDungeonRotateTag {
    SEAD_RTTI_OVERRIDE(DungeonRotateTag4FireApp, WholeDungeonRotateTag)
public:
    explicit DungeonRotateTag4FireApp(const InitArg& arg);
    ~DungeonRotateTag4FireApp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
