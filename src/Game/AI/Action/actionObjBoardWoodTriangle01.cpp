#include "Game/AI/Action/actionObjBoardWoodTriangle01.h"

namespace uking::action {

ObjBoardWoodTriangle01::ObjBoardWoodTriangle01(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ObjBoardWoodTriangle01::~ObjBoardWoodTriangle01() = default;

bool ObjBoardWoodTriangle01::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ObjBoardWoodTriangle01::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ObjBoardWoodTriangle01::leave_() {
    ksys::act::ai::Action::leave_();
}

void ObjBoardWoodTriangle01::loadParams_() {}

void ObjBoardWoodTriangle01::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
