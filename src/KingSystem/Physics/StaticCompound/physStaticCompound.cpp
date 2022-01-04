#include "KingSystem/Physics/StaticCompound/physStaticCompound.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundFieldBodyGroup.h"

namespace ksys::phys {

StaticCompound::StaticCompound() = default;

StaticCompound::~StaticCompound() {
    // FIXME
}

FieldBodyGroup* StaticCompound::getFieldBodyGroup(int idx) {
    return &mFieldBodyGroups[idx];
}

bool StaticCompound::hasFieldBodyGroup(FieldBodyGroup* group) const {
    for (int i = 0, n = mFieldBodyGroups.size(); i < n; ++i) {
        if (&mFieldBodyGroups[i] == group)
            return true;
    }
    return false;
}

}  // namespace ksys::phys
