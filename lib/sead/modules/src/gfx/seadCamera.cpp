#include "gfx/seadCamera.h"
#include "basis/seadRawPrint.h"

namespace sead
{
Camera::~Camera() = default;

LookAtCamera::LookAtCamera(const Vector3f& pos, const Vector3f& at, const Vector3f& up)
    : mPos(pos), mAt(at), mUp(up)
{
    SEAD_ASSERT(mPos != mAt);
    mUp.normalize();
}
}  // namespace sead
