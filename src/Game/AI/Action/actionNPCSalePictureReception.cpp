#include "Game/AI/Action/actionNPCSalePictureReception.h"

namespace uking::action {

NPCSalePictureReception::NPCSalePictureReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSalePictureReception::~NPCSalePictureReception() = default;

bool NPCSalePictureReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCSalePictureReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCSalePictureReception::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCSalePictureReception::loadParams_() {
    getDynamicParam(&mTableName_d, "TableName");
}

void NPCSalePictureReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
