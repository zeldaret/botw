#include "Game/AI/Action/actionSiteBossCreateIceSplinter.h"

namespace uking::action {

SiteBossCreateIceSplinter::SiteBossCreateIceSplinter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossCreateIceSplinter::~SiteBossCreateIceSplinter() = default;

bool SiteBossCreateIceSplinter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossCreateIceSplinter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossCreateIceSplinter::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossCreateIceSplinter::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIgnitionNum_d, "IgnitionNum");
}

void SiteBossCreateIceSplinter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
