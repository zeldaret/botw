#include "Game/AI/Action/actionTerrainCalcCenter.h"

namespace uking::action {

TerrainCalcCenter::TerrainCalcCenter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TerrainCalcCenter::~TerrainCalcCenter() = default;

bool TerrainCalcCenter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TerrainCalcCenter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TerrainCalcCenter::leave_() {
    ksys::act::ai::Action::leave_();
}

void TerrainCalcCenter::loadParams_() {
    getDynamicParam(&mlevel_d, "level");
    getDynamicParam(&mtype_d, "type");
    getDynamicParam(&mmeshReso_d, "meshReso");
    getDynamicParam(&mpos_d, "pos");
}

void TerrainCalcCenter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
