#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Graphics/gfxForestRenderer.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapStagePreActorCache.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::map {

// NON_MATCHING
Object::Object() {
    mHardModeFlags.makeAllZero();
    _b = 0xFF;
    _18 = nullptr;
    _20 = nullptr;
    mProc = nullptr;
    mLinkData = nullptr;
}

Object::~Object() {
    if (mLinkData != nullptr) {
        mLinkData->release(this, true);
        mLinkData = nullptr;
    }
}

void Object::free() {
    mId = 0;
    _10 = nullptr;
    _18 = nullptr;
    _20 = nullptr;

    if (mProc)
        mProc = nullptr;

    mFlags0.reset(Flag0::ResetOnFreed);
    mHardModeFlags.reset(HardModeFlag::ActorCreated);

    if (mFlags0.isOn(Flag0::_80000))
        mFlags0.set(Flag0::_40000);
    else
        mFlags0.set(Flag0::_8);

    if (mLinkData)
        mLinkData->field_57 = 0;
}

// NON_MATCHING
void Object::initData(MubinIter* iter, u8 idx, u32 actor_data_idx, ActorData* data) {
    mActorDataIdx = 0xFFFF;
    mFlags0.makeAllZero();
    mRevivalGameDataFlagHash = gdt::InvalidHandle;
    mId = 0;
    mActorFlags8.makeAllZero();
    mFlags.makeAllZero();
    mIdx = 0;
    mNumLinksPointingToMe = 0;
    mStaticCompoundActorId = -1;
    _18 = nullptr;
    _20 = nullptr;
    _10 = nullptr;
    _50 = nullptr;
    mTraverseDist = 0.0f;
    mTraverseDistInt = 0;
    mHashId = 0;
    mHardModeFlags.makeAllZero();
    _b = 0xFF;
    mProc = nullptr;
    mLinkData = nullptr;
    iter->tryGetFloatArrayByKey(&mTranslate.x, "Translate");
    mMubinIter = *iter;

    u32 hash = 0;
    iter->tryGetParamUIntByKey(&hash, "HashId");
    if (hash == 0)
        hash = 0xFFFFFFFF;
    mHashId = hash;

    mIdx = idx;
    mFlags0.setDirect(Flag0::_8);
    mNumLinksPointingToMe = 0;
    _10 = nullptr;
    _18 = nullptr;
    _20 = nullptr;
    mStaticCompoundActorId = -1;
    mActorDataIdx = actor_data_idx;
    mProc = nullptr;
    mLinkData = nullptr;
    mActorFlags8 = data->mActorFlags8;

    auto* fr = StagePreActorCache::instance()->getForestRenderer();
    if (fr != nullptr) {
        if (fr->x_7(mTranslate) != -1) {
            mFlags0.set(Flag0::_10);
        }
    }
    initRevivalGameDataFlagAndMiscFlags(data, false);
}

act::BaseProc* Object::tryGetProc(bool force) {
    auto* bpm = act::BaseProcMgr::instance();
    if (bpm == nullptr || !bpm->isHighPriorityThread())
        return nullptr;
    if (mProc == nullptr)
        return nullptr;

    act::BaseProc* result = nullptr;
    if (!mProc->isDeleteOrInvalid())
        result = mProc;
    if (mProc->isDeleteOrInvalid() || force)
        return result;

    if (!mProc->isInit())
        bpm->isAccessingProcSafe(mProc, nullptr);
    return mProc;
}

act::Actor* Object::tryGetActor(bool force) {
    auto* proc = tryGetProc(force);
    return sead::DynamicCast<act::Actor>(proc);
}

bool Object::getActorWithAccessor(act::ActorLinkConstDataAccess& accessor) {
    act::BaseProcMgr* instance = act::BaseProcMgr::instance();

    if (instance == nullptr || !instance->isHighPriorityThread() || mProc == nullptr)
        return accessor.acquire(nullptr);

    if (!mProc->isDeleteOrInvalid())
        return accessor.acquire(mProc);

    return accessor.acquire(nullptr);
}

act::Actor* Object::getActor() {
    return sead::DynamicCast<act::Actor>(mProc);
}

void Object::registerBaseProc(act::BaseProc* proc) {
    static const char* sActorStateStrings[4] = {"Init", "Calc", "Sleep", "Delete"};

    if (mProc != nullptr && mProc != proc) {
        sead::FixedSafeString<1000> message;
        message.format("%p   (%s:%p:%s) → (%s:%p:%s) \n", this, mProc->getName().cstr(), mProc,
                       sActorStateStrings[static_cast<s32>(mProc->getState())],
                       proc->getName().cstr(), proc,
                       sActorStateStrings[static_cast<s32>(proc->getState())]);
        util::PrintDebug(message);
    }
    setBaseProcDirect(proc);

    mFlags0.set(Flag0::_80);
    mFlags0.reset(Flag0::_80000000);
    mHardModeFlags.set(HardModeFlag::ActorCreated);
}

