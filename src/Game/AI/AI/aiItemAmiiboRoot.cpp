#include "Game/AI/AI/aiItemAmiiboRoot.h"

namespace uking::ai {

ItemAmiiboRoot::ItemAmiiboRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ItemAmiiboRoot::~ItemAmiiboRoot() = default;

bool ItemAmiiboRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ItemAmiiboRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ItemAmiiboRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ItemAmiiboRoot::loadParams_() {
    getMapUnitParam(&mAmiiboCharacterId_m, "AmiiboCharacterId");
    getMapUnitParam(&mAmiiboNumberingId_m, "AmiiboNumberingId");
}

}  // namespace uking::ai
