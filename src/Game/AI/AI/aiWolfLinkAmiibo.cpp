#include "Game/AI/AI/aiWolfLinkAmiibo.h"

namespace uking::ai {

WolfLinkAmiibo::WolfLinkAmiibo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkAmiibo::~WolfLinkAmiibo() = default;

bool WolfLinkAmiibo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkAmiibo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkAmiibo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkAmiibo::loadParams_() {
    getStaticParam(&mAreaSearchCharacterRadius_s, "AreaSearchCharacterRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mAreaSearchRadius_s, "AreaSearchRadius");
}

}  // namespace uking::ai