void Object::setBaseProcDirect(act::BaseProc* proc) {
    mProc = proc;
}

bool Object::checkActorDataFlag(const PlacementActors* pa, ActorData::Flag flag) const {
    return pa->mActorData[mActorDataIdx].mFlags.isOnBit(flag);
}

bool Object::isEnemyOrNpcOrActiveOrMapPassive() const {
    if (mActorFlags8.isOn(ActorFlag8::EnemyOrNpcOrActiveOrAreaOrAirWall))
        return true;

    auto pa = PlacementMgr::instance()->mPlacementActors;
    if (pa == nullptr)
        return false;

    return !checkActorDataFlag(pa, ActorData::Flag::MapPassiveOrFlag1);
}

bool Object::isNpcOrActiveOrMapPassiveOrFlag1() const {
    auto actFlags = mActorFlags8;
    if (isFlags8Cleared())
        return true;

    auto pa = PlacementMgr::instance()->mPlacementActors;
    if (pa == nullptr)
        return false;

    if (checkActorDataFlag(pa, ActorData::Flag::_16) ||
        actFlags.isOn(ActorFlag8::EnemyOrNpcOrActiveOrAreaOrAirWall))
        return false;

    return checkActorDataFlag(pa, ActorData::Flag::MapPassiveOrFlag1);
}

bool Object::isMapPassive(const PlacementActors* pa) const {
    if (isFlags8Cleared())
        return true;

    if (pa == nullptr)
        return false;

    if (checkActorDataFlag(pa, ActorData::Flag::_16) ||
        mActorFlags8.isOn(ActorFlag8::EnemyOrNpcOrActiveOrAreaOrAirWall))
        return false;

    return checkActorDataFlag(pa, ActorData::Flag::MapPassiveOrFlag1);
}

bool Object::isEnemyOrNpc(const PlacementActors* pa) const {
    return checkActorDataFlag(pa, ActorData::Flag::EnemyOrNpc_DisableFlashback);
}

bool Object::isFlags8Cleared() const {
    return mActorFlags8.isZero();
}

f32 Object::getDispDistance(const ActorData* data, bool get_diameter, u32 unused,
                            bool ignore_radius) const {
    if (data->mFlags.isOnBit(ActorData::Flag::TraverseDistReset))
        return 0.0;

    f32 dist = getTraverseDist(data, get_diameter, unused, ignore_radius);
    f32 mult = getDispDistanceMultiplier();

    if (dist > 0.0)
        return dist * mult;
    else
        return 100.0 * mult;
}

f32 Object::getDispDistance(const PlacementActors* pa, bool get_diameter,
                            bool ignore_radius) const {
    auto* dat = &pa->mActorData[mActorDataIdx];
    return getDispDistance(dat, get_diameter, 0, ignore_radius);
}

f32 Object::getDispDistance(bool get_diameter, bool ignore_radius) const {
    auto pa = PlacementMgr::instance()->mPlacementActors;
    return getDispDistance(pa, get_diameter, ignore_radius);
}

[[gnu::noinline]] f32 Object::getTraverseDist(const ActorData* data, bool get_diameter, u32,
                                              bool ignore_radius) const {
    using DFlag = ActorData::Flag;
    f32 dist = 0.0;

    if (mFlags.isOn(Flag::HasTraversePos) && !ignore_radius) {
        mMubinIter.tryGetParamFloatByKey(&dist, "TraverseRadiusXZ");
        if (get_diameter)
            dist = dist * 2;
    }

    // TODO: inline here?
    if (data->mFlags.isOnBit(DFlag::TraverseDistReset))
        return dist + 0.0;

    if (data->mFlags.isOnBit(DFlag::TraverseDist400) ||
        data->mFlags.isOnBit(DFlag::TraverseDist200) ||
        data->mFlags.isOnBit(DFlag::TraverseDist4000) ||
        data->mFlags.isOnBit(DFlag::TraverseDist800))
        return mTraverseDist + dist;

    if (data->mFlags.isOffBit(DFlag::TraverseDist2000))
        return mTraverseDist + dist;

    return mTraverseDist;
}

