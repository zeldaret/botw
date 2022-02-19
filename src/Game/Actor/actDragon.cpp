#include "Game/Actor/actDragon.h"
#include <math/seadVector.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::act {

inline float sqXYZDistance(const sead::Vector3f& a, const sead::Vector3f& b) {
    sead::Vector3f diff = a;
    diff -= b;
    return diff.squaredLength();
}

// NON_MATCHING: Swapped arguments in fadd for distance calcuation
bool getDragonItemDropPosition(sead::Vector3f* target_pos, const sead::Vector3f& current_pos) {
    auto* mgr = ksys::map::PlacementMgr::instance();
    const auto& results = mgr->mTraverseResults[1 - mgr->mTraverseResultIdx];

    sead::SafeArray<sead::Vector3f, 3> pos;
    pos.fill(sead::Vector3f::zero);

    bool ok = false;
    for (const auto& obj : results.dragon_item_drop_targets) {
        const sead::Vector3f& obj_pos = obj.getTranslate();
        if (!(obj_pos.y < current_pos.y)) {
            continue;
        }

        // Looks like an Insertion Sort
        for (int i = 0; i < pos.size(); i++) {
            bool closer = sqXYZDistance(obj_pos, current_pos) < sqXYZDistance(pos[i], current_pos);
            if (closer || pos[i] == sead::Vector3f(0, 0, 0)) {
                if (i > 0) {
                    pos[i - 1] = pos[i];
                }
                pos[i] = obj_pos;
                ok = true;
            }
        }
    }
    if (!ok) {
        return false;
    }
    int index = sead::GlobalRandom::instance()->getS32Range(0, 3);
    target_pos->e = pos[index].e;
    return true;
}

}  // namespace uking::act
