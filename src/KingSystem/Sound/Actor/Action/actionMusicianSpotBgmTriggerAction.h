#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Sound/Actor/Action/actionSpotBgmTriggerAction.h"

namespace ksys::snd {

class MusicianSpotBgmTriggerAction : public SpotBgmTriggerAction {
    SEAD_RTTI_OVERRIDE(MusicianSpotBgmTriggerAction, SpotBgmTriggerAction)
public:
    explicit MusicianSpotBgmTriggerAction(const InitArg& arg);
    ~MusicianSpotBgmTriggerAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace ksys::snd
