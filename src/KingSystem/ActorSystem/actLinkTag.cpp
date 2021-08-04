#include "KingSystem/ActorSystem/actLinkTag.h"

namespace ksys::act {

LinkTag* LinkTag::construct(const BaseProc::CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) LinkTag(arg);
}

LinkTag::LinkTag(const BaseProc::CreateArg& arg) : BaseProc(arg), mJob(this, &LinkTag::calc) {
    mJobHandlers[3] = &mJob;
}

bool LinkTag::init(){
    if(mName == "LinkTagOr")
        mLinkTagType = Type::Or;
    if(mName == "LinkTagNOr")
        mLinkTagType = Type::NOr;
    if(mName == "LinkTagNAnd")
        mLinkTagType = Type::NAnd;
    if(mName == "LinkTagXOr")
        mLinkTagType = Type::XOr;
    if(mName == "LinkTagAnd")
        mLinkTagType = Type::And;
    if(mName == "LinkTagCount")
        mLinkTagType = Type::Count;
    if(mName == "LinkTagPulse")
        mLinkTagType = Type::Pulse;
    if(mName == "LinkTagNone")
        mLinkTagType = Type::None;

    if(mName == "LinkTagNAnd" || mName == "LinkTagNOr")
        mFlags.set(LinkTagFlag::FLAG_PLACEHOLDER_4);
    
    int noChangeSignalValue = 0;
    mMubinIter.tryGetParamIntByKey(&noChangeSignalValue, "NoChangeSignal");
    if(noChangeSignalValue != 0)
        mFlags.set(LinkTagFlag::FLAG_PLACEHOLDER_40);
    
    int saveFlagOnOffTypeValue = 0;
    if(mMubinIter.tryGetParamIntByKey(&saveFlagOnOffTypeValue, "SaveFlagOnOffType")){
        if(saveFlagOnOffTypeValue == 2)
            mFlags.set(LinkTagFlag::FLAG_PLACEHOLDER_200);
        else if(saveFlagOnOffTypeValue == 1)
            mFlags.set(LinkTagFlag::FLAG_PLACEHOLDER_100);
    }

    bool flagSet = false;
    isFlagSet(&flagSet, 0, mMapObj);
    updateIsFlagSetFlag(flagSet, 1, 1);
    if(flagSet){
        mFlags.set(LinkTagFlag::FLAG_PLACEHOLDER_10);
        mTriggeredLinkFlags.makeAllOne();
        mFlags.set(LinkTagFlag::FLAG_PLACEHOLDER_30);
    }
    else {
        mFlags.reset(LinkTagFlag::FLAG_PLACEHOLDER_10);
        mTriggeredLinkFlags.makeAllZero();
        mFlags.reset(LinkTagFlag::FLAG_PLACEHOLDER_30);
    }
    return true;
}

}  // namespace ksys::act
