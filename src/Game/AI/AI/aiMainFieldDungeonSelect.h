#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MainFieldDungeonSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MainFieldDungeonSelect, ksys::act::ai::Ai)
public:
    explicit MainFieldDungeonSelect(const InitArg& arg);
    ~MainFieldDungeonSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
