#ifdef cafe
#include <gfx/cafe/seadPrimitiveRendererCafe.h>
#endif  // cafe

#include <gfx/seadPrimitiveRenderer.h>

namespace sead
{
SEAD_SINGLETON_DISPOSER_IMPL(PrimitiveRenderer)

PrimitiveRenderer::PrimitiveRenderer()
    : IDisposer(), mRendererImpl(NULL), mModelMtx(Matrix34f::ident)
{
}

void PrimitiveRenderer::doPrepare_(Heap* heap)
{
#ifdef cafe
    mRendererImpl = new (heap) PrimitiveRendererCafe(heap);
#else
#error "Unknown platform"
#endif  // cafe
}

void PrimitiveRenderer::prepareFromBinary(Heap* heap, const void* bin_data, u32 bin_size)
{
    doPrepare_(heap);
    mRendererImpl->prepareFromBinaryImpl(heap, bin_data, bin_size);
}

void PrimitiveRenderer::prepare(Heap* heap, const SafeString& path)
{
    doPrepare_(heap);
    mRendererImpl->prepareImpl(heap, path);
}

void PrimitiveRenderer::setCamera(const Camera& camera)
{
    mRendererImpl->setCameraImpl(camera);
}

void PrimitiveRenderer::setProjection(const Projection& projection)
{
    mRendererImpl->setProjectionImpl(projection);
}

void PrimitiveRenderer::setModelMatrix(const Matrix34f& model_mtx)
{
#ifdef cafe
    ASM_MTXCopy(const_cast<f32(*)[4]>(model_mtx.m), mModelMtx.m);
#else
#error "Unknown platform"
#endif  // cafe
}

void PrimitiveRenderer::begin()
{
    mRendererImpl->beginImpl();
}

void PrimitiveRenderer::end()
{
    mRendererImpl->endImpl();
}

}  // namespace sead
