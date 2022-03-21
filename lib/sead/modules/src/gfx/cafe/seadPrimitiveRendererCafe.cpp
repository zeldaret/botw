#include <cafe.h>
#include <cafe/gfd.h>

#include <filedevice/seadFileDevice.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <gfx/cafe/seadPrimitiveRendererCafe.h>
#include <gfx/cafe/seadTextureCafeGX2.h>
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <heap/seadHeap.h>
#include <math/seadMatrixCalcCommon.h>
#include <prim/seadSafeString.h>

namespace sead
{
PrimitiveRendererCafe::PrimitiveRendererCafe(Heap* heap) : mCameraMtx(), mProjectionMtx() {}

void PrimitiveRendererCafe::prepareFromBinaryImpl(Heap* heap, const void* bin_data, u32 bin_size)
{
    u32 vtxHeaderSize = GFDGetVertexShaderHeaderSize(0, bin_data);
    u32 vtxProgramSize = GFDGetVertexShaderProgramSize(0, bin_data);

    mVertexShader = static_cast<GX2VertexShader*>(heap->alloc(vtxHeaderSize, 1));
    void* vtxProgram = heap->alloc(vtxProgramSize, GX2_SHADER_ALIGNMENT);

    GFDGetVertexShader(mVertexShader, vtxProgram, 0, bin_data);
    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, mVertexShader->shaderPtr, mVertexShader->shaderSize);

    u32 pixHeaderSize = GFDGetPixelShaderHeaderSize(0, bin_data);
    u32 pixProgramSize = GFDGetPixelShaderProgramSize(0, bin_data);

    mPixelShader = static_cast<GX2PixelShader*>(heap->alloc(pixHeaderSize, 1));
    void* pixProgram = heap->alloc(pixProgramSize, GX2_SHADER_ALIGNMENT);

