
#include "KingSystem/Map/mapPlacementMap.h"
#include <prim/seadScopedLock.h>
#include <thread/seadReadWriteLock.h>
#include "Game/DLC/aocManager.h"
#include "KingSystem/Map/mapObject.h"
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
    for (auto& r : mRes) {
        r.cleanup();
    }
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

bool PlacementMap::isDynamicLoaded(const sead::Vector3f& pos) {
    int k = 0;
    if (mMgr->isShrineOrDivineBeast()) {
        k = 0;
    } else {
        float dx = (float)(pos.x - (float)(1000 * mCol - 5000));
        float dz = (float)(pos.z - (float)(1000 * mRow - 4000));
        k = (2 * (dz > 500.0)) | (dx > 500.0);
    }
    return mRes[k].mStatus == HkscRes::Status::_3;  // Likely InitStatus::DynamicLoaded
}

bool PlacementMap::x_6() {
    if (mDynamicGroupIdx < 0) {
        return true;
    }
    bool ret = true;
    s32 nobjs = mPa->getNumObjs(mDynamicGroupIdx);
    for (int i = 0; i < nobjs; i++) {
        Object* obj = mPa->getObj(mDynamicGroupIdx, i);
        obj->setFlags0(Object::Flag0::_4000);

        auto& f = obj->getFlags0();
        if (f.isOn(Object::Flag0::_2) || f.isOn(Object::Flag0::_4)) {
            ret &= f.isOn(Object::Flag0::_80);
        }
        if (f.isOn(Object::Flag0::_10000) || f.isOn(Object::Flag0::_80000000)) {
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

    ksys::res::LoadRequest arg;
    arg.mRequester = "PlacementMap";
    arg._22 = 1;

    sead::FixedSafeString<128> path;

    s32 path_len = mMubinPath.findIndex(".");
    path.copy(mMubinPath, path_len);
    if (act::ActorDebug::instance() &&
        (act::ActorDebug::instance()->hasFlag(act::ActorDebug::Flag::_10000000))) {
        path.append("_DynamicPast.mubin");
    } else if (Patrol::instance() && (Patrol::instance()->loadStaticPhysUnstableMapUnit)) {
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
int PlacementMap::x_2(int hksc_idx) {
    res::Handle* h = &mRes[hksc_idx].mRes;
    if (!h->isReadyOrNeedsParse()) {
        return 2;
    }
    h->parseResource(0);
    if (h->checkLoadStatus()) {
        return 1;
    }
    phys::StaticCompound* sc = nullptr;
    auto r = h->getResource();
    if (auto dr = sead::DynamicCast<phys::StaticCompound>(r)) {
        sc = dr;
    }

    sc->sub_7100FCAD0C(mMat);
    int i = mParsedNumStaticObjs;
    if (i <= mNumStaticObjs) {
        do {
            x(hksc_idx, mPa->getStaticObj_0(i));
        } while (i++ < mNumStaticObjs);
    }
    int gid = mDynamicGroupIdx;
    if (gid >= 0) {
        int n = mPa->getNumObjs(gid);
        i = 0;
        for (i = 0; i < n; i++) {
            x(hksc_idx, mPa->getObj(gid, i));
        }
    }
    return 0;
}

void PlacementMap::doDisableObjStaticCompound(Object* obj, bool disable) {
    if ((s16)obj->getStaticCompoundId() >= 0) {
        const auto lock = sead::makeScopedLock(mCs);

        // Is Flag0::_200000 a flag to disable an object?
        if ((disable ^ obj->getFlags0().isOn(Object::Flag0::_200000)) != 0) {
            if (disable) {
                obj->setFlags0(Object::Flag0::_200000);
            } else {
                obj->resetFlags0(Object::Flag0::_200000);
            }

            s32 k = 0;
            if (mMgr->isShrineOrDivineBeast()) {
                k = 0;
            } else {
                float dx = (float)(obj->getTranslate().x - (float)(1000 * mCol - 5000));
                float dz = (float)(obj->getTranslate().z - (float)(1000 * mRow - 4000));
                k = (2 * (dz > 500.0)) | (dx > 500.0);
            }
            auto* r = mRes[k].mRes.getResource();
            if (auto ptr = sead::DynamicCast<ksys::phys::StaticCompound>(r)) {
                s16 sc = obj->getStaticCompoundId();
                ptr->disableCollision(sc, disable);
            }
        }
    }
}

// Should this be renamed to what x_3() and/or x_4() does
int PlacementMap::doSomethingStaticCompound(int hksc_idx) {
    auto* r = mRes[hksc_idx].mRes.getResource();
    if (phys::StaticCompound* sc = sead::DynamicCast<phys::StaticCompound>(r)) {
        if (!sc->calledFromMapDtor() && !sc->x_3()) {
            sc->x_4();
        }
    }
    return 1;
}
bool PlacementMap::loadStaticCompound(int hksc_idx, bool auto_gen_mu, bool req_arg_8) {
    sead::FixedSafeString<0x100> path;
    ksys::res::LoadRequest arg;

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
        auto r = mRes[i].mRes.getResource();
        if (auto* sc = sead::DynamicCast<phys::StaticCompound>(r)) {
            sc->cleanUp();
        }
        mRes[i].mRes.requestUnload2();
        mRes[i].mStatus = HkscRes::Status::_0;
    }
    mInitStatus = InitStatus::StaticLoaded;
}

s32 PlacementMap::parseDynamicMap() {
    if (!mDynamicMubinRes.isReadyOrNeedsParse()) {
        return 2;
    }
    mDynamicMubinRes.parseResource(0);
    if (mDynamicMubinRes.checkLoadStatus()) {
        sead::ReadWriteLock* lock = &mPa->mLock;
        lock->writeLock();
        mPa->resetGroup(mDynamicGroupIdx);
        mDynamicGroupIdx = 0xFFFFFFFF;
        lock->writeUnlock();
        return 1;
    }
    auto* r = mDynamicMubinRes.getResource();
    sead::DirectResource* resource = nullptr;
    if (auto* res = sead::DynamicCast<sead::DirectResource>(r)) {
        resource = res;
    }
    sead::ReadWriteLock* lock = &mPa->mLock;
    lock->writeLock();
    parseMap_(0, resource->getRawData(), mDynamicGroupIdx, mIdx);
    lock->writeUnlock();
    return 0;
}

int PlacementMap::loadStaticMap_(bool load) {
    if (!mMubinPath.isEmpty()) {
        mStaticMapParsed = true;
        if (!mSkipLoadStaticMap) {
            doLoadStaticMap_(load);
        }
    }
    return 1;
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

phys::BodyGroup* PlacementMap::getFieldBodyGroup(int field_group_idx) {
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

}  // namespace ksys::map
