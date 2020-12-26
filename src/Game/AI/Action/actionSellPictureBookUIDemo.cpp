#include "Game/AI/Action/actionSellPictureBookUIDemo.h"

namespace uking::action {

SellPictureBookUIDemo::SellPictureBookUIDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SellPictureBookUIDemo::~SellPictureBookUIDemo() = default;

bool SellPictureBookUIDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SellPictureBookUIDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SellPictureBookUIDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void SellPictureBookUIDemo::loadParams_() {
    getDynamicParam(&mSellPicturePack_d, "SellPicturePack");
}

void SellPictureBookUIDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