    GFDGetPixelShader(mPixelShader, pixProgram, 0, bin_data);
    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, mPixelShader->shaderPtr, mPixelShader->shaderSize);

    mParamWVPOffset = GX2GetVertexUniformVarOffset(mVertexShader, "wvp");
    mParamUserOffset = GX2GetVertexUniformVarOffset(mVertexShader, "user");
    mParamColor0Offset = GX2GetVertexUniformVarOffset(mVertexShader, "color0");
    mParamColor1Offset = GX2GetVertexUniformVarOffset(mVertexShader, "color1");
    mParamRateOffset = GX2GetPixelUniformVarOffset(mPixelShader, "rate");
    mParamTexLocation = GX2GetPixelSamplerVarLocation(mPixelShader, "texture0");

    mAttrVertexLocation = GX2GetVertexAttribVarLocation(mVertexShader, "Vertex");
    mAttrTexCoord0Location = GX2GetVertexAttribVarLocation(mVertexShader, "TexCoord0");
    mAttrColorRateLocation = GX2GetVertexAttribVarLocation(mVertexShader, "ColorRate");

    GX2InitAttribStream(&mAttributes[0], mAttrVertexLocation, 0, 0,
                        GX2_ATTRIB_FORMAT_32_32_32_FLOAT);
    GX2InitAttribStream(&mAttributes[1], mAttrTexCoord0Location, 0, sizeof(f32) * 3,
                        GX2_ATTRIB_FORMAT_32_32_FLOAT);
    GX2InitAttribStream(&mAttributes[2], mAttrColorRateLocation, 0, sizeof(f32) * 5,
                        GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT);

    mFetchShaderBufPtr = heap->alloc(GX2CalcFetchShaderSize(3), GX2_SHADER_ALIGNMENT);

    GX2InitFetchShader(&mFetchShader, mFetchShaderBufPtr, 3, mAttributes);
    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, mFetchShaderBufPtr, GX2CalcFetchShaderSize(3));

    {
        // Quad
        mQuadVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(
            heap->alloc(4 * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mQuadIndexBuf = static_cast<u16*>(heap->alloc(6 * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));

        PrimitiveRendererUtil::setQuadVertex(mQuadVertexBuf, mQuadIndexBuf);
        mQuadVertexBuf[0].uv.x = 0.0f;
        mQuadVertexBuf[0].uv.y = 0.0f;
        mQuadVertexBuf[1].uv.x = 1.0f;
        mQuadVertexBuf[1].uv.y = 0.0f;
        mQuadVertexBuf[2].uv.x = 0.0f;
        mQuadVertexBuf[2].uv.y = 1.0f;
        mQuadVertexBuf[3].uv.x = 1.0f;
        mQuadVertexBuf[3].uv.y = 1.0f;

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mQuadVertexBuf,
                      4 * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mQuadIndexBuf, 6 * sizeof(u16));
    }

    {
        // Box
        static const u16 idx[4] = {0, 1, 3, 2};
        mBoxIndexBuf = static_cast<u16*>(heap->alloc(sizeof(idx), GX2_INDEX_BUFFER_ALIGNMENT));
        memcpy(mBoxIndexBuf, idx, sizeof(idx));

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mBoxIndexBuf, 4 * sizeof(u16));
    }

    {
        // Line
        mLineVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(
            heap->alloc(4 * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mLineIndexBuf = static_cast<u16*>(heap->alloc(6 * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        PrimitiveRendererUtil::setLineVertex(mLineVertexBuf, mLineIndexBuf);

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mLineVertexBuf,
                      4 * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mLineIndexBuf, 6 * sizeof(u16));
    }

    {
        // Cube
        mCubeVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(
            heap->alloc(8 * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mCubeIndexBuf =
            static_cast<u16*>(heap->alloc(36 * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        PrimitiveRendererUtil::setCubeVertex(mCubeVertexBuf, mCubeIndexBuf);

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mCubeVertexBuf,
                      8 * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mCubeIndexBuf, 36 * sizeof(u16));
    }

    {
        // WireCube
        mWireCubeVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(
            heap->alloc(8 * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mWireCubeIndexBuf =
            static_cast<u16*>(heap->alloc(17 * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        PrimitiveRendererUtil::setWireCubeVertex(mWireCubeVertexBuf, mWireCubeIndexBuf);

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mWireCubeVertexBuf,
                      8 * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mWireCubeIndexBuf, 17 * sizeof(u16));
    }

    {
        // SphereS
        mSphereSVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(heap->alloc(
            (4 * 8 + 2) * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mSphereSIndexBuf =
            static_cast<u16*>(heap->alloc((4 * 8 * 6) * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        PrimitiveRendererUtil::setSphereVertex(mSphereSVertexBuf, mSphereSIndexBuf, 8, 4);

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mSphereSVertexBuf,
                      (4 * 8 + 2) * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mSphereSIndexBuf,
                      (4 * 8 * 6) * sizeof(u16));
    }

    {
        // SphereL
        mSphereLVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(heap->alloc(
            (8 * 16 + 2) * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mSphereLIndexBuf =
            static_cast<u16*>(heap->alloc((8 * 16 * 6) * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        PrimitiveRendererUtil::setSphereVertex(mSphereLVertexBuf, mSphereLIndexBuf, 16, 8);

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mSphereLVertexBuf,
                      (8 * 16 + 2) * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mSphereLIndexBuf,
                      (8 * 16 * 6) * sizeof(u16));
    }

    {
        // DiskS
        mDiskSVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(heap->alloc(
            (16 + 1) * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mDiskSIndexBuf =
            static_cast<u16*>(heap->alloc((8 * 6) * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        PrimitiveRendererUtil::setDiskVertex(mDiskSVertexBuf, mDiskSIndexBuf, 16);

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mDiskSVertexBuf,
                      (16 + 1) * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mDiskSIndexBuf, (8 * 6) * sizeof(u16));
    }

    {
        // DiskL
        mDiskLVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(heap->alloc(
            (32 + 1) * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mDiskLIndexBuf =
            static_cast<u16*>(heap->alloc((16 * 6) * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        PrimitiveRendererUtil::setDiskVertex(mDiskLVertexBuf, mDiskLIndexBuf, 32);

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mDiskLVertexBuf,
                      (32 + 1) * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mDiskLIndexBuf, (16 * 6) * sizeof(u16));
    }

    {
        // CircleS
        mCircleSIndexBuf =
            static_cast<u16*>(heap->alloc(16 * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        for (s32 i = 0; i < 16; i++)
            mCircleSIndexBuf[i] = i;
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mCircleSIndexBuf, 16 * sizeof(u16));
    }

    {
        // CircleL
        mCircleLIndexBuf =
            static_cast<u16*>(heap->alloc(32 * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        for (s32 i = 0; i < 32; i++)
            mCircleLIndexBuf[i] = i;
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mCircleLIndexBuf, 32 * sizeof(u16));
    }

    {
        // CylinderS
        mCylinderSVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(heap->alloc(
            (16 * 2 + 2) * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mCylinderSIndexBuf =
            static_cast<u16*>(heap->alloc((16 * 12) * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        PrimitiveRendererUtil::setCylinderVertex(mCylinderSVertexBuf, mCylinderSIndexBuf, 16);

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mCylinderSVertexBuf,
                      (16 * 2 + 2) * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mCylinderSIndexBuf,
                      (16 * 12) * sizeof(u16));
    }

    {
        // CylinderL
        mCylinderLVertexBuf = static_cast<PrimitiveRendererUtil::Vertex*>(heap->alloc(
            (32 * 2 + 2) * sizeof(PrimitiveRendererUtil::Vertex), GX2_VERTEX_BUFFER_ALIGNMENT));
        mCylinderLIndexBuf =
            static_cast<u16*>(heap->alloc((32 * 12) * sizeof(u16), GX2_INDEX_BUFFER_ALIGNMENT));
        PrimitiveRendererUtil::setCylinderVertex(mCylinderLVertexBuf, mCylinderLIndexBuf, 32);

        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mCylinderLVertexBuf,
                      (32 * 2 + 2) * sizeof(PrimitiveRendererUtil::Vertex));
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, mCylinderLIndexBuf,
                      (32 * 12) * sizeof(u16));
    }

    GX2InitSampler(&mDrawQuadSampler, GX2_TEX_CLAMP_CLAMP, GX2_TEX_XY_FILTER_BILINEAR);
}

void PrimitiveRendererCafe::prepareImpl(Heap* heap, const SafeString& path)
{
    FileDevice::LoadArg arg;
    arg.path = path;
    arg.alignment = 0x20;
    arg.heap = heap;

    const void* file = sead::FileDeviceMgr::instance()->tryLoad(arg);
    prepareFromBinaryImpl(heap, file, arg.read_size);
}

void PrimitiveRendererCafe::setCameraImpl(const Camera& camera)
{
    ASM_MTXCopy(const_cast<f32(*)[4]>(camera.mMatrix.m), mCameraMtx.m);
}

void PrimitiveRendererCafe::setProjectionImpl(const Projection& projection)
{
    ASM_MTX44Copy(const_cast<f32(*)[4]>(projection.getDeviceProjectionMatrix().m),
                  mProjectionMtx.m);
}

void PrimitiveRendererCafe::beginImpl()
{
    Matrix44f wvp;
    Matrix44CalcCommon<f32>::multiply(wvp, mProjectionMtx, mCameraMtx);

    GX2SetShaders(&mFetchShader, mVertexShader, mPixelShader);

    GX2SetVertexUniformReg(mParamWVPOffset, 0x10, &wvp);
    GX2SetVertexUniformReg(mParamUserOffset, 0x10, &Matrix44f::ident);

    GX2SetLineWidth(2.0f);
}

void PrimitiveRendererCafe::endImpl() {}

void PrimitiveRendererCafe::drawQuadImpl(const Matrix34f& model_mtx, const Color4f& colorL,
                                         const Color4f& colorR)
{
    drawTriangles_(model_mtx, colorL, colorR, mQuadVertexBuf, 4, mQuadIndexBuf, 6, NULL);
}

void PrimitiveRendererCafe::drawQuadImpl(const Matrix34f& model_mtx, const Texture& texture,
                                         const Color4f& colorL, const Color4f& colorR,
                                         const Vector2f& uv_src, const Vector2f& uv_size)
{
    const TextureCafeGX2* texure_cafe_gx2 =
        DynamicCast<const TextureCafeGX2, const Texture>(&texture);
    drawTriangles_(model_mtx, colorL, colorR, mQuadVertexBuf, 4, mQuadIndexBuf, 6,
                   texure_cafe_gx2->mGX2Texture);
}

void PrimitiveRendererCafe::drawBoxImpl(const Matrix34f& model_mtx, const Color4f& colorL,
                                        const Color4f& colorR)
{
    drawLines_(model_mtx, colorL, colorR, mQuadVertexBuf, 4, mBoxIndexBuf, 4);
}

void PrimitiveRendererCafe::drawCubeImpl(const Matrix34f& model_mtx, const Color4f& c0,
                                         const Color4f& c1)
{
    drawTriangles_(model_mtx, c0, c1, mCubeVertexBuf, 8, mCubeIndexBuf, 36, NULL);
}

void PrimitiveRendererCafe::drawWireCubeImpl(const Matrix34f& model_mtx, const Color4f& c0,
                                             const Color4f& c1)
{
    drawLines_(model_mtx, c0, c1, mWireCubeVertexBuf, 8, mWireCubeIndexBuf, 17);
}

void PrimitiveRendererCafe::drawLineImpl(const Matrix34f& model_mtx, const Color4f& c0,
                                         const Color4f& c1)
{
    drawLines_(model_mtx, c0, c1, mLineVertexBuf, 2, mLineIndexBuf, 2);
}

void PrimitiveRendererCafe::drawSphere4x8Impl(const Matrix34f& model_mtx, const Color4f& north,
                                              const Color4f& south)
{
    drawTriangles_(model_mtx, north, south, mSphereSVertexBuf, 34, mSphereSIndexBuf, 192, NULL);
}

void PrimitiveRendererCafe::drawSphere8x16Impl(const Matrix34f& model_mtx, const Color4f& north,
                                               const Color4f& south)
{
    drawTriangles_(model_mtx, north, south, mSphereLVertexBuf, 130, mSphereLIndexBuf, 768, NULL);
}

void PrimitiveRendererCafe::drawDisk16Impl(const Matrix34f& model_mtx, const Color4f& center,
                                           const Color4f& edge)
{
    drawTriangles_(model_mtx, center, edge, mDiskSVertexBuf, 17, mDiskSIndexBuf, 48, NULL);
}

void PrimitiveRendererCafe::drawDisk32Impl(const Matrix34f& model_mtx, const Color4f& center,
                                           const Color4f& edge)
{
    drawTriangles_(model_mtx, center, edge, mDiskLVertexBuf, 33, mDiskLIndexBuf, 96, NULL);
}

void PrimitiveRendererCafe::drawCircle16Impl(const Matrix34f& model_mtx, const Color4f& edge)
{
    drawLines_(model_mtx, edge, edge, mDiskSVertexBuf, 17, mCircleSIndexBuf, 16);
}

void PrimitiveRendererCafe::drawCircle32Impl(const Matrix34f& model_mtx, const Color4f& edge)
{
    drawLines_(model_mtx, edge, edge, mDiskLVertexBuf, 33, mCircleLIndexBuf, 32);
}

void PrimitiveRendererCafe::drawCylinder16Impl(const Matrix34f& model_mtx, const Color4f& top,
                                               const Color4f& btm)
{
    drawTriangles_(model_mtx, top, btm, mCylinderSVertexBuf, 34, mCylinderSIndexBuf, 192, NULL);
}

void PrimitiveRendererCafe::drawCylinder32Impl(const Matrix34f& model_mtx, const Color4f& top,
                                               const Color4f& btm)
{
    drawTriangles_(model_mtx, top, btm, mCylinderLVertexBuf, 66, mCylinderLIndexBuf, 384, NULL);
}

void PrimitiveRendererCafe::drawTriangles_(const Matrix34f& model_mtx, const Color4f& c0,
                                           const Color4f& c1, PrimitiveRendererUtil::Vertex* vtx,
                                           u32 vtx_num, u16* idx, u32 idx_num,
                                           const GX2Texture* tex)
{
    GX2SetVertexUniformReg(mParamUserOffset, 12, &model_mtx);
    GX2SetVertexUniformReg(mParamColor0Offset, 4, &c0);
    GX2SetVertexUniformReg(mParamColor1Offset, 4, &c1);

    if (tex != NULL)
    {
        GX2SetPixelUniformReg(mParamRateOffset, 4, &Vector4f::ex);
        GX2SetPixelTexture(tex, mParamTexLocation);
        GX2SetPixelSampler(&mDrawQuadSampler, mParamTexLocation);
    }

    else
        GX2SetPixelUniformReg(mParamRateOffset, 4, &Vector4f::zero);

    GX2SetAttribBuffer(0, vtx_num * sizeof(PrimitiveRendererUtil::Vertex),
                       sizeof(PrimitiveRendererUtil::Vertex), vtx);
    GX2DrawIndexed(GX2_PRIMITIVE_TRIANGLES, idx_num, GX2_INDEX_FORMAT_U16, idx);
}

void PrimitiveRendererCafe::drawLines_(const Matrix34f& model_mtx, const Color4f& c0,
                                       const Color4f& c1, PrimitiveRendererUtil::Vertex* vtx,
                                       u32 vtx_num, u16* idx, u32 idx_num)
{
    GX2SetVertexUniformReg(mParamUserOffset, 12, &model_mtx);
    GX2SetVertexUniformReg(mParamColor0Offset, 4, &c0);
    GX2SetVertexUniformReg(mParamColor1Offset, 4, &c1);
    GX2SetPixelUniformReg(mParamRateOffset, 4, &Vector4f::zero);
    GX2SetAttribBuffer(0, vtx_num * sizeof(PrimitiveRendererUtil::Vertex),
                       sizeof(PrimitiveRendererUtil::Vertex), vtx);
    GX2DrawIndexed(GX2_PRIMITIVE_LINE_LOOP, idx_num, GX2_INDEX_FORMAT_U16, idx);
}

}  // namespace sead
