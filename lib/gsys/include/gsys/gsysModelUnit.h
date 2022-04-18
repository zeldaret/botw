#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <hostio/seadHostIONode.h>
#include <math/seadBoundBox.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <nn/g3d/World.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include "gsys/gsysModelUnitDrawArray.h"

namespace agl {
class UniformBlock;
}

namespace gsys {

namespace ModelEnum {
enum class ShaderAssignType;
enum class RenderOption;
enum class RenderViewOption;
}  // namespace ModelEnum

class ModelRenderUnit;
class ModelScene;
class ModelUnitCallbackArg;
class ModelViewData;

using ModelUnitCallback = sead::IDelegate1<const ModelUnitCallbackArg&>;
using ModelUnitCallbackStorage = sead::AnyDelegate1<const ModelUnitCallbackArg&>;

// TODO
class ModelUnit {
    SEAD_RTTI_BASE(ModelUnit)
public:
    // TODO: is this an enum/enum class or a class?
    enum class BoolType;

    enum class Flag {
        DebugWorldCallback = 4,
        DebugDrawCallback = 8,
    };

    enum class Attribute {
        OcclusionQuery = 1,
        ViewFrustrumCulling = 2,
        LodCalculation = 4,
        ShapeCulling = 8,
        BufferSwap = 0x10,
    };

    enum class ORFlag {
        Force = 1,
    };

    ModelUnit();
    virtual ~ModelUnit();

    // FIXME
    virtual void createDrawArray(const ModelUnitDrawArray::CreateArg& arg, sead::Heap* heap);

    virtual sead::SafeString getName() const;

    virtual int getBoneNum() const;
    virtual int searchBoneIndex(const sead::SafeString& bone_name) const;
    virtual sead::SafeString getBoneName(int bone_idx) const;
    virtual void setBoneLocalMatrix(const sead::Matrix34f& matrix, const sead::Vector3f& pos,
                                    int bone_idx);
    virtual void setBoneLocalRTMatrix(const sead::Matrix34f& matrix, int bone_idx);
    virtual void setBoneLocalScale(const sead::Vector3f& scale, int bone_idx);
    virtual void getBoneLocalMatrix(sead::Matrix34f* matrix, sead::Vector3f* scale,
                                    int bone_idx) const;
    virtual void setBoneWorldMatrix(const sead::Matrix34f& matrix, int bone_idx);
    virtual void getBoneWorldMatrix(sead::Matrix34f* matrix, int bone_idx) const;
    virtual sead::Matrix34f* getBoneWorldMatrixPtr(int bone_idx) const;
    virtual void safeGetBoneWorldMatrix(sead::Matrix34f* matrix, int bone_idx) const;
    virtual void setBoneVisible(int bone_idx, bool visible);
    virtual bool isBoneVisible(int bone_idx) const;
    virtual int getBoneParentIndex(int bone_idx) const;
    virtual void copyBoneLocalMatrixTo(gsys::ModelUnit* target) const;
    virtual void copyBoneWorldMatrixTo(gsys::ModelUnit* target) const;
    virtual void clearBoneLocalMatrix();

    virtual int getMaterialNum() const = 0;
    virtual int searchMaterialIndex(const sead::SafeString& material_name) const;
    virtual sead::SafeString getMaterialName(int material_idx) const;

    virtual int searchMaterialParamIndex(int material_idx,
                                         const sead::SafeString& param_name) const;
    virtual sead::SafeString getMaterialParamName(int material_idx, int param_idx) const;

    virtual bool getMaterialParamBool(int material_idx, int param_idx) const;
    virtual void setMaterialParamBool(int material_idx, int param_idx, bool value);

    virtual int getMaterialParamInt(int material_idx, int param_idx) const;
    virtual void setMaterialParamInt(int material_idx, int param_idx, int value);

    virtual u32 getMaterialParamU32(int material_idx, int param_idx) const;
    virtual void setMaterialParamU32(int material_idx, int param_idx, u32 value);

    virtual float getMaterialParamF32(int material_idx, int param_idx) const;
    virtual void setMaterialParamF32(int material_idx, int param_idx, float value);

    virtual const sead::Vector2f& getMaterialParamVector2f(int material_idx, int param_idx) const;
    virtual void setMaterialParamVector2f(int material_idx, int param_idx,
                                          const sead::Vector2f& value);

    virtual const sead::Vector3f& getMaterialParamVector3f(int material_idx, int param_idx) const;
    virtual void setMaterialParamVector3f(int material_idx, int param_idx,
                                          const sead::Vector3f& value);

