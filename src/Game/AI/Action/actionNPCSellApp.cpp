#include "Game/AI/Action/actionNPCSellApp.h"

namespace uking::action {

NPCSellApp::NPCSellApp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSellApp::~NPCSellApp() = default;

bool NPCSellApp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCSellApp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCSellApp::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCSellApp::loadParams_() {}

void NPCSellApp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
