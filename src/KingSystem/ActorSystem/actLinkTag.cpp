#include "KingSystem/ActorSystem/actLinkTag.h"

#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"
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

    bool noChangeSignalValue = false;
    if (mMubinIter.tryGetParamBoolByKey(&noChangeSignalValue, "NoChangeSignal")) {
        if (noChangeSignalValue)
            mFlags.set(LinkTagFlag::_40);
    }

    int saveFlagOnOffTypeValue = 0;
    if (mMubinIter.tryGetParamIntByKey(&saveFlagOnOffTypeValue, "SaveFlagOnOffType")) {
        if (saveFlagOnOffTypeValue == 2)
            mFlags.set(LinkTagFlag::_200);
        else if (saveFlagOnOffTypeValue == 1)
            mFlags.set(LinkTagFlag::_100);
    }

    bool flagSet = false;
    isFlagSet(&flagSet, 0, mMapObj);
    updateIsFlagSetFlag(flagSet, true, true);
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
        s32 currentCounter = SystemTimers::instance() ? SystemTimers::instance()->mFrameCounter : 0;
        s32 oldCounter = mCounter;
        mCounter = currentCounter;

        switch (mLinkTagType) {
        case Type::Count:
            calcCount(mCounter != oldCounter);
            break;
        case Type::Pulse:
            calcPulse(mCounter != oldCounter);
            break;
        case Type::None:
            break;
        default:
            calcOther(mCounter != oldCounter);
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
    if (!mMapObj || !mMapObj->getLinkData())
        return 0;
    auto& links = mMapObj->getLinkData()->mLinksToSelf.links;
    s8 linkCount = 0;

    s32 end = std::min(links.size(), 0x60);
    for (s32 i = 0; i < end; i++) {
        auto& link = links[i];
        if (link.type <= map::MapLinkDefType::ChangeAtnSig && isTriggered(&link, i))
            linkCount += 1;
    }
    return linkCount;
}

void LinkTag::calcCount(bool update) {
    if (mFlags.isOff(LinkTagFlag::_1) || !mMapObj)
        return;

    s8 linkCount = getSelfLinkCount();
    mFlags.reset(LinkTagFlag::_10);
    if (linkCount != mTagCount) {
        mTagCount = linkCount;
        gdt::Manager::instance()->setS32ByIdxForLinkTag(linkCount,
                                                        mMapObj->getRevivalGameDataFlagHash());
        updateIsFlagSetFlag(mTagCount > 0, false, update);
    }
}

void LinkTag::calcPulse(bool update) {
    if (mFlags.isOff(LinkTagFlag::_1)) {
        if (mMapObj && mMapObj->getLinkData()) {  // maybe inlined getSelfLinkCount?
            auto& links = mMapObj->getLinkData()->mLinksToSelf.links;
            s32 end = std::min(links.size(), 0x60);
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
    mTagCount = selfLinkCount;

    if (update) {
        if ((mTagCount != oldTagCount) == mFlags.isOn(LinkTagFlag::_8)) {
            something = mFlags.isOn(LinkTagFlag::_80);
            mFlags.reset(LinkTagFlag::_10);
        } else {
            something = true;
            updateIsFlagSetFlag(mTagCount != oldTagCount, false, true);
        }

        if (selfLinkCount != oldTagCount) {
            mFlags.set(LinkTagFlag::_2000);
            if (mMapObj && mMapObj->getLinkData()) {
                for (auto& link : mMapObj->getLinkData()->mLinksOther.links) {
                    if (link.type == map::MapLinkDefType::OffWaitRevival && link.other_obj) {
                        gdt::Manager::instance()->setBoolByHash(
                            false, link.other_obj->getRevivalGameDataFlagHash());
                    }
                }
            }
        } else {
            mFlags.reset(LinkTagFlag::_2000);
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

                s32 end = std::min(links.size(), 0x60);
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
            auto weirdFlag =
                isFlagSet == mMapObj->getFlags().isOn(map::Object::Flag::IsLinkTagNAndOrNOr);
            int frameCounter =
                SystemTimers::instance() ? SystemTimers::instance()->mFrameCounter : 0;

            if (mMapObj->getLinkData()) {
                for (auto& mapLink : mMapObj->getLinkData()->mLinksOther.links) {
                    if (!mapLink.other_obj)
                        continue;

                    switch (mapLink.type) {
                    case map::MapLinkDefType::Create:
                    case map::MapLinkDefType::MtxCopyCreate:
                        if (weirdFlag) {
                            if (mapLink.other_obj->getFlags0().isOff(
                                    map::Object::Flag0::_10000000)) {
                                mapLink.other_obj->getFlags0().set(map::Object::Flag0::_10000000);
                                _1E8 = frameCounter;
                            }
                        } else if (_1E8 == frameCounter) {
                            mapLink.other_obj->getFlags0().reset(map::Object::Flag0::_10000000);
                        }
                        break;
                    case map::MapLinkDefType::Delete:
                        if (!weirdFlag) {
                            if (mapLink.other_obj->getFlags0().isOff(
                                    map::Object::Flag0::_20000000)) {
                                mapLink.other_obj->getFlags0().set(map::Object::Flag0::_20000000);
                                _1E8 = frameCounter;
                            }
                        } else if (_1E8 == frameCounter) {
                            mapLink.other_obj->getFlags0().reset(map::Object::Flag0::_20000000);
                        }
                        break;
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
        mFlags.reset(LinkTagFlag::_800);
        mFlags.reset(LinkTagFlag::_400);
    }

    if (!a3) {
        auto* mapLinkData = mMapObj->getLinkData();
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

BaseProc::PreDeletePrepareResult LinkTag::prepareForPreDelete_() {
    if (!BaseProc::startPreparingForPreDelete_())
        return PreDeletePrepareResult::NotDone;
    if (!mJobFlags)
        return PreDeletePrepareResult::Done;

    auto jobLink = &mJob.getLink();
    if (mJobFlags.isBitOn(0)) {
        if (BaseProcMgr::instance()->hasExtraJobLink(jobLink, 0))
            return PreDeletePrepareResult::NotDone;
        mJobFlags.setBitOff(0);
    }

    if (mJobFlags.isBitOn(1)) {
        if (BaseProcMgr::instance()->hasExtraJobLink(jobLink, 1))
            return PreDeletePrepareResult::NotDone;
        mJobFlags.setBitOff(1);
    }
    return PreDeletePrepareResult::Done;
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

    return true;
}

bool LinkTag::shouldSkipJobPush() {
    if (mJobFlags.isBitOn(BaseProcMgr::instance()->getCurrentExtraJobArrayIdx()))
        return true;

    if (mFlags.isOn(LinkTagFlag::_1000))
        return false;

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
                    mFlags.set(LinkTagFlag::_1000);  // duplicate usage with above that gets
                                                     // removed in ASM
                }
            }
        }
    }
    _1dd.storeNonAtomic(-1);
}

void LinkTag::calcOther(bool update) {
    if (update)
        _1E3 = 0;

    bool flagIsSet = false;
    if (isFlagSet(&flagIsSet, 1, mMapObj) && flagIsSet != mFlags.isOn(LinkTagFlag::_8)) {
        updateIsFlagSetFlag(flagIsSet, 0, update);
        if (mMapObj) {
            auto* linkData = mMapObj->getLinkData();
            if (linkData) {
                for (auto& link : linkData->mLinksOther.links) {
                    ksys::act::ActorLinkConstDataAccess accessor{};
                    link.getObjectProcWithAccessor(accessor);
                    triggerLink(accessor);
                }
            }
        }
        return;
    }

    if (!mMapObj || !mMapObj->getLinkData()) {
        return;
    }
    auto& links = mMapObj->getLinkData()->mLinksToSelf.links;
    if (!links.size()) {
        return;
    }
    bool v35, v36;
    gdt::FlagHandle flagHash;
    bool status = false;
    s32 end;

    switch (mLinkTagType) {
    case Type::And:
    case Type::NAnd:
        status = true;
        end = std::min(links.size(), 0x60);
        for (s32 i = 0; i < end; i++) {
            auto& link = links[i];
            if (link.type <= map::MapLinkDefType::ChangeAtnSig)
                status &= isTriggered(&link, i);
        }
        break;
    case Type::Or:
    case Type::NOr:
        status = false;
        end = std::min(links.size(), 0x60);
        for (s32 i = 0; i < end; i++) {
            auto& link = links[i];
            if (link.type <= map::MapLinkDefType::ChangeAtnSig)
                status |= isTriggered(&link, i);
        }
        break;
    case Type::XOr:
        status = false;
        end = std::min(links.size(), 0x60);
        for (s32 i = 0; i < end; i++) {
            auto& link = links[i];
            if (link.type <= map::MapLinkDefType::ChangeAtnSig) {
                if (mLinkTagType == Type::Or || mLinkTagType == Type::NOr)
                    status |= isTriggered(&link, i);
                else
                    status ^= isTriggered(&link, i);
            }
        }
        break;
    }
    mFlags.change(LinkTagFlag::_10, status);
    if (mMapObj) {
        flagHash = mMapObj->getRevivalGameDataFlagHash();
        v35 = false;
        v36 = mMapObj->getFlags0().isOn(map::Object::Flag0::_2);
    } else {
        flagHash = gdt::InvalidHandle;
        v35 = false;
        v36 = true;
    }

    if (status != mFlags.isOn(LinkTagFlag::_8)) {
        if (_1E3)
            _1E3 = 0;
        else if (v36 || (mFlags.isOn(LinkTagFlag::_100))) {
            status = true;
            if (!v36 && mFlags.isOff(LinkTagFlag::_8)) {
                status = true;
                _1E3 = 1;
            }
        } else {
            status &= mFlags.isOff(LinkTagFlag::_200);
            if (mFlags.isOn(LinkTagFlag::_200) && mFlags.isOn(LinkTagFlag::_8)) {
                status = false;
                _1E3 = 1;
            }
        }
    }

    if (!v35 && mFlags.isOn(LinkTagFlag::_8))
        goto LABEL_105;
    else if (status != mFlags.isOn(LinkTagFlag::_8)) {
        updateIsFlagSetFlag(status, false, update);
        if (flagHash != gdt::InvalidHandle) {
            if (!v36) {
                gdt::Manager::instance()->setBoolByHash(status, flagHash);
                if (BaseProcMgr::instance()->getJobType() == JobType::Calc3) {
                    if (MCMgr::instance() && MCMgr::instance()->mCalcJobCounterMaybe >= 1)
                        BaseProcMgr::instance()->setPushActorJobType3InsteadOf6(true);
                }
                if (mState == State::Calc) {
                    if (mStateFlags.isOff(StateFlags::RequestDelete)) {
                        if (mJobFlags.setBitOn(
                                BaseProcMgr::instance()->getCurrentExtraJobArrayIdx())) {
                            BaseProcMgr::instance()->queueExtraJobPush(&mJob.getLink());
                        }
                    }
                }
                _1dd.storeNonAtomic(MCMgr::instance() ? MCMgr::instance()->mCalcJobCounterMaybe :
                                                        0);
            } else if (status) {
                gdt::Manager::instance()->setS32ByIdxForLinkTag(true, flagHash);
            }
        }
    } else if (!v36 || mFlags.isOn(LinkTagFlag::_10) || mFlags.isOff(LinkTagFlag::_10)) {
    LABEL_105:
        if (mFlags.isOff(LinkTagFlag::_80))
            return;
    } else {
        int value = 0;
        gdt::Manager::instance()->getS32(flagHash, &value);
        gdt::Manager::instance()->setS32ByIdxForLinkTag(value, flagHash);
        return;
    }
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

inline void setBitAfterCheck(sead::LongBitFlag<96>* mTriggeredLinkFlags, u8 linkIdx) {
    if (linkIdx < 0x60)
        mTriggeredLinkFlags->setBit(linkIdx);
}
inline void resetBitAfterCheck(sead::LongBitFlag<96>* mTriggeredLinkFlags, u8 linkIdx) {
    if (linkIdx < 0x60)
        mTriggeredLinkFlags->resetBit(linkIdx);
}

bool LinkTag::isTriggered(map::ObjectLink* link, u8 linkIdx) {
    auto* otherObj = link->other_obj;
    if (!otherObj)
        return mTriggeredLinkFlags.isOnBit(linkIdx);

    BaseProc* baseProc = otherObj->getProc();
    if (baseProc &&
        (baseProc->getState() == State::Calc || baseProc->getState() == State::Delete)) {
        LinkTag* linkTag = sead::DynamicCast<LinkTag>(baseProc);
        if (!linkTag) {
            Actor* actor = sead::DynamicCast<Actor>(baseProc);
            if (!actor) {
                resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
            } else if (actor->getEmittedSignalType() == link->type)
                resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
            else
                setBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
        } else if (linkTag->mFlags.isOn(LinkTagFlag::_40)) {
            if (linkTag->mFlags.isOn(LinkTagFlag::_20) == linkTag->mFlags.isOn(LinkTagFlag::_4))
                resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
            setBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
        } else if (link->type != map::MapLinkDefType::BasicSigOnOnly) {
            if (linkTag->mFlags.isOn(LinkTagFlag::_8) == linkTag->mFlags.isOn(LinkTagFlag::_4))
                resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
            setBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
        } else if (linkTag->mFlags.isOff(LinkTagFlag::_400)) {
            resetBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
        } else {
            setBitAfterCheck(&mTriggeredLinkFlags, linkIdx);
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
