#pragma once

#include <container/seadBuffer.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Map/mapMubinIter.h"

namespace ksys::map {

class Placement18;

class RailPoint {
    friend class Rail;

public:
    RailPoint() {
        mSRT.scale = sead::Vector3f::ones;
        mSRT.rotate = sead::Vector3f::zero;
        mSRT.translate = sead::Vector3f::zero;
        mCtrlPoints[0] = sead::Vector3f::zero;
        mCtrlPoints[1] = sead::Vector3f::zero;
        mPrevDistance = 0.0;
        mNextDistance = 0.0;
    }
    virtual ~RailPoint();
    virtual bool parse(MubinIter* iter, sead::Heap* heap);

    const MubinIter& getIter() const;
    const sead::Vector3f& getRotate() const;
    const sead::Vector3f& getTranslate() const;
    f32 getPrevDistance() const;
    f32 getNextDistance() const;

protected:
    SRT mSRT;
    ControlPoints mCtrlPoints;
    float mPrevDistance;
    float mNextDistance;
    MubinIter mIter;
};

class Rail {
public:
    Rail();
    virtual ~Rail();
    virtual void init(MubinIter* iter, sead::Heap* heap);
    virtual s32 x_18() { return 0; }
    virtual s32 x_20() { return 0; }
    virtual RailPoint* allocPoint(sead::Heap* heap);
    virtual bool parse(MubinIter* iter);
    virtual void x_38() {}

    RailPoint* allocPointIdx(s32 idx, sead::Heap* heap);
    s32 getNumPoints() const;
    const RailPoint* getPoint(s32 idx) const;
    RailPoint* getPoint(s32 idx);

    const SRT& getPointSRT(s32 idx) const;
    const sead::Vector3f& getPointRotate(s32 idx) const;
    const sead::Vector3f& getPointTranslate(s32 idx) const;
    const sead::Vector3f& getControlPoint(s32 rail_idx, s32 pt_idx) const;

    sead::Vector3f calcTranslate(float progress) const;
    void calcTranslate(sead::Vector3f* pos_out, float progress) const;
    void calcTranslateRotate(sead::Vector3f* pos_out, sead::Vector3f* rot_out,
                             float progress) const;
    bool isClosed() const;
    bool isBezier() const;
    const u32& getHashId() const;
    const char* getUniqueName() const;

    enum class Flag : u32 {
        Closed = 1 << 0,
        Bezier = 1 << 1,
        RenderEnabled = 1 << 2,
        AutoPlacementEnabled = 1 << 3,
        Walkable = 1 << 4,
        EnableHorseTrace = 1 << 5,
    };

protected:
    static constexpr u32 sHashBase = 0;

    sead::TypedBitFlag<Flag> mFlags{};
    u32 mHashId = sHashBase;
    const char* mUniqueName{};
    sead::Buffer<RailPoint*> mRailPoints{};
    MubinIter mIter{};
};

class RailGuidePoint : public RailPoint {
    friend class RailGuide;

public:
    RailGuidePoint();
    ~RailGuidePoint() override;

    bool parse(MubinIter* iter, sead::Heap* heap) override;

protected:
    float mWaitFrame;
};

class RailRemainGuidePoint : public RailGuidePoint {
    friend class RailRemainGuide;

public:
    RailRemainGuidePoint();
    ~RailRemainGuidePoint() override;

    bool parse(MubinIter* iter, sead::Heap* heap) override;

protected:
    float mMoveSpeed;
};

class RailGuide : public Rail {
public:
    RailGuide();
    ~RailGuide() override;
};

class RailRemainGuide : public RailGuide {
public:
    RailRemainGuide();
    ~RailRemainGuide() override;

    RailPoint* allocPoint(sead::Heap* heap) override;
};

class RailConnectablePoint : public RailPoint {
    friend class RailConnectable;

public:
    RailConnectablePoint();
    ~RailConnectablePoint() override;

    bool parse(MubinIter* iter, sead::Heap* heap) override;

    Rail* getJunctionRail() const;
    RailPoint* getJunctionPoint() const;
    void parseJunctions(Placement18 p18, s32 idx, u32 hash, sead::Heap* heap);

protected:
    Rail* mJunctionRail;
    RailPoint* mJunctionPoint;
};

class RailConnectable : public Rail {
public:
    RailConnectable();
    ~RailConnectable() override;

    s32 x_18() override { return 1; }
    s32 x_20() override { return 1; }
    void x_38() override {}
};

class RailRoutePoint : public RailConnectablePoint {
    friend class RailRoute;

public:
    RailRoutePoint();
    ~RailRoutePoint() override;

    bool parse(MubinIter* iter, sead::Heap* heap) override;
    const char* getCheckPointName() const;

protected:
    const char* mEntryPointName;
    const char* mCheckPointName;
};

class RailRoute : public RailConnectable {
public:
    RailRoute();
    ~RailRoute() override;

    bool parse(MubinIter* iter) override;

    bool isRenderEnabled() const;
    bool isAutoPlacementEnabled() const;
    bool isWalkable() const;
    bool isHorseTraceEnabled() const;
    const char* getRouteId() const;
    const char* getCheckPointName(s32 idx) const;

protected:
    const char* mRouteId;
};

}  // namespace ksys::map
