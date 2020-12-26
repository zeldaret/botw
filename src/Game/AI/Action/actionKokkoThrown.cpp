#include "Game/AI/Action/actionKokkoThrown.h"

namespace uking::action {

KokkoThrown::KokkoThrown(const InitArg& arg) : Thrown(arg) {}

KokkoThrown::~KokkoThrown() = default;

bool KokkoThrown::init_(sead::Heap* heap) {
    return Thrown::init_(heap);
}

void KokkoThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    Thrown::enter_(params);
}

void KokkoThrown::leave_() {
    Thrown::leave_();
}

void KokkoThrown::loadParams_() {
    Thrown::loadParams_();
    getStaticParam(&mGravityScale_s, "GravityScale");
    getAITreeVariable(&mIsChangeableStateFreeFall_a, "IsChangeableStateFreeFall");
}

void KokkoThrown::calc_() {
    Thrown::calc_();
}

}  // namespace uking::action
