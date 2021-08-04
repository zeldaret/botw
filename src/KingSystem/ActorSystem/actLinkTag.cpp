#include "KingSystem/ActorSystem/actLinkTag.h"

#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/System/SystemTimers.h"

namespace ksys::act {

LinkTag* LinkTag::construct(const BaseProc::CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) LinkTag(arg);
}

LinkTag::LinkTag(const BaseProc::CreateArg& arg) : BaseProc(arg), mJob(this, &LinkTag::calc) {
    mJobHandlers[3] = &mJob;
}

bool LinkTag::init() {
    if (mName == "LinkTagOr")
        mLinkTagType = Type::Or;
    else if (mName == "LinkTagNOr")
        mLinkTagType = Type::NOr;
    else if (mName == "LinkTagNAnd")
        mLinkTagType = Type::NAnd;
    else if (mName == "LinkTagXOr")
        mLinkTagType = Type::XOr;
    else if (mName == "LinkTagAnd")
        mLinkTagType = Type::And;
    else if (mName == "LinkTagCount")
        mLinkTagType = Type::Count;
    else if (mName == "LinkTagPulse")
        mLinkTagType = Type::Pulse;
    else if (mName == "LinkTagNone")
        mLinkTagType = Type::None;

    if (mName == "LinkTagNAnd" || mName == "LinkTagNOr")
        mFlags.set(LinkTagFlag::_4);

    int noChangeSignalValue = 0;
    mMubinIter.tryGetParamIntByKey(&noChangeSignalValue, "NoChangeSignal");
    if (noChangeSignalValue != 0)
        mFlags.set(LinkTagFlag::_40);

    int saveFlagOnOffTypeValue = 0;
    if (mMubinIter.tryGetParamIntByKey(&saveFlagOnOffTypeValue, "SaveFlagOnOffType")) {
        if (saveFlagOnOffTypeValue == 2)
            mFlags.set(LinkTagFlag::_200);
        else if (saveFlagOnOffTypeValue == 1)
            mFlags.set(LinkTagFlag::_100);
    }

    bool flagSet = false;
    isFlagSet(&flagSet, 0, mMapObj);
    updateIsFlagSetFlag(flagSet, 1, 1);
    if (flagSet) {
        mFlags.set(LinkTagFlag::_10);
        mTriggeredLinkFlags.makeAllOne();
        mFlags.set(LinkTagFlag::_30);
    } else {
        mFlags.reset(LinkTagFlag::_10);
        mTriggeredLinkFlags.makeAllZero();
        mFlags.reset(LinkTagFlag::_30);
    }
    return true;
}

void LinkTag::finalizeInit(BaseProc::InitContext* context) {
    if (mMapObj)
        mMapObj->registerBaseProc(this);
    BaseProc::finalizeInit_(context);
}

void LinkTag::calc() {
    if (this->mState != BaseProc::State::Delete && !_1de) {
        int currentExtraJobArrayIdx = BaseProcMgr::instance()->getCurrentExtraJobArrayIdx();
        s32 currentCounter = 0;
        if (SystemTimers::instance())
            currentCounter = SystemTimers::instance()->mFrameCounter;
        s32 oldCounter = mCounter;
        mCounter = currentCounter;

        switch (mLinkTagType) {
        case Type::Count:
            calcCount(currentCounter != oldCounter);
            break;
        case Type::Pulse:
            calcPulse(currentCounter != oldCounter);
            break;
        case Type::None:
            break;
        default:
            calcOther(currentCounter != oldCounter);
            break;
        }
        if (mFlags.isOff(LinkTagFlag::_1)) {
            mFlags.set(LinkTagFlag::_1);
            if (mMapObj && mMapObj->getLinkData())
                mMapObj->getLinkData()->setNumExecLinkTagTo1();
        }
        mFlags.reset(LinkTagFlag::_1000);
        mJobFlags.setBitOff(currentExtraJobArrayIdx ^ 1);
    }
}

