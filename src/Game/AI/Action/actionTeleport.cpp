#include "Game/AI/Action/actionTeleport.h"

namespace uking::action {

Teleport::Teleport(const InitArg& arg) : TeleportBase(arg) {}

Teleport::~Teleport() = default;

bool Teleport::init_(sead::Heap* heap) {
    return TeleportBase::init_(heap);
}

void Teleport::enter_(ksys::act::ai::InlineParamPack* params) {
    TeleportBase::enter_(params);
}

void Teleport::leave_() {
    TeleportBase::leave_();
}

void Teleport::loadParams_() {
    TeleportBase::loadParams_();
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mDistY_s, "DistY");
}

void Teleport::calc_() {
    TeleportBase::calc_();
}

}  // namespace uking::action
