#include "Game/AI/AI/aiAirOctaFlyUp.h"
#include "Game/DLC/aocHardModeManager.h"
#include "KingSystem/Utils/Thread/Message.h"



namespace uking::ai {

AirOctaFlyUp::AirOctaFlyUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaFlyUp::~AirOctaFlyUp() = default;

bool AirOctaFlyUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool AirOctaFlyUp::handleMessage_( const ksys::Message& message) {
    if (message.getType().value == 0x80000c8) {
        u32* user_data = static_cast<u32*>(message.getUserData());
        auto* data_mgr = sead::DynamicCast<AirOctaDataMgr>((AirOctaDataMgr*)*mAirOctaDataMgr_a);
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
    if (auto* data_mgr = sead::DynamicCast<AirOctaDataMgr>((AirOctaDataMgr*)*mAirOctaDataMgr_a)){
    data_mgr->unk_114 = 0;
    data_mgr->sub_71002FB17C();
    }
    auto &mtx = getActor()->getMtx();
    AirOctaY = mtx(1, 3);
    ksys::act::ai::Ai::changeChild("開始");
    
}

void AirOctaFlyUp::leave_() {
    if (auto* data_mgr = sead::DynamicCast<AirOctaDataMgr>((AirOctaDataMgr*)*mAirOctaDataMgr_a)){
    data_mgr->unk_118 = *mTargetDistance_d + data_mgr->unk_118;
    data_mgr->unk_114 = 0;
    return data_mgr->sub_71002FB17C();
    }
}

float sub_71002FB17C();

void AirOctaFlyUp::loadParams_() {
    getStaticParam(&mFlyUpDuration_s, "FlyUpDuration");
    getDynamicParam(&mTargetDistance_d, "TargetDistance");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai

