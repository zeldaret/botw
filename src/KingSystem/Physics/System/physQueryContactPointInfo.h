#pragma once

#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace ksys::phys {

class QueryContactPointInfo : public ContactPointInfo {
public:
    static QueryContactPointInfo* make(sead::Heap* heap, int num_points,
                                       const sead::SafeString& name, int a, int b);
    static void free(QueryContactPointInfo* info);

    using ContactPointInfo::ContactPointInfo;
    ~QueryContactPointInfo() override;
};

}  // namespace ksys::phys
