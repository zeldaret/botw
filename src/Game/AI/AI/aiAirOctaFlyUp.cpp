#include "Game/AI/AI/aiAirOctaFlyUp.h"
#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "Game/AI/AI/aiAirOctaRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

AirOctaFlyUp::AirOctaFlyUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaFlyUp::~AirOctaFlyUp() = default;

bool AirOctaFlyUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}
// NON_MATCHING: stack for the sendMessage() message, type that y is casted to
void AirOctaFlyUp::calc_() {
    auto* data_mgr = getDataMgr();
    if (!data_mgr) {
        return;
    }
    auto dt = ksys::VFR::instance()->getDeltaTime();
    mElapsedTime += dt;
    auto fly_up_turning_pts =
        (sead::Mathf::min(1.0f, mElapsedTime / *mFlyUpDuration_s) * 2.f) - 1.f;
    auto fly_up_multiplier = fly_up_turning_pts < 1.f ?
                                 sead::Mathf::exp((fly_up_turning_pts * 2.f) - 1.f * 10.f) :
                                 2.f - sead::Mathf::exp((fly_up_turning_pts * 2.f) - 1.f * -10.f);
    data_mgr->unk_114 = fly_up_multiplier * 0.5f * *mTargetDistance_d;
    data_mgr->changeOctasYheightMaybe();
    auto y = getActor()->getMtx().m[1][3];
    if (isCurrentChild("終了")) {  // "End"
        if (!mIsEnded) {
            auto currentChild = getCurrentChild();
            if (currentChild->isFinished() || currentChild->isFailed()) {
                auto as_list = getActor()->getASList();
                if (as_list) {
                    as_list->startAnimationMaybe(-1.f, -1.f, "Wait", 0, 0, true);
                }
                mIsEnded = true;
            } else if (!mIsEnded) {
                return;
            }
        }
        if ((fly_up_multiplier * 0.5f >= 1.f && y >= getDataMgr()->vec_F8.y) ||
            mElapsedTime >= (*mFlyUpDuration_s * 3.0f)) {
            ksys::act::ActorConstDataAccess linkData;
            if (ksys::act::acquireActor(&getDataMgr()->mBaseProcLink, &linkData)) {
                mUserData = 3;
                getActor()->sendMessage(*linkData.getMessageTransceiverId(), 0x80000C8, &mUserData,
                                        false);
            }
        }
    } else if (y - AirOctaY >= *mTargetDistance_d * 0.9f ||
               mElapsedTime >= (*mFlyUpDuration_s * 3.0f)) {
        ksys::act::ActorConstDataAccess linkData;
        if (ksys::act::acquireActor(&getDataMgr()->mBaseProcLink, &linkData)) {
            mUserData = 2;
            getActor()->sendMessage(*linkData.getMessageTransceiverId(), 0x80000C8, &mUserData,
                                    false);
        }
    }
}

bool AirOctaFlyUp::handleMessage_(const ksys::Message& message) {
    if (message.getType().value != 0x80000c8) {
        return false;
    }
    u32* user_data = static_cast<u32*>(message.getUserData());
    auto* data_mgr = getDataMgr();
    if (!data_mgr) {
        return true;
    }
    if (user_data == nullptr) {
        return true;
    }
    if (*user_data == 3) {
        Ai::changeChild("終了");  // Ended
    } else if (*user_data == 4) {
        ActionBase::setFinished();
    }
    return true;
}

void AirOctaFlyUp::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* data_mgr = getDataMgr()) {
        data_mgr->unk_114 = 0;
        data_mgr->changeOctasYheightMaybe();
    }
    auto& mtx = mActor->getMtx();
    AirOctaY = mtx(1, 3);
    ksys::act::ai::Ai::changeChild("開始");
}

void AirOctaFlyUp::leave_() {
    if (auto* data_mgr = getDataMgr()) {
        data_mgr->unk_118 += *mTargetDistance_d;
        data_mgr->unk_114 = 0;
        data_mgr->changeOctasYheightMaybe();
    }
}
// NON_MATCHING: addresses that variables are loaded from
void AirOctaFlyUp::loadParams_() {
    getStaticParam(&mFlyUpDuration_s, "FlyUpDuration");
    getDynamicParam(&mTargetDistance_d, "TargetDistance");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
