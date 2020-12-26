#include "Game/AI/Action/actionCreateEpona.h"

namespace uking::action {

CreateEpona::CreateEpona(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CreateEpona::~CreateEpona() = default;

bool CreateEpona::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateEpona::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateEpona::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateEpona::loadParams_() {
    getStaticParam(&mAreaSearchCharacterRadius_s, "AreaSearchCharacterRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mAreaSearchRadius_s, "AreaSearchRadius");
    getStaticParam(&mCreateStartRate_s, "CreateStartRate");
}

void CreateEpona::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
