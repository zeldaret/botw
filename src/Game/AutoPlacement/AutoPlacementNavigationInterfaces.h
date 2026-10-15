#pragma once
#include <math/seadVector.h>
namespace ksys::ai {
// The original service owns this instance. Its storage is not defined here.
class HavokAI;
extern HavokAI* gHavokAI;
// The original service writes XYZ to result and reads XYZ from position.
int queryNavMeshFace(HavokAI* service, sead::Vector3f* result, const sead::Vector3f& position,
                     float radius);
}  // namespace ksys::ai
