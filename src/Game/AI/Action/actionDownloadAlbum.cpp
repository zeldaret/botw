#include "Game/AI/Action/actionDownloadAlbum.h"

namespace uking::action {

DownloadAlbum::DownloadAlbum(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DownloadAlbum::~DownloadAlbum() = default;

bool DownloadAlbum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DownloadAlbum::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DownloadAlbum::leave_() {
    ksys::act::ai::Action::leave_();
}

void DownloadAlbum::loadParams_() {}

void DownloadAlbum::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
