#include "Game/AI/Action/actionKorokFlowerVanish.h"

namespace uking::action {

KorokFlowerVanish::KorokFlowerVanish(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KorokFlowerVanish::~KorokFlowerVanish() = default;

bool KorokFlowerVanish::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KorokFlowerVanish::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KorokFlowerVanish::leave_() {
    ksys::act::ai::Action::leave_();
}

void KorokFlowerVanish::loadParams_() {}

void KorokFlowerVanish::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
