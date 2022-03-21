#ifndef SEAD_PRIMITIVE_RENDERER_H_
#define SEAD_PRIMITIVE_RENDERER_H_

#include <gfx/seadColor.h>
#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace sead
{
class Heap;
class Camera;
class Projection;
class Texture;

class PrimitiveRendererBase
{
public:
    virtual void prepareFromBinaryImpl(Heap* heap, const void* bin_data, u32 bin_size) = 0;
    virtual void prepareImpl(Heap* heap, const SafeString& path) = 0;
    virtual void setCameraImpl(const Camera& camera) = 0;
    virtual void setProjectionImpl(const Projection& projection) = 0;
    virtual void beginImpl() = 0;
    virtual void endImpl() = 0;
    virtual void drawQuadImpl(const Matrix34f& model_mtx, const Color4f& colorL,
                              const Color4f& colorR) = 0;
    virtual void drawQuadImpl(const Matrix34f& model_mtx, const Texture& texture,
                              const Color4f& colorL, const Color4f& colorR, const Vector2f& uv_src,
                              const Vector2f& uv_size) = 0;
    virtual void drawBoxImpl(const Matrix34f& model_mtx, const Color4f& colorL,
                             const Color4f& colorR) = 0;
    virtual void drawCubeImpl(const Matrix34f& model_mtx, const Color4f& c0, const Color4f& c1) = 0;
    virtual void drawWireCubeImpl(const Matrix34f& model_mtx, const Color4f& c0,
                                  const Color4f& c1) = 0;
    virtual void drawLineImpl(const Matrix34f& model_mtx, const Color4f& c0, const Color4f& c1) = 0;
    virtual void drawSphere4x8Impl(const Matrix34f& model_mtx, const Color4f& north,
                                   const Color4f& south) = 0;
    virtual void drawSphere8x16Impl(const Matrix34f& model_mtx, const Color4f& north,
                                    const Color4f& south) = 0;
    virtual void drawDisk16Impl(const Matrix34f& model_mtx, const Color4f& center,
                                const Color4f& edge) = 0;
    virtual void drawDisk32Impl(const Matrix34f& model_mtx, const Color4f& center,
                                const Color4f& edge) = 0;
    virtual void drawCircle16Impl(const Matrix34f& model_mtx, const Color4f& edge) = 0;
    virtual void drawCircle32Impl(const Matrix34f& model_mtx, const Color4f& edge) = 0;
    virtual void drawCylinder16Impl(const Matrix34f& model_mtx, const Color4f& top,
                                    const Color4f& btm) = 0;
    virtual void drawCylinder32Impl(const Matrix34f& model_mtx, const Color4f& top,
                                    const Color4f& btm) = 0;
};

class PrimitiveRenderer : public IDisposer
{
    SEAD_SINGLETON_DISPOSER(PrimitiveRenderer)

public:
    class QuadArg
    {
    public:
        QuadArg()
            : mCenter(Vector3f::zero), mSize(Vector2f::zero), mColor0(Color4f::cWhite),
              mColor1(Color4f::cWhite), mHorizontal(false)
        {
        }

        void setCornerAndSize(const Vector3f&, const Vector2f&);
        // void setBoundBox(const BoundBox2f&, float);
        void setColor(const Color4f&, const Color4f&);
        void setColorHorizontal(const Color4f&, const Color4f&);

        Vector3f mCenter;
        Vector2f mSize;
        Color4f mColor0;
        Color4f mColor1;
        bool mHorizontal;
    };

    class CubeArg
    {
    public:
        void setCornerAndSize(const Vector3f&, const Vector3f&);
        // void setBoundBox(const BoundBox3f&);
    };

    struct UVArg;

public:
    PrimitiveRenderer();
    virtual ~PrimitiveRenderer() {}

    void prepareFromBinary(Heap* heap, const void* bin_data, u32 bin_size);
    void prepare(Heap* heap, const SafeString& path);
    void setCamera(const Camera& camera);
    void setProjection(const Projection& projection);
    void setModelMatrix(const Matrix34f& model_mtx);
    void begin();
    void end();

    void drawQuad(const Color4f&, const Color4f&);
    void drawQuad(const Texture&, const Color4f&, const Color4f&, const Vector2f&, const Vector2f&);
    void drawBox(const Color4f&, const Color4f&);
    void drawCube(const Color4f&, const Color4f&);
    void drawWireCube(const Color4f&, const Color4f&);
    void drawLine(const Color4f&, const Color4f&);
    void drawSphere4x8(const Color4f&, const Color4f&);
    void drawSphere8x16(const Color4f&, const Color4f&);
    void drawDisk16(const Color4f&, const Color4f&);
    void drawDisk32(const Color4f&, const Color4f&);
    void drawCircle16(const Color4f&);
    void drawCircle32(const Color4f&);
    void drawCylinder16(const Color4f&, const Color4f&);
    void drawCylinder32(const Color4f&, const Color4f&);

    void drawQuad(const QuadArg&);
    void drawQuad(const Texture&, const QuadArg&, const UVArg&);
    void drawBox(const QuadArg&);
    void drawCube(const CubeArg&);
    void drawWireCube(const CubeArg&);
    void drawLine(const Vector3f&, const Vector3f&, const Color4f&, const Color4f&);
    void drawLine(const Vector3f&, const Vector3f&, const Color4f&);
    void drawSphere4x8(const Vector3f&, float, const Color4f&, const Color4f&);
    void drawSphere4x8(const Vector3f&, float, const Color4f&);
    void drawSphere8x16(const Vector3f&, float, const Color4f&, const Color4f&);
    void drawSphere8x16(const Vector3f&, float, const Color4f&);
    void drawDisk16(const Vector3f&, float, const Color4f&, const Color4f&);
    void drawDisk16(const Vector3f&, float, const Color4f&);
    void drawDisk32(const Vector3f&, float, const Color4f&, const Color4f&);
    void drawDisk32(const Vector3f&, float, const Color4f&);
    void drawCircle16(const Vector3f&, float, const Color4f&);
    void drawCircle32(const Vector3f&, float, const Color4f&);
    void drawCylinder16(const Vector3f&, float, float, const Color4f&, const Color4f&);
    void drawCylinder16(const Vector3f&, float, float, const Color4f&);
    void drawCylinder32(const Vector3f&, float, float, const Color4f&, const Color4f&);
    void drawCylinder32(const Vector3f&, float, float, const Color4f&);

    void drawAxis(const Vector3f&, float);

private:
    void doPrepare_(Heap* heap);

    PrimitiveRendererBase* mRendererImpl;
    Matrix34f mModelMtx;
};

}  // namespace sead

#endif  // SEAD_PRIMITIVE_RENDERER_H_
