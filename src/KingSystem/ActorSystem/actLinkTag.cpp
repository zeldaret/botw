#include "KingSystem/ActorSystem/actLinkTag.h"

#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/System/MCMgr.h"
#include "KingSystem/System/SystemTimers.h"

namespace ksys::act {

LinkTag* LinkTag::construct(const BaseProc::CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) LinkTag(arg);
}

LinkTag::LinkTag(const BaseProc::CreateArg& arg) : BaseProc(arg), mJob(this, &LinkTag::calc) {
    mJobHandlers[3] = &mJob;
}

LinkTag::~LinkTag() {
    if (getSceneStatus() != 4) {
        mJobFlags.load();
    }
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
        mFlags.set(LinkTagFlag::_20);
    } else {
        mFlags.reset(LinkTagFlag::_10);
        mTriggeredLinkFlags.makeAllZero();
        mFlags.reset(LinkTagFlag::_20);
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

inline s8 LinkTag::getSelfLinkCount() {
    auto& links = mMapObj->getLinkData()->mLinksToSelf.links;
    s8 linkCount = 0;

    // s32 end = std::min(links.size(), 0x60);
    s32 end = links.size() < 0x60 ? links.size() : 0x60;
    for (s32 i = 0; i < end; i++) {
        auto& link = links[i];
        if (link.type <= map::MapLinkDefType::ChangeAtnSig && isTriggered(&link, i))
            linkCount += 1;
    }
    return linkCount;
}

void LinkTag::calcCount(bool update) {
    if (mFlags.isOff(LinkTagFlag::_1) || !mMapObj || !mMapObj->getLinkData())
        return;

    auto& links = mMapObj->getLinkData()->mLinksToSelf.links;
    s8 linkCount = 0;

    s32 end = std::min(links.size(), 0x60);
    // s32 end = links.size() < 0x60 ? links.size() : 0x60;
    for (s32 i = 0; i < end; i++) {
        auto& link = links[i];
        if (link.type <= map::MapLinkDefType::ChangeAtnSig && isTriggered(&link, i))
            linkCount += 1;
    }

    mFlags.reset(LinkTagFlag::_10);
    if (linkCount != mTagCount) {
        mTagCount = linkCount;
        gdt::Manager::instance()->setS32ByIdxForLinkTag(linkCount,
                                                        mMapObj->getRevivalGameDataFlagHash());
        updateIsFlagSetFlag(mTagCount > 0, 0, update);
    }
}

void LinkTag::calcPulse(bool update) {
    if (mFlags.isOff(LinkTagFlag::_1)) {
        if (mMapObj && mMapObj->getLinkData()) {  // maybe inlined getSelfLinkCount?
            auto& links = mMapObj->getLinkData()->mLinksToSelf.links;
            s32 end = links.size() < 0x60 ? links.size() : 0x60;
            for (s32 i = 0; i < end; i++) {
                auto& link = links[i];
                if (link.type <= map::MapLinkDefType::ChangeAtnSig && isTriggered(&link, i))
                    mTagCount += 1;
            }
        }
        mFlags.reset(LinkTagFlag::_10);
        return;
    }

    bool something = mFlags.isOn(LinkTagFlag::_80);
    s8 selfLinkCount = getSelfLinkCount();
    s8 oldTagCount = mTagCount;
    mFlags.reset(LinkTagFlag::_10);
    mTagCount = selfLinkCount;

    if (update) {
        if ((selfLinkCount != oldTagCount) == mFlags.isOn(LinkTagFlag::_8)) {
            something = mFlags.isOn(LinkTagFlag::_80);
        } else {
            something = true;
            updateIsFlagSetFlag(selfLinkCount != oldTagCount, 0, 1);
        }

        if (selfLinkCount == oldTagCount) {
            mFlags.reset(LinkTagFlag::_2000);
        } else {
            mFlags.set(LinkTagFlag::_2000);
            if (mMapObj && mMapObj->getLinkData()) {
                for (auto& link : mMapObj->getLinkData()->mLinksOther.links) {
                    if (link.type == map::MapLinkDefType::OffWaitRevival && link.other_obj) {
                        gdt::Manager::instance()->setBoolByHash(
                            false, link.other_obj->getRevivalGameDataFlagHash());
                    }
                }
            }
        }
    }
    if (!something)
        return;

    if (mMapObj) {
        if (mMapObj->getLinkData()) {
            for (auto& link : mMapObj->getLinkData()->mLinksOther.links) {
                ActorLinkConstDataAccess acc{};
                link.getObjectProcWithAccessor(acc);
                triggerLink(acc);
            }
        }
        if (mMapObj->getRevivalGameDataFlagHash() != gdt::InvalidHandle) {
            BaseProcMgr::instance()->setPushActorJobType3InsteadOf6(true);
        }
    }
    mFlags.reset(LinkTagFlag::_80);
}

void LinkTag::onEnterCalc() {
    if (mLinkTagType == Type::Pulse) {
        mFlags.set(LinkTagFlag::_4000);
        if (mMapObj) {
            auto mapLinkData = mMapObj->getLinkData();
            if (mapLinkData) {
                // inlined getSelfLinkCount?
                auto& links = mMapObj->getLinkData()->mLinksToSelf.links;

                // s32 end = std::min(links.size(), 0x60);
                s32 end = links.size() < 0x60 ? links.size() : 0x60;
                for (s32 i = 0; i < end; i++) {
                    auto& link = links[i];
                    if (link.type <= map::MapLinkDefType::ChangeAtnSig && isTriggered(&link, i))
                        mTagCount += 1;
                }
            }
        }
        mFlags.reset(LinkTagFlag::_10);
    }
    _1dd = 0;
    mFlags.reset(LinkTagFlag::_1081);
    mFlags.set(LinkTagFlag::_80);

    if (mMapObj) {
        if (mMapObj->getRevivalGameDataFlagHash() != gdt::InvalidHandle)
            mFlags.set(LinkTagFlag::_4000);
        s8 extraJobArrayId = BaseProcMgr::instance()->getCurrentExtraJobArrayIdx();
        if (!isDeletedOrDeleting() && mJobFlags.setBitOn(extraJobArrayId)) {
            BaseProcMgr::instance()->queueExtraJobPush(&mJob.getLink());
        }
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
                for (auto it = mapLinks.begin(), end = mapLinks.end(); it != end; ++it) {
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

bool LinkTag::prepareForPreDelete() {
    if (!BaseProc::startPreparingForPreDelete_())
        return false;
    if (!mJobFlags)
        return true;

    auto jobLink = &mJob.getLink();
    if (mJobFlags.isBitOn(0)) {
        if (BaseProcMgr::instance()->hasExtraJobLink(jobLink, 0))
            return false;
        mJobFlags.setBitOff(0);
    }

    if (mJobFlags.isBitOn(1)) {
        if (BaseProcMgr::instance()->hasExtraJobLink(jobLink, 1))
            return false;
        mJobFlags.setBitOff(1);
    }
    return true;
}

bool LinkTag::isDonePreparingForPreDelete() {
    if (!mMapObj)
        return true;
    auto linkData = mMapObj->getLinkData();
    if (linkData && mFlags.isOn(LinkTagFlag::_8000)) {
        linkData->x_3(true);
        linkData->printDebugInfo();
    }
    mMapObj->unlinkProc(true);
    mMapObj = nullptr;
    return true;
}

bool LinkTag::hasJobType(JobType jobType) {
    if (jobType != JobType::Calc3)
        return false;
    if (mFlags.isOn(LinkTagFlag::_4000))
        return true;
    if (!mMapObj || mMapObj->getRevivalGameDataFlagHash() == gdt::InvalidHandle)
        return mLinkTagType == Type::Pulse;
    else
        return true;
}

bool LinkTag::shouldSkipJobPush() {
    if (mJobFlags.isBitOn(BaseProcMgr::instance()->getCurrentExtraJobArrayIdx()))
        return true;

    if (mFlags.isOn(LinkTagFlag::_1000))
        return false;
    else
        return mFlags.isOff(LinkTagFlag::_2000);
}

bool LinkTag::isSpecialJobType() {
    return false;
}

void LinkTag::queueExtraJobPush(JobType jobType, u32 jobFlagBit) {
    if (jobType == JobType::Calc3) {
        mJobFlags.setBitOff(1 ^ jobFlagBit);
        s8 extraJobArrayId = BaseProcMgr::instance()->getCurrentExtraJobArrayIdx();
        if (!isDeletedOrDeleting() && mJobFlags.setBitOn(extraJobArrayId)) {
            BaseProcMgr::instance()->queueExtraJobPush(&mJob.getLink());
        }
    }
}

bool LinkTag::canWakeUp() {
    if (mMapObj && mMapObj->getLinkData()) {
        auto linkData = mMapObj->getLinkData();
        if (mFlags.isOff(LinkTagFlag::_8000)) {
            mFlags.set(LinkTagFlag::_8000);
            linkData->x_8(true);
            linkData->x_9();
        }
        if (!linkData->x_7(true))
            return false;
    }
    if (mMapObj && mMapObj->getLinkData()) {
        if (mMapObj->getLinkData()->findLinkWithType(map::MapLinkDefType::MtxCopyCreate))
            mFlags.set(LinkTagFlag::_2);
    }

    return true;
}

void LinkTag::prePushJob2() {
    if (MCMgr::instance()) {
        if (_1dd == MCMgr::instance()->mCalcJobCounterMaybe) {
            mFlags.set(LinkTagFlag::_1000);  // Here
        } else if (mMapObj) {
            bool a1 = false;
            if (isFlagSet(&a1, 1, mMapObj)) {
                if (mFlags.isOn(LinkTagFlag::_8) != a1) {
                    mFlags.set(
                        LinkTagFlag::_1000);  // duplicate usage with above that gets removed in ASM
                }
            }
        }
    }
    _1dd.storeNonAtomic(0xff);
}

/*void LinkTag::calcOther(bool update){
    if(update)
        _1E3 = 0;

    bool flagIsSet = false;
    if(isFlagSet(&flagIsSet, 1, mMapObj) && flagIsSet != mFlags.isOn(LinkTagFlag::_8)){
        updateIsFlagSetFlag(flagIsSet, 0, update);
        if(mMapObj){
            auto* linkData = mMapObj->getLinkData();
            if(linkData){
                for(auto& link : linkData->mLinksOther.links){
                    ksys::act::ActorLinkConstDataAccess accessor{};
                    link.getObjectProcWithAccessor(accessor);
                    triggerLink(accessor);
                }
            }
            goto LABEL_111;
        }
        goto end;
    }
    else {
        if(mMapObj){
            auto* linkData = mMapObj->getLinkData();
            if(linkData){
                if(linkData->mLinksToSelf.links.size()){
                    switch(mLinkTagType){
                        case Type::And:
                        case Type::NAnd:

                    }
                }
            }
        }
    }
}*/

inline void setBitAfterCheck(sead::LongBitFlag<96>* mTriggeredLinkFlags, s8 linkIdx) {
    if (linkIdx < 0x60)
        mTriggeredLinkFlags->setBit(linkIdx);
}
inline void resetBitAfterCheck(sead::LongBitFlag<96>* mTriggeredLinkFlags, s8 linkIdx) {
    if (linkIdx < 0x60)
        mTriggeredLinkFlags->resetBit(linkIdx);
}

bool LinkTag::isTriggered(map::ObjectLink* link, u8 linkIdx) {
    auto* otherObj = link->other_obj;
    if (!otherObj)
        return mTriggeredLinkFlags.isOnBit(linkIdx);

    Actor* actor = otherObj->getActor();
    if (actor && (u8(actor->getState()) | 2) != 3) {  // some weirdness with " | 2"
        if (!sead::IsDerivedFrom<LinkTag>(actor)) {
            if (!sead::IsDerivedFrom<Actor>(actor)) {
                resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
            } else if (actor->mEmittedSignalType == link->type)
                resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
            else
                setBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
        } else if ((actor->TEMP_0x17c[0x38] & 0x40) != 0) {
            if (((actor->TEMP_0x17c[0x38] >> 5) & 1) ==
                ((actor->TEMP_0x17c[0x38] & 4) >> 2))  // probably checking for two flags?
                resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
            setBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
        } else if (link->type != map::MapLinkDefType::BasicSigOnOnly) {
            if (((actor->TEMP_0x17c[0x38] >> 3) & 1) ==
                ((actor->TEMP_0x17c[0x38] & 4) >> 2))  // probably checking for two flags?
                resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
            setBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
        } else if ((actor->TEMP_0x17c[0x38] & 0x400) != 0) {
            setBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
        } else {
            resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
        }
    } else {
        if (link->type <= map::MapLinkDefType::DeadUp) {
            if (otherObj->getFlags0().isOn(map::Object::Flag0::_100000) ||
                otherObj->checkRevivalFlag(map::ActorData::Flag::RevivalEnable)) {
                if (linkIdx >= 0x60)
                    mTriggeredLinkFlags.resetBit(linkIdx);
            }
        }
    }
    if (mFlags.isOn(LinkTagFlag::_2) && otherObj->getFlags().isOff(map::Object::Flag::IsLinkTag))
        _1df = linkIdx;
    return mTriggeredLinkFlags.isOnBit(linkIdx);
}

}  // namespace ksys::act