f32 Object::getTraverseDistForLOD() const {
    using DFlag = ActorData::Flag;
    auto* data = &PlacementMgr::instance()->mPlacementActors->mActorData[mActorDataIdx];
    f32 dist = 0.0;

    if (data->mFlags.isOnBit(ActorData::Flag::TraverseDistReset))
        return 0.0;
    if (data->mFlags.isOnBit(ActorData::Flag::TraverseDistReset))
        dist = 0.0;
    else if (data->mFlags.isOnBit(DFlag::TraverseDist400) ||
             data->mFlags.isOnBit(DFlag::TraverseDist200) ||
             data->mFlags.isOnBit(DFlag::TraverseDist4000) ||
             data->mFlags.isOnBit(DFlag::TraverseDist800))
        dist = mTraverseDist + 0.0;
    else if (data->mFlags.isOffBit(DFlag::TraverseDist2000))
        dist = mTraverseDist + 0.0;
    else
        dist = mTraverseDist;

    f32 mult = getDispDistanceMultiplier();

    if (dist > 0.0)
        return dist * mult;
    else
        return 100.0 * mult;
}

sead::Vector3f Object::getScale() const {
    sead::Vector3f vec;
    mMubinIter.getScale(&vec);
    return vec;
}

const char* Object::getUnitConfigName() const {
    auto* mgr = PlacementMgr::instance();

    if (mgr != nullptr && mgr->mPlacementActors != nullptr)
        return mgr->mPlacementActors->mActorData[mActorDataIdx].mActorName.cstr();

    return getUnitConfigNameFromByaml();
}

const char* Object::getUnitConfigNameFromByaml() const {
    const char* result;
    if (!mMubinIter.tryGetParamStringByKey(&result, "UnitConfigName"))
        result = "";
    return result;
}

Object* Object::findPlacementLODLinkObject(const PlacementActors*) const {
    if (!mLinkData)
        return nullptr;

    ObjectLink* result = mLinkData->mLinksToSelf.findLinkWithType(MapLinkDefType::PlacementLOD);
    if (result)
        return result->other_obj;
    return nullptr;
}

Object* Object::findPlacementLODLinkObject() const {
    if (!mLinkData)
        return nullptr;

    ObjectLink* result = mLinkData->mLinksToSelf.findLinkWithType_0(MapLinkDefType::PlacementLOD);
    if (result)
        return result->other_obj;
    return nullptr;
}

const char* Object::getHashIdStringDebug() const {
    return getHashIdStringDebug_0();
}

const char* Object::getHashIdStringDebug_0() const {
    act::ActorDebug::HashUnused t;
    const char* terminator;

    if (mMubinIter.tryGetParamUIntByKey(&t.hash, "HashId"))
        terminator = act::ActorDebug::instance()->getNullStr(&t);
    else
        terminator = "";
    return terminator;
}

void Object::unlinkProc(bool force) {
    bool set = false;
    auto flag = Flag0::ResetOnUnlinkFailed;

    if (!tera::checkTeraSystemStatus()) {
        auto* thread = sead::ThreadMgr::instance()->getCurrentThread();
        thread->getPriority();
    }
    static_cast<void>(mFlags0.isZero());

    if (force || mFlags0.isOn(Flag0::ActorCreated))
        set = true;
    else if (checkActorDataFlag(PlacementMgr::instance()->mPlacementActors,
                                ActorData::Flag::RevivalEnable))
        set = isRevivalGameDataFlagOn();

    if (set)
        flag = Flag0::ResetOnUnlink;

    mFlags0.reset(flag);
    mProc = nullptr;
}

bool Object::checkRevivalFlag(ActorData::Flag bit) const {
    if (bit == ActorData::Flag::RevivalEnable || bit == ActorData::Flag::RevivalForUsed ||
        bit == ActorData::Flag::RevivalForDrop) {
        if (getActorData().mFlags.isOffBit(bit))
            return false;
        return isRevivalGameDataFlagOn();
    }
    return false;
}

bool Object::isRevivalGameDataFlagOn() const {
    bool x = false;
    gdt::Manager::instance()->getBool(mRevivalGameDataFlagHash, &x, true);
    return x;
}

void Object::setRevivalFlagValueIf(ActorData::Flag bit, bool value) {
    if (bit == ActorData::Flag::RevivalEnable || bit == ActorData::Flag::RevivalForUsed ||
        bit == ActorData::Flag::RevivalForDrop) {
        if (getActorData().mFlags.isOnBit(bit)) {
            setRevivalFlagValue(value);
        }
    }
}

void Object::setRevivalFlagValue(bool value) {
    gdt::Manager::instance()->setBool(value, mRevivalGameDataFlagHash);
}

// NON_MATCHING
bool Object::x_18() const {
    act::InfoData::InvalidLifeConditions info;
    const char* s;
    auto* id = act::InfoData::instance();

    if (PlacementMgr::instance() != nullptr &&
        PlacementMgr::instance()->mPlacementActors != nullptr)
        s = PlacementMgr::instance()->mPlacementActors->mActorData[mActorDataIdx].mActorName.cstr();
    else
        s = getUnitConfigNameFromByaml();
    id->getInvalidLifeConditions(s, info);

    sead::Vector3f temp = mTranslate;
    return !id->sub_7100D30DF8(info, temp);
}

