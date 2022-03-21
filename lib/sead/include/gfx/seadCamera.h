#ifndef SEAD_CAMERA_H_
#define SEAD_CAMERA_H_

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead
{
class Camera
{
    SEAD_RTTI_BASE(Camera)

public:
    Camera() = default;
    virtual ~Camera();

    virtual void doUpdateMatrix(Matrix34f* mtx) const = 0;

    Matrix34f mMatrix = Matrix34f::ident;
};

class LookAtCamera : public Camera
{
    SEAD_RTTI_OVERRIDE(LookAtCamera, Camera)
public:
    LookAtCamera(const Vector3f& pos, const Vector3f& at, const Vector3f& up);

    Vector3f& getPos() { return mPos; }
    Vector3f& getAt() { return mAt; }
    Vector3f& getUp() { return mUp; }
    const Vector3f& getPos() const { return mPos; }
    const Vector3f& getAt() const { return mAt; }
    const Vector3f& getUp() const { return mUp; }

    void doUpdateMatrix(Matrix34f* mtx) const override;

private:
    Vector3f mPos;
    Vector3f mAt;
    Vector3f mUp;
};
}  // namespace sead

#endif  // SEAD_CAMERA_H_