    virtual const sead::Vector4f& getMaterialParamVector4f(int material_idx, int param_idx) const;
    virtual void setMaterialParamVector4f(int material_idx, int param_idx,
                                          const sead::Vector4f& value);

    virtual const sead::Color4f& getMaterialParamColor4f(int material_idx, int param_idx) const;
    virtual void setMaterialParamColor4f(int material_idx, int param_idx,
                                         const sead::Color4f& value);

    virtual const sead::Color4f& getMaterialParamColor3f(int material_idx, int param_idx) const;
    virtual void setMaterialParamColor3f(int material_idx, int param_idx,
                                         const sead::Color4f& value);

    virtual void getMaterialParamTexSRT(int material_idx, int param_idx, sead::Vector2f* scale,
                                        float* rotate, sead::Vector2f* translate) const;
    virtual void setMaterialParamTexSRT(int material_idx, int param_idx,
                                        const sead::Vector2f& scale, float rotate,
                                        const sead::Vector2f& translate);

    virtual sead::Matrix34f* getMaterialParamEffectMatrixPtr(int material_idx, int param_idx) const;
    virtual void setMaterialParamEffectMatrixPtr(int material_idx, int param_idx,
                                                 sead::Matrix34f* matrix);

    virtual float getMaterialParamXluAlpha(int material_idx, int param_idx) const;
    virtual void setMaterialParamXluAlpha(int material_idx, int param_idx, float xlu_alpha);

    virtual void clearMaterialParameter(int material_idx);
    virtual void clearTexture(int unk);

    virtual void setMaterialVisible(int material_idx, bool visible);
    virtual bool isMaterialVisible(int material_idx) const;

    virtual void setMaterialShaderAssignVariation(int material_idx,
                                                  ModelEnum::ShaderAssignType assign_type, int);

    virtual int getShapeNum() const = 0;

    // TODO: reference or pointer?
    virtual ModelRenderUnit* getModelRenderUnit(int idx) = 0;
    virtual const ModelRenderUnit* getModelRenderUnit(int idx) const = 0;

    virtual void* createSubMeshRangeBuffer(sead::Heap* heap) const;
    virtual void setSubMeshRangeBuffer(int, void*);
    virtual void setSubMeshRangeBufferVisible(int, int, const bool*);

    virtual int countPolygonNum() const;

    virtual int getViewNum() const;
    virtual void calcBoundAABB(sead::BoundBox3f* aabb, bool) const;

    virtual bool isDefaultRenderOptionEnabled(int, ModelEnum::RenderOption) const;
    virtual bool isDefaultRenderViewOptionEnabled(int, ModelEnum::RenderViewOption, int) const;

    virtual void setUserUniformBlock(int, agl::UniformBlock* block);

    virtual void enableReverseCulling(int, bool enable);
    virtual bool isReverseCullingEnabled(int) const;

    virtual void setLodLevelNum(int lod_level_num);

    virtual void check(BoolType) const;
    virtual void calcBounding();
    virtual void bind(const ModelScene* scene);
    virtual void bindResource();
    virtual void syncResource();
    virtual void unbindResource();
    virtual void calcWorld(const sead::Matrix34f&, const sead::Vector3f&);
    virtual void postCalcWorld(const ModelScene* scene, u32, u32,
                               const ModelViewData* model_view_data, int);
    virtual void calcBeforeDraw(ModelScene* scene, const gsys::ModelViewData* model_view_data, int);
    virtual void forceCalcDrawSetup();
    virtual void setUpMaterialImpl(int, sead::Heap* heap);

protected:
    sead::TypedBitFlag<Flag, u8> mFlags;
    s8 mUnkIndex;
    s8 mNumLods;
    sead::BitFlag16 mVisibilityMask;
    u8 mDepthShadowCascade;
    u16 mCalcWeight;
    sead::TypedBitFlag<Attribute, u16> mAttributeFlags;
    u16 _14;
    u16 _16;
    void* _18;
    void* _20;
    ModelUnitDrawArray* mDrawArray;
    void* _30;
    void* _38;
    sead::Vector3f _40;
    u32 _4c;
    sead::Vector3f* _50;
    void* _58;
    void* _60;
    void* mMaterialInfo;
    void* _70;
    void* _78;
    void* _80;
    void* _88;
    void* _90;
    ModelUnitCallbackStorage mCallback;
    sead::SafeString mName;

#ifdef SEAD_DEBUG
    sead::TypedBitFlag<ORFlag, u8> mORFlags;
#endif
};

}  // namespace gsys
