#include "Game/AI/Action/actionReserveParashawlStart.h"

namespace uking::action {

ReserveParashawlStart::ReserveParashawlStart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReserveParashawlStart::~ReserveParashawlStart() = default;

bool ReserveParashawlStart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReserveParashawlStart::loadParams_() {}

}  // namespace uking::action
