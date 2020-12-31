#include "Game/AI/AI/aiArmorSearchKorokRoot.h"

namespace uking::ai {

ArmorSearchKorokRoot::ArmorSearchKorokRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ArmorSearchKorokRoot::~ArmorSearchKorokRoot() = default;

bool ArmorSearchKorokRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ArmorSearchKorokRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ArmorSearchKorokRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ArmorSearchKorokRoot::loadParams_() {
    getStaticParam(&mSearchKorokDis_s, "SearchKorokDis");
    getStaticParam(&mSearchRefreshFrame_s, "SearchRefreshFrame");
}

}  // namespace uking::ai