bool Object::setupTargetLinks(Object* src, ObjectLink* link, sead::Heap* heap) {
    if (mNumLinksPointingToMe == 0)
        return false;

    if (mLinkData == nullptr) {
        mLinkData = new (heap) ObjectLinkData();
        if (mLinkData == nullptr)
            return false;
    }

    if (!mLinkData->mLinksToSelf.links.isBufferReady()) {
        if (!mLinkData->allocLinksToSelf(mNumLinksPointingToMe, heap))
            return false;
    }

    return mLinkData->sub_7100D4EC40(src, link, this);
}

bool Object::checkCreateOrDeleteLinkObjRevival() const {
    if (mLinkData != nullptr)
        return mLinkData->checkCreateOrDeleteLinkObjRevival();
    return false;
}

bool Object::shouldSkipSpawn() const {
    if (checkTraverseFlags() || shouldSkipSpawn_(false))
        return true;
    return checkCreateOrDeleteLinkObjRevival();
}

bool Object::checkTraverseFlags() const {
    return mFlags0.isOn(Flag0::_500400);
}

// NON_MATCHING
bool Object::x_20() const {
    if (getActorData().mFlags.isOffBit(ActorData::Flag::RevivalEnable))
        return false;

    if (mFlags0.isOff(Flag0::_400400))
        return false;

    if (!shouldSkipSpawn_(false)) {
        return checkCreateOrDeleteLinkObjRevival();
    }
    return false;
}

void Object::onBaseProcCreated(act::BaseProc* actor) {
    if (actor != nullptr) {
        registerBaseProc(actor);
        mFlags0.set(Flag0::ActorCreated);
    } else {
        mFlags0.reset(Flag0::_80002106);
    }
}

void Object::spawnGenGroupActorsIfNeeded(Object* obj) {
    if (mLinkData != nullptr)
        mLinkData->sub_7100D4FB78(obj);
}

void Object::setFieldATrue() {
    if (mActorFlags8.isOn(ActorFlag8::MapPassive) || mActorFlags8.isOn(ActorFlag8::_8)) {
        mActorFlags8.reset(ActorFlag8::MapPassive);
        mActorFlags8.reset(ActorFlag8::_8);
        mActorFlags8.set(ActorFlag8::EnemyOrNpcOrActiveOrAreaOrAirWall);
    }
}

void* Object::getRails() const {
    return getRails_0();
}

void* Object::getRails_0() const {
    if (mLinkData == nullptr)
        return nullptr;
    return mLinkData->mRails;
}

bool Object::allocLinkData(sead::Heap* heap) {
    mLinkData = new (heap) ObjectLinkData;
    return mLinkData != nullptr;
}

bool Object::hasGenGroup() const {
    if (!mLinkData)
        return false;
    return mLinkData->mGenGroup != nullptr;
}

void Object::incrementLinkNum() {
    if (mNumLinksPointingToMe != 0xFF) {
        mNumLinksPointingToMe++;
        return;
    }

    if (sead::SafeString(getUnitConfigName()) == "LinkTagNone") {
        // More than 255 actors are specified in one generation group.
        // If it is not a test, consult the programmer.
        printDebugMsg(this,
                      "一つの生成グループに 255 以上のアクタが指定されています。"
                      "テストで無ければプログラマに相談",
                      nullptr);
        return;
    }

    // We have exceeded the expected number of links.
    // If it's not a test, talk to your programmer.
    printDebugMsg(this, "リンクの想定数を越えました。テストで無ければプログラマに相談", nullptr);
}

void Object::decrementLinkNum() {
    if (mNumLinksPointingToMe != 0)
        --mNumLinksPointingToMe;
}

sead::Vector3f Object::getRotate() const {
    sead::Vector3f result;
    mMubinIter.getRotate(&result);
    return result;
}

// NON_MATCHING: Vec3f copy incorrect
void Object::getTraversePosAndLoadDistance(sead::Vector3f* traverse_pos, f32* load_dist) const {
    if (mFlags.isOn(Flag::HasTraversePos))
        mMubinIter.tryGetFloatArrayByKey(&traverse_pos->x, "TraversePos");
    else
        *traverse_pos = mTranslate;
    *load_dist = getLoadDistance(false);
}

void Object::getUniqueName(const char** out) const {
    if (mFlags.isOff(Flag::HasUniqueName) || !mMubinIter.tryGetParamStringByKey(out, "UniqueName"))
        *out = "";
}

void Object::setTranslate(const sead::Vector3f& translate) {
    mTranslate = translate;
}

}  // namespace ksys::map
