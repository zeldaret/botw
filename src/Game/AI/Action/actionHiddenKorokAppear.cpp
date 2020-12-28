#include "Game/AI/Action/actionHiddenKorokAppear.h"

namespace uking::action {

HiddenKorokAppear::HiddenKorokAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HiddenKorokAppear::~HiddenKorokAppear() = default;

bool HiddenKorokAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HiddenKorokAppear::loadParams_() {}

}  // namespace uking::action
