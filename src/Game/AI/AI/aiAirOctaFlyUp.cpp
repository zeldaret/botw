#include "Game/AI/AI/aiAirOctaFlyUp.h"
#include "Game/DLC/aocHardModeManager.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/AirOctaDataMgrTemp.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

AirOctaFlyUp::AirOctaFlyUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaFlyUp::~AirOctaFlyUp() = default;

bool AirOctaFlyUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}
void sub_710115b070(ksys::as::ASList *this_, f32 a2, f32 a3, const sead::SafeString& a4, int a5, int a6, bool a7);
void AirOctaFlyUp::calc_(){
    if (auto* data_mgr = getDataMgr()) {
        // I added VFR::getDeltaFrame and changed VFR::getDeltaTime to refer to mDeltaTimes array.
        auto deltaTime = ksys::VFR::instance()->getDeltaTime();
        mElapsedTime += deltaTime;
        auto v11 = sead::Mathf::min( 1.0f, mElapsedTime / *mFlyUpDuration_s);
        auto v12 = v11 * 2.f;
        auto v13 = (v11 * 2.f) - 1.f;
        auto v14 = v12 < 1.f ? sead::Mathf::exp(v13 * 10.f) : 2.f - sead::Mathf::exp(v13 * -10.f);
        auto v15 = v14 * 0.5f;
        data_mgr->unk_114 = v15 * *mTargetDistance_d;
        data_mgr->sub_71002fb17c();
        u32 y_ = *(u32*)&(getActor()->getMtx().m[1][3]);
        if (isCurrentChild("終了")) { // "End"
            if (!mIsEnded) {
                auto currentChild = getCurrentChild();
                if (currentChild->isFinished() || currentChild->isFailed() ){
                    auto ASList = getActor()->getASList();
                    if (ASList){
                        sub_710115b070(ASList, -1.f, -1.f, "Wait", 0, 0, true);
                    }
                    mIsEnded = true;
                } else if (!mIsEnded) {
                    return;
                }
            }  

            if ((v15 >= 1.f && *(float*)&y_  >= getDataMgr()->unk_fc.y) || mElapsedTime >= (*mFlyUpDuration_s * 3.0f)) {
                ksys::act::ActorConstDataAccess linkData;
                if (ksys::act::acquireActor(&getDataMgr()->unk_00, &linkData)) {
                    UserData = 3;
                    getActor()->sendMessage(*linkData.getMessageTransceiverId(), 0x80000C8, &UserData, false);
                }
            }
        } else if (*(float*)&y_   - AirOctaY >= *mTargetDistance_d * 0.9f || mElapsedTime >= (*mFlyUpDuration_s * 3.0f)) {
            ksys::act::ActorConstDataAccess linkData;
            if (ksys::act::acquireActor(&getDataMgr()->unk_00, &linkData)) {
                UserData = 2;
                getActor()->sendMessage(*linkData.getMessageTransceiverId(), 0x80000C8, &UserData, false);
            }
        }
    }
}



bool AirOctaFlyUp::handleMessage_( const ksys::Message& message) {
    if (message.getType().value == 0x80000c8) {
        u32* user_data = static_cast<u32*>(message.getUserData());
        auto* data_mgr = getDataMgr();
        if (!data_mgr) {
            return true;
        }
        if (user_data != nullptr) {
            if (*user_data == 3) {
                Ai::changeChild( "終了"); //END IN JAPANESE
            } else if (*user_data == 4) {
                ActionBase::setFinished();
            }
        }
        return true;
    }
    return false;
}

void AirOctaFlyUp::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* data_mgr = getDataMgr()){
    data_mgr->unk_114 = 0;
    data_mgr->uking::AirOctaDataMgr::sub_71002fb17c();
    }
    auto &mtx = mActor->getMtx();
    AirOctaY = mtx(1, 3);
    ksys::act::ai::Ai::changeChild("開始");
}

void AirOctaFlyUp::leave_() {
    if (auto* data_mgr = getDataMgr()){
    data_mgr->unk_118 = *mTargetDistance_d + data_mgr->unk_118;
    data_mgr->unk_114 = 0;
    data_mgr->uking::AirOctaDataMgr::sub_71002fb17c();
    }
}

void AirOctaFlyUp::loadParams_() {
    getStaticParam(&mFlyUpDuration_s, "FlyUpDuration");
    getDynamicParam(&mTargetDistance_d, "TargetDistance");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai

