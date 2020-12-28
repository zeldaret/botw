#include "Game/AI/Action/actionForkASPlay.h"

namespace uking::action {

ForkASPlay::ForkASPlay(const InitArg& arg) : ForkASPlayBase(arg) {}

ForkASPlay::~ForkASPlay() = default;

void ForkASPlay::loadParams_() {
    ForkASPlayBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
