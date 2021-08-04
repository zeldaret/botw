#include "KingSystem/ActorSystem/actLinkTag.h"

#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapPlacementGlobal.h"

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

void LinkTag::updateIsFlagSetFlag(bool isFlagSet, bool a3, bool a4) {
    if (!mMapObj)
        return;

    if (isFlagSet)
        mFlags.set(LinkTagFlag::_8);
    else
        mFlags.reset(LinkTagFlag::_8);

    if (mFlags.isOff(LinkTagFlag::_40) || a3) {
        if (isFlagSet)
            mMapObj->getFlags0().set(map::Object::Flag0::_100);
        else
            mMapObj->getFlags0().reset(map::Object::Flag0::_100);

        if (mFlags.isOff(LinkTagFlag::_40)) {
            int frameCounter = map::PlacementGlobal::instance()->frameCounter;
            if (mMapObj->getLinkData()) {
                auto mapLinks = mMapObj->getLinkData()->mLinksOther.links;
                if (((isFlagSet ^ mMapObj->getFlags().isOn(map::Object::Flag::IsLinkTagNAndOrNOr)) &
                     1) != 0) {
                    for (int i = 0; i < mapLinks.size(); i++) {
                        if (mapLinks[i].other_obj) {
                            if (mapLinks[i].type == map::MapLinkDefType::Create ||
                                mapLinks[i].type == map::MapLinkDefType::MtxCopyCreate) {
                                if (_1E8 == frameCounter) {
                                    mapLinks[i].other_obj->getFlags0().reset(
                                        map::Object::Flag0::_10000000);
                                }
                            } else if (mapLinks[i].type == map::MapLinkDefType::Delete &&
                                       (mapLinks[i].other_obj->getFlags0().isOff(
                                           map::Object::Flag0::_20000000))) {
                                mapLinks[i].other_obj->getFlags0().set(
                                    map::Object::Flag0::_20000000);
                                _1E8 = frameCounter;
                            }
                        }
                    }
                } else {
                    for (int i = 0; i < mapLinks.size(); i++) {
                        if (mapLinks[i].other_obj) {
                            if (mapLinks[i].type == map::MapLinkDefType::MtxCopyCreate ||
                                mapLinks[i].type == map::MapLinkDefType::Create) {
                                if (mapLinks[i].other_obj->getFlags0().isOff(
                                        map::Object::Flag0::_10000000)) {
                                    mapLinks[i].other_obj->getFlags0().set(
                                        map::Object::Flag0::_10000000);
                                    _1E8 = frameCounter;
                                }
                            } else if (mapLinks[i].type == map::MapLinkDefType::Delete) {
                                if (_1E8 == frameCounter) {
                                    mapLinks[i].other_obj->getFlags0().reset(
                                        map::Object::Flag0::_10000000);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // TODO continue LABEL_43
}

}  // namespace ksys::act
