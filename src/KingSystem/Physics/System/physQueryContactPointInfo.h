#pragma once

#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace ksys::phys {

class QueryContactPointInfo : public ContactPointInfo {
public:
    class Iterator : public ContactPointInfo::Iterator {
    public:
        using ContactPointInfo::Iterator::Iterator;

        void getPointPosition(sead::Vector3f* out, Point point) const override;
        sead::Vector3f getPointPosition(Point point) const override;
    };

    static QueryContactPointInfo* make(sead::Heap* heap, int num_points,
                                       const sead::SafeString& name, int a, int b);
    static void free(QueryContactPointInfo* info);

    using ContactPointInfo::ContactPointInfo;
    ~QueryContactPointInfo() override;

    auto begin() const { return Iterator(mPoints, mNumContactPoints); }
    auto end() const { return Iterator(mPoints, mNumContactPoints, Iterator::IsEnd::Yes); }

    friend class ClosestPointQuery;
};

}  // namespace ksys::phys
