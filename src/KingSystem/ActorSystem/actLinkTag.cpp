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
    else if(mName == "LinkTagNOr")
        mLinkTagType = Type::NOr;
    else if(mName == "LinkTagNAnd")
        mLinkTagType = Type::NAnd;
    else if(mName == "LinkTagXOr")
        mLinkTagType = Type::XOr;
    else if(mName == "LinkTagAnd")
        mLinkTagType = Type::And;
    else if(mName == "LinkTagCount")
        mLinkTagType = Type::Count;
    else if(mName == "LinkTagPulse")
        mLinkTagType = Type::Pulse;
    else if(mName == "LinkTagNone")
        mLinkTagType = Type::None;

    if(mName == "LinkTagNAnd" || mName == "LinkTagNOr")
        mFlags.set(LinkTagFlag::_4);
    
    int noChangeSignalValue = 0;
    mMubinIter.tryGetParamIntByKey(&noChangeSignalValue, "NoChangeSignal");
    if(noChangeSignalValue != 0)
        mFlags.set(LinkTagFlag::_40);
    
    int saveFlagOnOffTypeValue = 0;
    if(mMubinIter.tryGetParamIntByKey(&saveFlagOnOffTypeValue, "SaveFlagOnOffType")){
        if(saveFlagOnOffTypeValue == 2)
            mFlags.set(LinkTagFlag::_200);
        else if(saveFlagOnOffTypeValue == 1)
            mFlags.set(LinkTagFlag::_100);
    }

    bool flagSet = false;
    isFlagSet(&flagSet, 0, mMapObj);
    updateIsFlagSetFlag(flagSet, 1, 1);
    if(flagSet){
        mFlags.set(LinkTagFlag::_10);
        mTriggeredLinkFlags.makeAllOne();
        mFlags.set(LinkTagFlag::_30);
    }
    else {
        mFlags.reset(LinkTagFlag::_10);
        mTriggeredLinkFlags.makeAllZero();
        mFlags.reset(LinkTagFlag::_30);
    }
    return true;
}

}  // namespace ksys::act
