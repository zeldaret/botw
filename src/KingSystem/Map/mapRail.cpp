#include "KingSystem/Map/mapRail.h"
#include <heap/seadHeapMgr.h>

namespace ksys::map {

RailPoint::~RailPoint() = default;

const MubinIter* RailPoint::getIter() const {
    return &iter;
}

const sead::Vector3f* RailPoint::getRotate() const {
    return &srt.rotate;
}

const sead::Vector3f* RailPoint::getTranslate() const {
    return &srt.translate;
}

f32 RailPoint::getPrevDistance() const {
    return prev_distance;
}

f32 RailPoint::getNextDistance() const {
    return next_distance;
}

bool RailPoint::parse(MubinIter* iter, sead::Heap* heap) {
    iter->getScale(&srt.scale);
    iter->getRotate(&srt.rotate);

    bool success = true;
    if (!iter->tryGetFloatArrayByKey(srt.translate.e.data(), "Translate")) {
        success = false;
    }

    if (!iter->tryGetParamFloatByKey(&prev_distance, "PrevDistance")) {
        success = false;
    }

    if (!iter->tryGetParamFloatByKey(&next_distance, "NextDistance")) {
        success = false;
    }

    iter->tryGetControlPoints(&ctrl_points);

    return success;
}

RailBase::RailBase() = default;

RailBase::~RailBase() {
    mRailPoints.freeBuffer();
}

void RailBase::init(MubinIter* iter, sead::Heap* heap) {
    parse(iter);

    MubinIter result;
    if (iter->tryGetParamIterByKey(&result, "RailPoints")) {
        s32 size = result.getSize();
        mRailPoints.allocBufferAssert(size, heap);
        for (int i = 0; i < size; ++i) {
            MubinIter node_iter;
            if (result.tryGetIterByIndex(&node_iter, i)) {
                auto* n = [&] {
                    mRailPoints[i] = allocRail(heap);
                    return mRailPoints[i];
                }();

                n->iter = node_iter;
                n->parse(&node_iter, heap);
            }
        }
    }

    x_38();
}

s32 RailBase::getSize() const {
    return mRailPoints.size();
}

RailPoint* RailBase::getPoint(s32 idx) const {
    if (idx < 0 || idx >= mRailPoints.size())
        return nullptr;
    return mRailPoints[idx];
}

RailPoint* RailBase::getPoint_0(s32 idx) const {
    return getPoint(idx);
}

SRT* RailBase::getPointSRT(s32 idx) const {
    return &mRailPoints[idx]->srt;
}

sead::Vector3f* RailBase::getPointRotate(s32 idx) const {
    return &mRailPoints[idx]->srt.rotate;
}

sead::Vector3f* RailBase::getPointTranslate(s32 idx) const {
    return &mRailPoints[idx]->srt.translate;
}

sead::Vector3f* RailBase::getControlPoint(s32 rail_idx, s32 pt_idx) const {
    return &mRailPoints[rail_idx]->ctrl_points[pt_idx];
}

sead::Vector3f RailBase::calcTranslate(float progress) const {
    sead::Vector3f pos;
    calcTranslateRotate(&pos, nullptr, progress);
    return pos;
}

void RailBase::calcTranslate(sead::Vector3f* pos_out, float progress) const {
    calcTranslateRotate(pos_out, nullptr, progress);
}

bool RailBase::isClosed() const {
    return mFlags.isOn(Flag::Closed);
}

bool RailBase::isBezier() const {
    return mFlags.isOn(Flag::Bezier);
}

const u32& RailBase::getHashId() const {
    return mHashId;
}

const char* RailBase::getUniqueName() const {
    return mUniqueName;
}

RailPoint* RailBase::allocRail(sead::Heap* heap) {
    RailPoint* rail = new (heap) RailPoint;

    rail->srt.scale = sead::Vector3f::ones;
    rail->srt.rotate = sead::Vector3f::zero;
    rail->srt.translate = sead::Vector3f::zero;
    rail->ctrl_points[0] = sead::Vector3f::zero;
    rail->ctrl_points[1] = sead::Vector3f::zero;

    rail->prev_distance = 0.0;
    rail->next_distance = 0.0;

    return rail;
}

bool RailBase::parse(MubinIter* iter) {
    bool success = true;

    if (!iter->tryGetParamUIntByKey(&mHashId, "HashId")) {
        success = false;
    }

    if (!iter->tryGetParamStringByKey(&mUniqueName, "UniqueName")) {
        success = false;
    }

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
    iter->getScale(&srt.scale);
    iter->getRotate(&srt.rotate);

    bool success = true;
    if (!iter->tryGetFloatArrayByKey(srt.translate.e.data(), "Translate")) {
        success = false;
    }

    if (!iter->tryGetParamFloatByKey(&prev_distance, "PrevDistance")) {
        success = false;
    }

    if (!iter->tryGetParamFloatByKey(&next_distance, "NextDistance")) {
        success = false;
    }

    iter->tryGetControlPoints(&ctrl_points);

    if (!iter->tryGetParamFloatByKey(&wait_frame, "WaitFrame")) {
        success = false;
    }

    return success;
}

RailGuide::RailGuide() = default;

RailGuide::~RailGuide() = default;

bool RailRemainGuidePoint::parse(MubinIter* iter, sead::Heap* heap) {
    bool success = true;

    if (!RailPoint::parse(iter, heap)) {
        success = false;
    }

    if (!iter->tryGetParamFloatByKey(&mMoveSpeed, "MoveSpeed")) {
        success = false;
    }

    return success;
}

RailRemainGuide::RailRemainGuide() = default;

RailRemainGuide::~RailRemainGuide() = default;

RailPoint* RailRemainGuide::allocRail(sead::Heap* heap) {
    auto* rail = new (heap) RailRemainGuidePoint;

    rail->srt.scale = sead::Vector3f::ones;
    rail->srt.rotate = sead::Vector3f::zero;
    rail->srt.translate = sead::Vector3f::zero;
    rail->ctrl_points[0] = sead::Vector3f::zero;
    rail->ctrl_points[1] = sead::Vector3f::zero;

    rail->prev_distance = 0.0;
    rail->next_distance = 0.0;

    return rail;
}

RailConnectablePoint::RailConnectablePoint() = default;

RailConnectablePoint::~RailConnectablePoint() {
    sead::HeapMgr::instance()->getCurrentHeap();
    delete[] mJunctionPoint;
}

RailBase* RailConnectablePoint::getJunctionRail() const {
    return mJunctionRail;
}

RailPoint* RailConnectablePoint::getJunctionPoint() const {
    return mJunctionPoint;
}

bool RailConnectablePoint::parse(MubinIter* iter, sead::Heap* heap) {
    iter->getScale(&srt.scale);
    iter->getRotate(&srt.rotate);

    bool success = true;
    if (!iter->tryGetFloatArrayByKey(srt.translate.e.data(), "Translate")) {
        success = false;
    }

    if (!iter->tryGetParamFloatByKey(&prev_distance, "PrevDistance")) {
        success = false;
    }

    if (!iter->tryGetParamFloatByKey(&next_distance, "NextDistance")) {
        success = false;
    }

    iter->tryGetControlPoints(&ctrl_points);

    return success;
}

RailRoutePoint::RailRoutePoint() = default;

RailRoutePoint::~RailRoutePoint() = default;

const char* RailRoutePoint::getCheckPointName() const {
    return mCheckPointName;
}

bool RailRoutePoint::parse(MubinIter* iter, sead::Heap* heap) {
    iter->getScale(&srt.scale);
    iter->getRotate(&srt.rotate);

    bool success = true;
    if (!iter->tryGetFloatArrayByKey(srt.translate.e.data(), "Translate")) {
        success = false;
    }

    if (!iter->tryGetParamFloatByKey(&prev_distance, "PrevDistance")) {
        success = false;
    }

    if (!iter->tryGetParamFloatByKey(&next_distance, "NextDistance")) {
        success = false;
    }

    iter->tryGetControlPoints(&ctrl_points);

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
    int success = RailBase::parse(iter);

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

    return success & iter->tryGetParamStringByKey(&mRouteId, "RouteId");
}

}  // namespace ksys::map
