#include "KingSystem/Map/mapPlacementMap.h"
#include <prim/seadScopedLock.h>
#include <thread/seadReadWriteLock.h>
#include "Game/DLC/aocManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompound.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundRigidBodyGroup.h"
#include "KingSystem/Resource/resLoadRequest.h"

namespace ksys::map {

PlacementMap::PlacementMap() {
    mInitStatus = InitStatus::None;
    mParsedNumStaticObjs = 0xFFFFFFFF;
    mStaticMapLoaded = false;
    mStaticMapParsed = false;
    mNumStaticObjs = 0xFFFFFFFF;
    mMat = sead::Matrix34f::ident;
    mDistanceToCurrentMapUnit = 0;
    _0 = 0;
    mSkipLoadStaticMap = 0;
    _38c = 0xFFFFFFFF;
    mIdx = 0;
    _388 = 0;
    mCol = 0;
    mRow = 0;
    mNumRoutes = 0;
    mP18 = 0;
    mMgr = 0;
    mPa = 0;
    mDynamicGroupIdx = 0xFFFFFFFF;
    mRes[0].mStatus = HkscRes::Status::_0;
    mRes[1].mStatus = HkscRes::Status::_0;
    mRes[2].mStatus = HkscRes::Status::_0;
    mRes[3].mStatus = HkscRes::Status::_0;
}

PlacementMap::~PlacementMap() {
    mRoutes.freeBuffer();
    for (auto& resource : mRes) {
        resource.cleanup();
    }
}
bool PlacementMap::clearStaticCompoundActorId(int idx) {
    const auto lock = sead::makeScopedLock(mCs);
    const auto& resource = mRes[idx].mRes.getResource();
    if (auto* sc = sead::DynamicCast<phys::StaticCompound>(resource)) {
        if (sc->isAnyRigidBodyAddedToWorld()) {
            return false;
        }
        mRes[idx].mRes.requestUnload();
    }

    for (int i = mParsedNumStaticObjs; i <= mNumStaticObjs; i++) {
        auto* obj = mPa->getStaticObj_2(i);
        if (getStaticCompoundIdFromPosition(*obj) == idx) {
            obj->setStaticCompoundActorId(-1);
        }
    }

    int gid = mDynamicGroupIdx;
    if (gid >= 0) {
        int num_objs = mPa->getNumObjs(gid);
        for (int i = 0; i < num_objs; i++) {
            auto* obj = mPa->getObj(gid, i);
            if (getStaticCompoundIdFromPosition(*obj) == idx) {
                obj->setStaticCompoundActorId(-1);
            }
        }
    }
    return true;
}

void PlacementMap::updateObjectCollisionAndId(int index, Object* obj) {
    if (PlacementMgr::instance()->auto17(obj)) {
        return;
    }
    if (getStaticCompoundIdFromPosition(*obj) != index) {
        return;
    }
    auto& rsrc = mRes[index];
    obj->setStaticCompoundActorId(-1);

    const auto lock = sead::makeScopedLock(mCs);

    auto* sc = sead::DynamicCast<phys::StaticCompound>(rsrc.mRes.getResource());
    if (!sc) {
        return;
    }
    u32 hash_id = obj->getHashId();
    int srt_hash = 0;
    obj->getMubinIter().tryGetParamIntByKey(&srt_hash, "SRTHash");
    int idx = sc->setMapObject(hash_id, static_cast<u32>(srt_hash), obj);
    obj->setStaticCompoundActorId(idx);
    if (obj->getStaticCompoundActorId() < 0) {
        return;
    }
    bool enabled = false;
    if (obj->shouldSkipSpawn() ||
        (obj->checkActorDataFlag(mPa, map::ActorData::Flag::MapConstPassive) &&
         obj->getFlags0().isOn(Object::Flag0::_800))) {
        obj->resetFlags0(Object::Flag0::StaticCompoundInstanceEnabled);
        enabled = false;
    } else {
        obj->setFlags0(Object::Flag0::StaticCompoundInstanceEnabled);
        enabled = true;
    }
    sc->setInstanceEnabled(idx, enabled);
}

bool PlacementMap::parseStaticMap_(sead::Heap* heap, u8* data) {
    if (!mMubinPath.isEmpty()) {
        if (!mSkipLoadStaticMap) {
            parseMap_(heap, data, 0, mIdx);
        }
        mStaticMapLoaded = true;
        mStaticMapParsed = false;
        return true;
    }
    mStaticMapLoaded = true;
    return false;
}
int PlacementMap::getStaticCompoundIdFromPosition(const Object& object) const {
    if (mMgr->isShrineOrDivineBeast()) {
        return 0;
    }
    return getStaticCompoundIdFromPosition(object.getTranslate().x, object.getTranslate().z);
}
int PlacementMap::getStaticCompoundIdFromPosition(float x, float z) const {
    if (mMgr->isShrineOrDivineBeast()) {
        return 0;
    }
    return getStaticCompoundIdFromPosition(sead::Vector3f(x, 0, z));
}
int PlacementMap::getStaticCompoundIdFromPosition(const sead::Vector3f& pos) const {
    if (mMgr->isShrineOrDivineBeast()) {
        return 0;
    }
    float dx = (pos.x - (1000 * mCol - 5000));
    float dz = (pos.z - (1000 * mRow - 4000));
    return (2 * (dz > 500.0f)) + (dx > 500.0f);
}

bool PlacementMap::isDynamicLoaded(const sead::Vector3f& pos) {
    int idx = getStaticCompoundIdFromPosition(pos);
    return mRes[idx].mStatus == HkscRes::Status::_3;  // Likely InitStatus::DynamicLoaded
}

bool PlacementMap::x_6() {
    if (mDynamicGroupIdx < 0) {
        return true;
    }
    bool ret = true;
    int num_objs = mPa->getNumObjs(mDynamicGroupIdx);

    for (int i = 0; i < num_objs; i++) {
        Object* obj = mPa->getObj(mDynamicGroupIdx, i);
        obj->setFlags0(Object::Flag0::_4000);

        const auto& flags = obj->getFlags0();
        if (flags.isOn(Object::Flag0::_2) || flags.isOn(Object::Flag0::_4)) {
            ret &= flags.isOn(Object::Flag0::_80);
        }
        if (flags.isOn(Object::Flag0::_10000) || flags.isOn(Object::Flag0::_80000000)) {
            ret = false;
        }
    }

    return ret;
}

bool PlacementMap::loadDynamicMap() {
    if (mDynamicGroupIdx >= 0) {
        return true;
    }

    sead::ReadWriteLock* lock = &mPa->mLock;
    lock->writeLock();
    mDynamicGroupIdx = mPa->allocGroupForDynamicMap(this);
    lock->writeUnlock();

    if (mDynamicGroupIdx < 0) {
        return false;
    }

    res::LoadRequest arg;
    arg.mRequester = "PlacementMap";
    arg._22 = 1;

    sead::FixedSafeString<128> path;

    int path_len = mMubinPath.findIndex(".");
    path.copy(mMubinPath, path_len);
    if (act::ActorDebug::instance() &&
        (act::ActorDebug::instance()->hasFlag(act::ActorDebug::Flag::_10000000))) {
        path.append("_DynamicPast.mubin");
    } else if (Patrol::instance() && Patrol::instance()->mLoadStaticPhysUnstableMapUnit) {
        path.append("_Dynamic_PhysUnstable.mubin");
    } else if (PlacementMgr::instance()->isGrudgeMerge() || mMgr->isShrineOrDivineBeast()) {
        path.append("_Dynamic.mubin");
    } else {
        path.append("_Dynamic_NoGrudgeMerge.mubin");
    }
    if (uking::aoc::Manager::instance()) {
        arg.mAocFileDevice = uking::aoc::Manager::instance()->getFileDeviceForMapFile(path);
    }
    return mDynamicMubinRes.requestLoad(path, &arg, 0);
}

// Objects: Static and Dynamic
PlacementMap::MapObjStatus PlacementMap::x_2(int hksc_idx) {
    res::Handle* handle = &mRes[hksc_idx].mRes;
    if (!handle->isReadyOrNeedsParse()) {
        return MapObjStatus::NotReady;
    }
    handle->parseResource(nullptr);
    if (handle->checkLoadStatus()) {
        return MapObjStatus::Ready;
    }

    auto* resource = handle->getResource();
    auto* sc = sead::DynamicCast<phys::StaticCompound>(resource);

    sc->applyExtraTransforms(mMat);
    for (int i = mParsedNumStaticObjs; i <= mNumStaticObjs; i++) {
        updateObjectCollisionAndId(hksc_idx, mPa->getStaticObj_0(i));
    }
    const int gid = mDynamicGroupIdx;
    if (gid >= 0) {
        int n = mPa->getNumObjs(gid);
        for (int i = 0; i < n; i++) {
            updateObjectCollisionAndId(hksc_idx, mPa->getObj(gid, i));
        }
    }
    return MapObjStatus::Loading;
}

void PlacementMap::setStaticCompoundInstanceEnabled(Object* obj, bool enabled) {
    if (obj->getStaticCompoundActorId() < 0) {
        return;
    }
    const auto lock = sead::makeScopedLock(mCs);

    if (enabled == obj->getFlags0().isOn(Object::Flag0::StaticCompoundInstanceEnabled)) {
        return;
    }
    if (enabled) {
        obj->setFlags0(Object::Flag0::StaticCompoundInstanceEnabled);
    } else {
        obj->resetFlags0(Object::Flag0::StaticCompoundInstanceEnabled);
    }

    int idx = getStaticCompoundIdFromPosition(obj->getTranslate());
    auto* resource = mRes[idx].mRes.getResource();
    if (auto* sc = sead::DynamicCast<ksys::phys::StaticCompound>(resource)) {
        s16 sc_id = obj->getStaticCompoundActorId();
        sc->setInstanceEnabled(sc_id, enabled);
    }
}

// Should this be renamed to what x_3() and/or x_4() does
int PlacementMap::doSomethingStaticCompound(int hksc_idx) {
    auto* resource = mRes[hksc_idx].mRes.getResource();
    if (auto* sc = sead::DynamicCast<phys::StaticCompound>(resource)) {
        if (!sc->isAnyRigidBodyAddedToWorld() && !sc->isAnyRigidBodyAddedOrBeingAddedToWorld()) {
            sc->addToWorld();
        }
    }
    return 1;
}
bool PlacementMap::loadStaticCompound(int hksc_idx, bool auto_gen_mu, bool req_arg_8) {
    sead::FixedSafeString<0x100> path;
    res::LoadRequest arg;

    arg.mRequester = "PlacementMgr";
    arg._8 = req_arg_8;
    arg._22 = 1;

    const auto lock = sead::makeScopedLock(mCs);

    if (auto_gen_mu) {
        path.format("Physics/StaticCompoundForAutoGenMU/%s-%d.hksc", mFolderAndFile.cstr(),
                    hksc_idx);
    } else {
        if (mMgr->isShrineOrDivineBeast()) {
            path.format("Physics/StaticCompound/%d.hksc", mFolderAndFile.cstr());
        } else {
            path.format("Physics/StaticCompound/%s-%d.hksc", mFolderAndFile.cstr(), hksc_idx);
        }
    }
    if (uking::aoc::Manager::instance()) {
        arg.mAocFileDevice = uking::aoc::Manager::instance()->getFileDeviceForStaticCompound(path);
    }

    return mRes[hksc_idx].mRes.requestLoad(path, &arg, 0);
}

// Should this be cleanupStaticCompound, unloadStaticCompound
void PlacementMap::cleanupPhysics() {
    const auto lock = sead::makeScopedLock(mCs);

    for (int i = 0; i < 4; i++) {
        auto resource = mRes[i].mRes.getResource();
        if (auto* sc = sead::DynamicCast<phys::StaticCompound>(resource)) {
            sc->removeFromWorldImmediately();
        }
        mRes[i].mRes.requestUnload2();
        mRes[i].mStatus = HkscRes::Status::_0;
    }
    mInitStatus = InitStatus::StaticLoaded;
}

PlacementMap::MapObjStatus PlacementMap::parseDynamicMap() {
    if (!mDynamicMubinRes.isReadyOrNeedsParse()) {
        return MapObjStatus::NotReady;
    }
    mDynamicMubinRes.parseResource(nullptr);
    if (mDynamicMubinRes.checkLoadStatus()) {
        sead::ReadWriteLock* lock = &mPa->mLock;
        lock->writeLock();
        mPa->resetGroup(mDynamicGroupIdx);
        mDynamicGroupIdx = 0xFFFFFFFF;
        lock->writeUnlock();
        return MapObjStatus::Ready;
    }
    auto* r = mDynamicMubinRes.getResource();
    auto* resource = sead::DynamicCast<sead::DirectResource>(r);

    sead::ReadWriteLock* lock = &mPa->mLock;
    lock->writeLock();
    parseMap_(0, resource->getRawData(), mDynamicGroupIdx, mIdx);
    lock->writeUnlock();
    return MapObjStatus::Loading;
}

bool PlacementMap::loadStaticMap_(bool load) {
    if (!mMubinPath.isEmpty()) {
        mStaticMapParsed = true;
        if (!mSkipLoadStaticMap) {
            doLoadStaticMap_(load);
        }
    }
    return true;
}

void PlacementMap::unload() {
    sead::ReadWriteLock* rw_lock = &mPa->mLock;
    rw_lock->writeLock();
    mPa->resetGroup(mDynamicGroupIdx);
    mDynamicGroupIdx = 0xFFFFFFFF;
    rw_lock->writeUnlock();

    const auto lock = sead::makeScopedLock(mCs);
    mDynamicMubinRes.requestUnload();
}

phys::StaticCompoundRigidBodyGroup* PlacementMap::getFieldBodyGroup(int field_group_idx) {
    const auto lock = sead::makeScopedLock(mCs);

    auto* r = mRes[0].mRes.getResource();
    if (auto* sc = sead::DynamicCast<phys::StaticCompound>(r)) {
        if (field_group_idx < sc->getNumFieldBodyGroups()) {
            return sc->getFieldBodyGroup(field_group_idx);
        }
    }
    return nullptr;
}

void PlacementMap::x_7(int idx, int unknown, s8 column, s8 row, const sead::SafeString& mubin_path,
                       const sead::SafeString& folder_and_file, int map_id_maybe,
                       bool skip_load_static_map) {
    _388 = unknown;
    mIdx = idx;
    mCol = column;
    mRow = row;
    mMubinPath.copy(mubin_path);
    mFolderAndFile.copy(folder_and_file);
    _38c = map_id_maybe;  // Index in open world map
    mSkipLoadStaticMap = skip_load_static_map;
}

void PlacementMap::unloadHksc(int hksc_idx) {
    mRes[hksc_idx].mRes.requestUnload();
}

void PlacementMap::HkscRes::cleanup() {
    auto* r = mRes.getResource();
    if (auto sc = sead::DynamicCast<phys::StaticCompound>(r)) {
        if (sc->isAnyRigidBodyAddedToWorld()) {
            sc->removeFromWorldImmediately();
        }
    }
}

}  // namespace ksys::map
