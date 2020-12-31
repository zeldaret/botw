#include "Game/AI/AI/aiAssassinCallSelect.h"

namespace uking::ai {

AssassinCallSelect::AssassinCallSelect(const InitArg& arg) : EnemyCalledAppear(arg) {}

AssassinCallSelect::~AssassinCallSelect() = default;

bool AssassinCallSelect::init_(sead::Heap* heap) {
    return EnemyCalledAppear::init_(heap);
}

void AssassinCallSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyCalledAppear::enter_(params);
}

void AssassinCallSelect::leave_() {
    EnemyCalledAppear::leave_();
}

void AssassinCallSelect::loadParams_() {
    EnemyCalledAppear::loadParams_();
    getStaticParam(&mChangeDemoName_s, "ChangeDemoName");
    getStaticParam(&mChangeDemoEPName_s, "ChangeDemoEPName");
}

}  // namespace uking::ai
