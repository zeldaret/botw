#pragma once

#include <Havok/Physics2012/Collide/Query/Collector/PointCollector/hkpClosestCdPointCollector.h>
#include <gfx/seadColor.h>
#include <math/seadMatrix.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>

class hkpAllCdPointCollector;
class hkpCdPointCollector;
struct hkpLinearCastInput;
struct hkpRootCdPoint;

namespace ksys::phys {

enum class OnlyLockIfNeeded : bool;

class LayerMaskBuilder;
class RigidBody;
class QueryContactPointInfo;

class ShapeCast {
    SEAD_RTTI_BASE(ShapeCast)
public:
    enum class WeldClosestPoints : bool { Yes = true, No = false };

    virtual bool executeQuery(WeldClosestPoints weld_closest_points) = 0;

protected:
    virtual void doCast(const hkpLinearCastInput& input, hkpCdPointCollector& cast_collector,
                        hkpCdPointCollector* start_collector) = 0;

public:
    enum class Mode {
        _0 = 0,
        _1 = 1,
        _2 = 2,
    };

    ShapeCast(RigidBody* body, QueryContactPointInfo* contact_point_info, Mode mode);
    virtual ~ShapeCast();

    void reset();

    void setRotation(sead::Quatf rotation);
    void setRotation(const sead::Matrix33f& rotation_matrix);
    void setRotation(const sead::Matrix34f& transform_matrix);

    const sead::Vector3f& getStart() const { return mFrom; }
    const sead::Vector3f& getEnd() const { return mTo; }
    void setStartAndEnd(const sead::Vector3f& start, const sead::Vector3f& end);
    void setStartAndDisplacement(const sead::Vector3f& start, const sead::Vector3f& displacement);
    void setStartAndDisplacementScaled(const sead::Vector3f& start,
                                       const sead::Vector3f& displacement,
                                       float displacement_scale);

    void setLayerMasks(const LayerMaskBuilder& mask_builder);

    void setColors(const sead::Color4f& color1, const sead::Color4f& color2,
                   const sead::Color4f& color3, bool enabled = true);

protected:
    bool doExecuteQuery(hkpCdPointCollector& cast_collector,
                        hkpAllCdPointCollector* start_collector,
                        WeldClosestPoints weld_closest_points,
                        OnlyLockIfNeeded only_lock_if_needed);

    enum class ClampDistance : bool { Yes = true, No = false };
    bool registerContactPoint(const hkpRootCdPoint& point, RigidBody* body,
                              ClampDistance clamp_distance);

    RigidBody* mBody{};
    QueryContactPointInfo* mContactPointInfo{};
    /// The start position of the ray in world space.
    sead::Vector3f mFrom = sead::Vector3f::zero;
    /// The end position of the ray in world space.
    sead::Vector3f mTo = sead::Vector3f::zero;
    sead::Quatf mRotation = sead::Quatf::unit;
    bool _40{};
    bool _41{};
    bool _42{};
    int _44{};
    Mode mMode{};
};

class FilteredClosestCdPointCollector : public hkpClosestCdPointCollector {
public:
    HK_DECLARE_CLASS_ALLOCATOR(FilteredClosestCdPointCollector)

    FilteredClosestCdPointCollector(RigidBody* body, QueryContactPointInfo* contact_point_info);
    ~FilteredClosestCdPointCollector() override;

    void addCdPoint(const hkpCdPoint& point) override;
    void reset() override;

protected:
    RigidBody* mBody{};
    QueryContactPointInfo* mContactPointInfo{};
};

}  // namespace ksys::phys
