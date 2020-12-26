#include "Game/AI/Action/actionWindmill_WingWithAutoAnime.h"

namespace uking::action {

Windmill_WingWithAutoAnime::Windmill_WingWithAutoAnime(const InitArg& arg) : Windmill_Wing(arg) {}

Windmill_WingWithAutoAnime::~Windmill_WingWithAutoAnime() = default;

bool Windmill_WingWithAutoAnime::init_(sead::Heap* heap) {
    return Windmill_Wing::init_(heap);
}

void Windmill_WingWithAutoAnime::enter_(ksys::act::ai::InlineParamPack* params) {
    Windmill_Wing::enter_(params);
}

void Windmill_WingWithAutoAnime::leave_() {
    Windmill_Wing::leave_();
}

void Windmill_WingWithAutoAnime::loadParams_() {
    Windmill_Wing::loadParams_();
}

void Windmill_WingWithAutoAnime::calc_() {
    Windmill_Wing::calc_();
}

}  // namespace uking::action
