#include "Game/AI/Action/actionDownloadPictureBook.h"

namespace uking::action {

DownloadPictureBook::DownloadPictureBook(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DownloadPictureBook::~DownloadPictureBook() = default;

bool DownloadPictureBook::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DownloadPictureBook::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DownloadPictureBook::leave_() {
    ksys::act::ai::Action::leave_();
}

void DownloadPictureBook::loadParams_() {}

void DownloadPictureBook::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