void LinkTag::calcCount(bool update) {
    if (mFlags.isOff(LinkTagFlag::_1) || !mMapObj || !mMapObj->getLinkData())
        return;

    auto& links = mMapObj->getLinkData()->mLinksToSelf.links;
    s8 linkCount = 0;

    for (s32 i = 0; i < (links.size()); i++) {
        auto& link = links[i];
        if (link.type <= map::MapLinkDefType::ChangeAtnSig && isTriggered(&link, i))
            linkCount++;
    }

    mFlags.reset(LinkTagFlag::_10);
    if (linkCount != mTagCount) {
        mTagCount = linkCount;
        gdt::Manager::instance()->setS32(linkCount, this->mMapObj->getRevivalGameDataFlagHash());
        updateIsFlagSetFlag(mTagCount > 0, 0, update);
    }
}

void LinkTag::updateIsFlagSetFlag(bool isFlagSet, bool a3, bool a4) {
    if (!mMapObj)
        return;

    mFlags.change(LinkTagFlag::_8, isFlagSet);

    if (mFlags.isOff(LinkTagFlag::_40) || a3) {
        mMapObj->getFlags0().change(map::Object::Flag0::_100, isFlagSet);

        if (mFlags.isOff(LinkTagFlag::_40)) {
            int frameCounter = 0;
            auto mapFlags = mMapObj->getFlags();
            if (SystemTimers::instance())
                frameCounter = SystemTimers::instance()->mFrameCounter;

            auto mapLinkData = mMapObj->getLinkData();
            if (mapLinkData) {
                auto& mapLinks = mapLinkData->mLinksOther.links;
                for(auto it = mapLinks.begin(), end = mapLinks.end(); it != end; ++it){
                    auto& mapLink = *it;
                    if (!mapLink.other_obj) {
                        continue;
                    }

                    if (isFlagSet != mapFlags.isOn(map::Object::Flag::IsLinkTagNAndOrNOr)) {
                        switch (mapLink.type) {
                        case map::MapLinkDefType::Create:
                        case map::MapLinkDefType::MtxCopyCreate:
                            if (_1E8 == frameCounter) {
                                mapLink.other_obj->getFlags0().reset(map::Object::Flag0::_10000000);
                            }
                            break;
                        case map::MapLinkDefType::Delete:
                            if (mapLink.other_obj->getFlags0().isOff(
                                    map::Object::Flag0::_20000000)) {
                                mapLink.other_obj->getFlags0().set(map::Object::Flag0::_20000000);
                                _1E8 = frameCounter;
                            }
                            break;
                        }
                    } else {
                        switch (mapLink.type) {
                        case map::MapLinkDefType::Create:
                        case map::MapLinkDefType::MtxCopyCreate:
                            if (mapLink.other_obj->getFlags0().isOff(
                                    map::Object::Flag0::_10000000)) {
                                mapLink.other_obj->getFlags0().set(map::Object::Flag0::_10000000);
                                _1E8 = frameCounter;
                            }
                            break;
                        case map::MapLinkDefType::Delete:
                            if (_1E8 == frameCounter)
                                mapLink.other_obj->getFlags0().reset(map::Object::Flag0::_20000000);
                            break;
                        }
                    }
                }
            }
        }
    }

    bool v0 = isFlagSet != mFlags.isOn(LinkTagFlag::_4);

    if (a4) {
        mFlags.reset(LinkTagFlag::_800);
    }
    if (v0) {
        if (mFlags.isOff(LinkTagFlag::_400)) {
            mFlags.set(LinkTagFlag::_800);
        }
        mFlags.set(LinkTagFlag::_400);
    } else if (mFlags.isOn(LinkTagFlag::_800)) {
        mFlags.reset(LinkTagFlag::_C00);
    }

    if (!a3) {
        auto mapLinkData = mMapObj->getLinkData();
        if (mapLinkData) {
            if (mapLinkData->isGenGroupInitState3() &&
                (mapLinkData->findLinkWithType(map::MapLinkDefType::Create) ||
                 mapLinkData->findLinkWithType(map::MapLinkDefType::Delete) ||
                 mapLinkData->findLinkWithType(map::MapLinkDefType::MtxCopyCreate))) {
                mapLinkData->sub_7100D4FA90();
            }
        }
    }
}

}  // namespace ksys::act
