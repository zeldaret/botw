#include "KingSystem/Map/mapRail.h"
#include <heap/seadHeapMgr.h>
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::map {

RailPoint::~RailPoint() = default;

const MubinIter& RailPoint::getIter() const {
    return mIter;
}

const sead::Vector3f& RailPoint::getRotate() const {
    return mSRT.rotate;
}

const sead::Vector3f& RailPoint::getTranslate() const {
    return mSRT.translate;
}

f32 RailPoint::getPrevDistance() const {
    return mPrevDistance;
}

f32 RailPoint::getNextDistance() const {
    return mNextDistance;
}

bool RailPoint::parse(MubinIter* iter, sead::Heap* heap) {
    iter->getScale(&mSRT.scale);
    iter->getRotate(&mSRT.rotate);

    bool success = true;
    success &= iter->tryGetFloatArrayByKey(mSRT.translate.e.data(), "Translate");
    success &= iter->tryGetParamFloatByKey(&mPrevDistance, "PrevDistance");
    success &= iter->tryGetParamFloatByKey(&mNextDistance, "NextDistance");
    iter->tryGetControlPoints(&mCtrlPoints);

    return success;
}

Rail::Rail() = default;

Rail::~Rail() {
    mRailPoints.freeBuffer();
}

void Rail::init(MubinIter* iter, sead::Heap* heap) {
    parse(iter);

    MubinIter result;
    if (iter->tryGetParamIterByKey(&result, "RailPoints")) {
        s32 size = result.getSize();
        mRailPoints.allocBufferAssert(size, heap);
        for (int i = 0; i < size; ++i) {
            MubinIter node_iter;
            if (result.tryGetIterByIndex(&node_iter, i)) {
                RailPoint* point = allocPointIdx(i, heap);
                point->mIter = node_iter;
                point->parse(&node_iter, heap);
            }
        }
    }

    x_38();
}

RailPoint* Rail::allocPointIdx(s32 idx, sead::Heap* heap) {
    mRailPoints[idx] = allocPoint(heap);
    return mRailPoints[idx];
}

s32 Rail::getNumPoints() const {
    return mRailPoints.size();
}

const RailPoint* Rail::getPoint(s32 idx) const {
    if (idx < 0 || idx >= mRailPoints.size())
        return nullptr;
    return mRailPoints[idx];
}

RailPoint* Rail::getPoint(s32 idx) {
    if (idx < 0 || idx >= mRailPoints.size())
        return nullptr;
    return mRailPoints[idx];
}

const SRT& Rail::getPointSRT(s32 idx) const {
    return mRailPoints[idx]->mSRT;
}

const sead::Vector3f& Rail::getPointRotate(s32 idx) const {
    return mRailPoints[idx]->mSRT.rotate;
}

const sead::Vector3f& Rail::getPointTranslate(s32 idx) const {
    return mRailPoints[idx]->mSRT.translate;
}

const sead::Vector3f& Rail::getControlPoint(s32 rail_idx, s32 pt_idx) const {
    return mRailPoints[rail_idx]->mCtrlPoints[pt_idx];
}

sead::Vector3f Rail::calcTranslate(float progress) const {
    sead::Vector3f pos;
    calcTranslateRotate(&pos, nullptr, progress);
    return pos;
}

void Rail::calcTranslate(sead::Vector3f* pos_out, float progress) const {
    calcTranslateRotate(pos_out, nullptr, progress);
}

// NON_MATCHING: the complete body has a different compiler layout.
void Rail::calcTranslateRotate(sead::Vector3f* pos_out, sead::Vector3f* rot_out,
                               float progress) const {
    const int count = mRailPoints.size();
    if (count == 1) {
        *pos_out = mRailPoints[0]->mSRT.translate;
        if (rot_out)
            *rot_out = sead::Vector3f::zero;
        return;
    }

    const auto floorIndex = [](float value) {
        const int integer = static_cast<int>(value);
        return integer - (!(value >= 0.0f) && integer != value);
    };
    const bool closed = isClosed();
    if (closed)
        progress -= float(count) * float(floorIndex(progress / count));
    int index = floorIndex(progress);
    if (!closed && index == count - 1)
        --index;
    const float t = progress - index;
    const RailPoint* start = mRailPoints[index];
    const RailPoint* end = mRailPoints[(index + 1) % count];
    const sead::Vector3f& p0 = start->mSRT.translate;
    const sead::Vector3f& p3 = end->mSRT.translate;
    if (!isBezier()) {
        *pos_out = p0 + (p3 - p0) * t;
        if (rot_out) {
            *rot_out = p3 - p0;
            rot_out->normalize();
        }
        return;
    }

    const sead::Vector3f p1 = p0 + start->mCtrlPoints[1];
    const sead::Vector3f p2 = p3 + end->mCtrlPoints[0];
    const float u = 1.0f - t;
    const float u2 = u * u;
    const float t2 = t * t;
    *pos_out = p0 * (u * u2);
    *pos_out += p1 * (t * u2 * 3.0f);
    *pos_out += p2 * (t2 * u * 3.0f);
    *pos_out += p3 * (t * t2);
    if (!rot_out)
        return;

    const auto nearlyZero = [](const sead::Vector3f& v) {
        return v.x <= 0.01f && v.x >= -0.01f && v.y <= 0.01f && v.y >= -0.01f && v.z <= 0.01f &&
               v.z >= -0.01f;
    };
    if (nearlyZero(start->mCtrlPoints[1]) && t < 0.01f) {
        *rot_out = p3 + end->mCtrlPoints[0];
        *rot_out -= p0;
    } else if (nearlyZero(end->mCtrlPoints[0]) && t > 0.99f) {
        *rot_out = p3 - start->mCtrlPoints[1];
        *rot_out -= p0;
    } else {
        const sead::Vector3f tangent_p1 = p0 + start->mCtrlPoints[1];
        const sead::Vector3f tangent_p2 = p3 + end->mCtrlPoints[0];
        const float threeT = t * 3.0f;
        *rot_out = p0 * (u2 * -3.0f);
        *rot_out += tangent_p1 * (u * 3.0f * (1.0f - threeT));
        *rot_out += tangent_p2 * (threeT * (2.0f - threeT));
        *rot_out += p3 * (t2 * 3.0f);
    }
    rot_out->normalize();
}

bool Rail::isClosed() const {
    return mFlags.isOn(Flag::Closed);
}

bool Rail::isBezier() const {
    return mFlags.isOn(Flag::Bezier);
}

const u32& Rail::getHashId() const {
    return mHashId;
}

const char* Rail::getUniqueName() const {
    return mUniqueName;
}

RailPoint* Rail::allocPoint(sead::Heap* heap) {
    return new (heap) RailPoint;
}

bool Rail::parse(MubinIter* iter) {
    bool success = true;

    success &= iter->tryGetParamUIntByKey(&mHashId, "HashId");
    success &= iter->tryGetParamStringByKey(&mUniqueName, "UniqueName");

    bool closed = false;
    if (!iter->tryGetParamBoolByKey(&closed, "Closed")) {
        success = false;
    } else if (closed) {
        mFlags.set(Flag::Closed);
    } else {
        mFlags.reset(Flag::Closed);
    }

    const char* type = nullptr;
    if (!iter->tryGetParamStringByKey(&type, "RailType")) {
        success = false;
    } else {
        mFlags.change(Flag::Bezier, sead::SafeString(type) == "Bezier");
    }

    return success;
}

bool RailGuidePoint::parse(MubinIter* iter, sead::Heap* heap) {
    bool success = true;
    success &= RailPoint::parse(iter, heap);
    success &= iter->tryGetParamFloatByKey(&mWaitFrame, "WaitFrame");
    return success;
}

RailGuide::RailGuide() = default;

RailGuide::~RailGuide() = default;

bool RailRemainGuidePoint::parse(MubinIter* iter, sead::Heap* heap) {
    bool success = true;
    success &= RailGuidePoint::parse(iter, heap);
    success &= iter->tryGetParamFloatByKey(&mMoveSpeed, "MoveSpeed");
    return success;
}

RailRemainGuide::RailRemainGuide() = default;

RailRemainGuide::~RailRemainGuide() = default;

RailPoint* RailRemainGuide::allocPoint(sead::Heap* heap) {
    return new (heap) RailRemainGuidePoint;
}

RailConnectablePoint::RailConnectablePoint() = default;

RailConnectablePoint::~RailConnectablePoint() {
    sead::HeapMgr::instance()->getCurrentHeap();

    if (mJunctionPoint)
        util::safeDeleteArray(mJunctionPoint);
}

Rail* RailConnectablePoint::getJunctionRail() const {
    return mJunctionRail;
}

RailPoint* RailConnectablePoint::getJunctionPoint() const {
    return mJunctionPoint;
}

bool RailConnectablePoint::parse(MubinIter* iter, sead::Heap* heap) {
    return RailPoint::parse(iter, heap);
}

RailRoutePoint::RailRoutePoint() = default;

RailRoutePoint::~RailRoutePoint() = default;

const char* RailRoutePoint::getCheckPointName() const {
    return mCheckPointName;
}

bool RailRoutePoint::parse(MubinIter* iter, sead::Heap* heap) {
    bool success = true;
    success &= RailConnectablePoint::parse(iter, heap);
    iter->tryGetParamStringByKey(&mEntryPointName, "EntryPointName");
    iter->tryGetParamStringByKey(&mCheckPointName, "CheckPointName");
    return success;
}

RailRoute::RailRoute() {
    mFlags.set(Flag::AutoPlacementEnabled);
    mFlags.set(Flag::EnableHorseTrace);
    mFlags.set(Flag::Walkable);
}

RailRoute::~RailRoute() = default;

bool RailRoute::isRenderEnabled() const {
    return mFlags.isOn(Flag::RenderEnabled);
}

bool RailRoute::isAutoPlacementEnabled() const {
    return mFlags.isOn(Flag::AutoPlacementEnabled);
}

bool RailRoute::isWalkable() const {
    return mFlags.isOn(Flag::Walkable);
}

bool RailRoute::isHorseTraceEnabled() const {
    return mFlags.isOn(Flag::EnableHorseTrace);
}

const char* RailRoute::getRouteId() const {
    return mRouteId;
}

const char* RailRoute::getCheckPointName(s32 idx) const {
    return static_cast<RailRoutePoint*>(mRailPoints[idx])->mCheckPointName;
}

bool RailRoute::parse(MubinIter* iter) {
    int success = Rail::parse(iter);

    bool result = false;
    if (iter->tryGetParamBoolByKey(&result, "RenderEnabled")) {
        if (result) {
            mFlags.set(Flag::RenderEnabled);
        } else {
            mFlags.reset(Flag::RenderEnabled);
        }
    }

    if (iter->tryGetParamBoolByKey(&result, "AutoPlacementEnabled")) {
        if (result) {
            mFlags.set(Flag::AutoPlacementEnabled);
        } else {
            mFlags.reset(Flag::AutoPlacementEnabled);
        }
    } else {
        success = false;
    }

    if (iter->tryGetParamBoolByKey(&result, "IsWalkable")) {
        if (result) {
            mFlags.set(Flag::Walkable);
        } else {
            mFlags.reset(Flag::Walkable);
        }
    } else {
        success = false;
    }

    if (iter->tryGetParamBoolByKey(&result, "IsEnableHorseTrace")) {
        if (result) {
            mFlags.set(Flag::EnableHorseTrace);
        } else {
            mFlags.reset(Flag::EnableHorseTrace);
        }
    }

    success &= iter->tryGetParamStringByKey(&mRouteId, "RouteId");
    return success;
}

}  // namespace ksys::map
