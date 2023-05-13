#include "Game/AI/AI/aiActorWaterDepthSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ActorWaterDepthSelect::ActorWaterDepthSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ActorWaterDepthSelect::~ActorWaterDepthSelect() = default;

bool ActorWaterDepthSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool ActorWaterDepthSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool ActorWaterDepthSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool ActorWaterDepthSelect::init_(sead::Heap* heap) {
    return true;
}

void ActorWaterDepthSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (isDeep() && isUnderwater()) {
        changeChild("深瀬", params);
    } else {
        changeChild("浅瀬", params);
    }
}

void ActorWaterDepthSelect::calc_() {
    if (*mOnEnterOnly_s)
        return;

    auto is_deep = isDeep() && isUnderwater();
    if (*mForceDeepChange_s && is_deep) {
        if (!isCurrentChild("深瀬")) {
            changeChild("深瀬");
            return;
        }
    }

    if (getCurrentChild()->isChangeable()) {
        if (is_deep && !isCurrentChild("深瀬"))
            changeChild("深瀬");
        else if (!is_deep && !isCurrentChild("浅瀬"))
            changeChild("浅瀬");
    }
}

void ActorWaterDepthSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ActorWaterDepthSelect::loadParams_() {
    getStaticParam(&mDeepDepth_s, "DeepDepth");
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
    getStaticParam(&mForceDeepChange_s, "ForceDeepChange");
}

bool ActorWaterDepthSelect::isDeep() const {
    return 0.0 < *mDeepDepth_s && mActor->get68f().load();
}

bool ActorWaterDepthSelect::isUnderwater() const {
    float y_w = mActor->getMtx().m[1][3];
    return mActor->get6f0() - y_w > *mDeepDepth_s;
}

}  // namespace uking::ai
