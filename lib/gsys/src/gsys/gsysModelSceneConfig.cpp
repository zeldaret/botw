#include "gsys/gsysModelSceneConfig.h"
#include <agl/detail/aglPrivateResource.h>
#include <agl/env/aglFog.h>
#include <agl/env/aglLight.h>
#include <agl/env/aglProjector.h>
#include <agl/pfx/aglBloom.h>
#include <agl/pfx/aglDepthOfField.h>
#include <basis/seadRawPrint.h>
#include <prim/seadEnum.h>
#include "agl/fx/aglFxOfxLensFlare.h"
#include "gsys/gsysLightRigObj.h"
#include "gsys/gsysMaskedProjLight.h"
#include "gsys/gsysMaskedSpotLight.h"
#include "gsys/gsysORUtil.h"
#include "gsys/gsysOfxLensFlareRig.h"
#include "gsys/gsysPointLight.h"
#include "gsys/gsysSpotLight.h"

namespace gsys {

namespace {

SEAD_ENUM_EX(DepthFormat, Depth_32, Depth_16)
SEAD_ENUM_EX_VALUES(DepthFormat, 60, 59)

SEAD_ENUM_EX(DepthShadowMapFormat, R32_G32_float, R16_G16_float, R16_G16_uNorm, R8_G8_uNorm)
SEAD_ENUM_EX_VALUES(DepthShadowMapFormat, 38, 25, 21, 10)

}  // namespace

static sead::FixedSafeString<32> sDepthFormat32Str{DepthFormat(60).text()};

static sead::FixedSafeString<32> sDepthShadowMapFormat_R32_G32_float_Str{
    DepthShadowMapFormat(38).text()};

static const ModelSceneConfig::FeatureDescription sModelSceneFeatures[] = {
    {"LightMap", "light_map", false, false, true, "環境マップにライトを合成"},
    {"LightProbe", "light_probe", false, false, false, "静的なライトプローブ"},
    {"SnapShot", "snap_shot", false, false, false, "モデルのスナップショットを作成"},
    {"DepthShadow", "depth_shadow", false, false, false, "動的デプスシャドウ"},
    {"MaskedLight", "masked_light", false, false, false, "シャドウによってマスクされるライト"},
    {"StaticDepthShadow", "static_depth_shadow", false, false, false, "静的デプスシャドウ"},
    {"EnvCubeMap", "env_cube_map", false, false, true, "環境キューブマップ"},
    {"Reflection", "reflection", false, false, false, "平面的な反射"},
    {"LocalReflection", "local_reflection", false, false, false, "ローカルリフレクション"},
    {"Z-PrePass", "z_pre_pass", true, false, true, "Z値だけをを先に埋める"},
    {"Light-PrePass", "light_pre_pass", false, false, false,
     "Deferred Lighting用のライトバッファ生成"},
    {"ShadowPrePass", "shadow_pre_pass", false, false, false,
     "Deferred Shadowing用のシャドウバッファ生成"},
    {"Decal", "decal", false, false, false, "デカール"},
    {"NormalDrawer", "normal_drawer", false, false, false, "法線をモディファイしたり"},
    {"SSAO", "ssocclusion", false, false, false, "スクリーンスペースのアンビエントオクルージョン"},
    {"SSII", "ssii", false, false, false, "スクリーンスペースの間接光"},
    {"SSSSS", "sssss", false, false, false, "スクリーンスペースのサブサーフェススキャッタリング"},
    {"OcclusionQeuery", "occlusion_query", false, false, false, "遮蔽されているモデルをカリング"},
    {"DeferredShading", "deferred_opa_alphamask", false, false, false,
     "【モデル】不透明と抜き（デファード）"},
    {"Opaque + AlphaMask", "opa_alphamask", true, true, true, "【モデル】不透明と抜き"},
    {"OutlineSilhouette", "outline_silhouette", false, false, false,
     "【モデル】輪郭に沿ってアウトラインを描画"},
    {"DepthSilhouette", "depth_silhouette", true, true, true,
     "【モデル】遮蔽されたときのシルエット表示"},
    {"Xlu(Seal)", "xlu_seal", true, true, true, "【モデル】半透明（シールポリゴン）"},
    {"Cloud", "cloud", false, false, false, "プロシージャル雲"},
    {"VolumeMask", "volume_mask", false, false, false, "空間マスク"},
    {"Xlu(Water)", "xlu_water", true, true, true, "【モデル】半透明（水）"},
    {"Xlu", "xlu", true, true, true, "【モデル】半透明"},
    {"Xlu(Indirect)", "xlu_indirect", true, true, true, "【モデル】半透明（インダイレクト）"},
    {"Xlu(Fx)", "xlu_fx", true, true, true, "【モデル】半透明（特殊効果）"},
    {"ReducedBuffer", "reduced_buffer", true, true, true, "縮小バッファ"},
    {"ShadowMask", "shadow_mask", false, false, false,
     "画面の見せたい部分を残して他の部分を黒く覆ってくれる"},
    {"RadialBlur", "radial_blur", false, false, false, "空間に放射状のブラーエフェクトをおける"},
    {"DOF", "dof", false, false, true, "被写界深度"},
    {"Xlu Z-PrePass", "xlu_z_pre_pass", false, false, true, "【モデル】半透明Zプリパス"},
    {"Bloom", "bloom", false, false, true, "ブルーム効果"},
    {"GlareFilter", "glare_filter", false, false, false, "グレアフィルタ"},
    {"FlareFilter", "flare_filter", false, false, false,
     "フレアフィルタ（スクリーンスペースのレンズフレア）"},
    {"OccludedEffect", "occluded_effect", false, false, false, "遮蔽率をいい感じに使うエフェクト"},
    {"AutoExposure", "auto_exposure", false, false, false, "自動露出"},
    {"HDR", "hdr", false, false, true, "HDR解決(トーンマップ + sRGB変換)"},
    {"ColorCorrection", "color_correction", false, false, true, "カラーコレクション"},
    {"FilterAA", "filter_aa", false, false, true, "エイリアシングを除去"},
};

// NON_MATCHING: various issues, notably iterator stuff(?) for mDeferredShadingModels
ModelSceneConfig::ModelSceneConfig() {
    mEnvObjMgrInitArg.setContainMax(agl::env::AmbientLight::sTypeInfo->id, 5);
    mEnvObjMgrInitArg.setContainMax(agl::env::HemisphereLight::sTypeInfo->id, 10);
    mEnvObjMgrInitArg.setContainMax(agl::env::DirectionalLight::sTypeInfo->id, 30);
    mEnvObjMgrInitArg.setContainMax(agl::env::Projector::sTypeInfo->id, 10);
    mEnvObjMgrInitArg.setContainMax(agl::env::Fog::sTypeInfo->id, 10);
    mEnvObjMgrInitArg.setContainMax(agl::pfx::BloomObj::sTypeInfo->id, 10);
    mEnvObjMgrInitArg.setContainMax(agl::pfx::DepthOfFieldObj::sTypeInfo->id, 10);
    mEnvObjMgrInitArg.setContainMax(MaskedSpotLight::sTypeInfo->id, 13);
    mEnvObjBufferAllocateArg.setContainMax(agl::env::AmbientLight::sTypeInfo->id, 1);
    mEnvObjBufferAllocateArg.setContainMax(agl::env::HemisphereLight::sTypeInfo->id, 1);
    mEnvObjBufferAllocateArg.setContainMax(agl::env::DirectionalLight::sTypeInfo->id, 4);

    for (int i = 0; i < NumFeatures; ++i) {
        const FeatureDescription& info = sModelSceneFeatures[i];

        if (info._11)
            mEnabledFeatures[i].init(true, info.parameter_name, info.description, &_c0);
        else if (!info._10)
            mEnabledFeatures[i].init(false, info.parameter_name, info.description, &_c0);
        else
            mEnabledFeatures[i].init(false, info.parameter_name, info.description, this);

        if (info._10) {
            *mShouldCreateFeatures[i] = true;
        } else {
            mShouldCreateFeatures[i].init(
                info.should_create_by_default,
                sead::FormatFixedSafeString<64>("create_%s", info.parameter_name), info.description,
                this);
        }
    }

    mOpaPolygonOffset.init(-1.0, "opa_polygon_offset", "Opaポリゴンオフセット", this);
    mOpaPolygonScale.init(-1.0, "opa_polygon_scale", "Opaポリゴンスケール", this);

    mXluPolygonOffset.init(-2.5, "xlu_polygon_offset", "Xluポリゴンオフセット", this);
    mXluPolygonScale.init(-2.5, "xlu_polygon_scale", "Xluポリゴンスケール", this);

    mRevPolygonOffset.init(0.0, "rev_polygon_offset", "逆ポリゴンオフセット", this);
    mRevPolygonScale.init(0.0, "rev_polygon_scale", "逆ポリゴンスケール", this);

    {
        static constexpr sead::SafeArray<const char*, 3> names = {
            "lm_max_front_only",
            "lm_max_front_and_back",
            "lm_max_cube_map",
        };
        static constexpr sead::SafeArray<const char*, 3> labels = {
            "SphereFrontOnly",
            "SphereFrontAndBack",
            "CubeMap",
        };
        for (int i = 0; i < mLmMax.size(); ++i)
            mLmMax[i].init(i == 1 ? 12 : 0, names[i], labels[i], this);
    }

    mLightMapSizeSphere.init(0x30, "LightMapSizeSphere", "light_map_size_sphere", this);
    mLightMapCube.init(0x20, "LightMapCube", "light_map_size_cube", this);
    mLightMapAmbientLight.init(1, "LightMapAmbientLight", "アンビエントライト数", this);
    mLightMapHemiSphereLight.init(1, "LightMapHemiSphereLight", "半球ライト数", this);
    mLightMapDirectionalLight.init(4, "LightMapDirectionalLight", "ディレクショナルライト数", this);

    {
        static constexpr sead::SafeArray<const char*, 2> names = {
            "cube_map_max_tex_num",
            "cube_map_max_tex_width",
        };
        static constexpr sead::SafeArray<const char*, 2> labels = {
            "MaxTexNum",
            "CMaxTexWidth",
        };
        for (int i = 0; i < mCubeMapMaxTex.size(); ++i)
            mCubeMapMaxTex[i].init(i == 0 ? 10 : 256, names[i], labels[i], this);
    }

    mLightPrepassTextureHalf.init(false, "light_prepass_texture_half",
                                  "ライトプリパスの解像度を下げる", this);

    mUseDecalAo.init(false, "use_decal_ao", "デカールAO使用", this);
    mDecalAoObjectMax.init(0x20, "decal_ao_object_max", "デカールAOオブジェクト最大数", this);
    mDecalAoTextureMax.init(0x20, "decal_ao_texture_max", "デカールAOテクスチャ最大数", this);
    mDecalAoTextureWidth.init(0x100, "decal_ao_texture_width", "デカールAOテクスチャ幅", this);
    mDecalAoTextureHeight.init(0x100, "decal_ao_texture_height", "デカールAOテクスチャ高さ", this);
    mDecalAoTextureCannelNum.init(4, "decal_ao_texture_cannel_num",
                                  "デカールAOテクスチャチャンネル数", this);

    mUseDecalBuffer.init(false, "use_decal_buffer", "デカールバッファ使用", this);
    mUseDecalTrail.init(false, "use_decal_trail", "デカール軌跡使用", this);

    mBloomCorrectDepth.init(false, "bloom_correct_depth", "ブルームで正しいデプスを使う", this);

    mMaskedLightShadowOnly.init(false, "masked_light_shadow_only", "MaskedLightShadowのみをつかう",
                                this);

    mDepthShadowTexWidth.init(0x400, "depth_shadow_tex_width", "シャドウマップ幅", this);
    mDepthShadowTexHeight.init(-1, "depth_shadow_tex_height", "シャドウマップ高さ", this);
    mDepthShadowEnableBbClip.init(false, "depth_shadow_enable_bb_clip", "BoundingによるClip", this);
    mDepthShadowCheckOnly.init(false, "depth_shadow_check_only", "（初期化のみ使用）CheckOnly",
                               this);
    mDepthShadowMatrixViewCoordinate.init(false, "depth_shadow_matrix_view_coordinate",
                                          "ビュー座標系をシェーダに送る", this);
    mDepthShadowEnableHiZ.init(false, "depth_shadow_enable_hiz", "Hi-Z", this);
    mDepthShadowForceArray.init(false, "depth_shadow_force_array",
                                "（初期化のみ使用）強制でArrayにする", this);
    mDepthShadowNearFarMargin.init(0.0, "depth_shadow_near_far_margin",
                                   "（初期化のみ使用）撮影範囲マージン", this);
    mDepthShadowPolygonOffset.init(0.2, "depth_shadow_polygon_offset", "ポリゴンオフセット", this);
    mDepthShadowPolygonScale.init(2.7, "depth_shadow_polygon_scale", "ポリゴンスケール", this);

    mDepthShadowClipPlaneEnable.init(0, "depth_shadow_clip_plane_enable", "クリップ有効", this);
    for (int i = 0; i < mDepthShadowClipPlanes.size(); ++i) {
        mDepthShadowClipPlanes[i].init(
            sead::Vector4f::ey, sead::FormatFixedSafeString<64>("depth_shadow_clip_plane_%d", i),
            "clip_plane", this);
    }

    mDepthShadowExClipPlaneNum.init(0, "depth_shadow_ex_clip_plane_num", "拡張クリップ面の数",
                                    this);

    mDepthShadowPcfOffset.init(0.5, "depth_shadow_pcf_offset", "pcf_offset", this);

    for (int i = 0; i < mDepthShadowRefValueThresholds.size(); ++i) {
        mDepthShadowRefValueThresholds[i].init(
            -1.0, sead::FormatFixedSafeString<64>("depth_shadow_refvalue_threshold_%d", i), "",
            this);
    }

    mDepthShadowReleaseGbuffer.init(false, "depth_shadow_release_gbuffer",
                                    "G-Bufferを描き終えたら捨てる", this);

    for (int i = 0; i < mDepthShadowParams.size(); ++i) {
        auto& param = mDepthShadowParams[i];

        param.use_uniform_mtx.init(
            false, sead::FormatFixedSafeString<32>("depth_shadow_use_uniform_mtx_%d", i),
            "UniformMtx", this);

        param.cascade_num.init(1, sead::FormatFixedSafeString<32>("depth_shadow_cascade_num_%d", i),
                               "（初期化のみ使用）カスケード数", i == 0 ? this : &_c0);

        for (int j = 0; j < param.near.size(); ++j) {
            param.near[j].init(float(20 << j),
                               sead::FormatFixedSafeString<32>("depth_shadow_near_%d_%d", i, j), "",
                               this);
        }

        param.far.init(2000.0, sead::FormatFixedSafeString<32>("depth_shadow_far_%d", i),
                       "FrustumのFar", "Min=0", this);
        param.offset_near.init(0.0,
                               sead::FormatFixedSafeString<32>("depth_shadow_offset_near_%d", i),
                               "OptimaizeOffsetNear", "Min=0", this);
        param.offset_far.init(0.0, sead::FormatFixedSafeString<32>("depth_shadow_offset_far_%d", i),
                              "OptimizeOffsetFar", "Min=0", this);
    }

    mStaticSdwWidth.init(0x100, "static_sdw_width", "シャドウマップの幅", this);
    mStaticSdwDepthFormatName.init(sDepthFormat32Str, "static_sdw_depth_format_name",
                                   "デプスフォーマット", this);
    mStaticSdwShadowMapFormatName.init(sDepthShadowMapFormat_R32_G32_float_Str,
                                       "static_sdw_shadow_map_format_name",
                                       "シャドウマップフォーマット", this);

    mProjectionShadowNum.init(1, "projection_shadow_num", "投影影の数", this);
    mProjShadowMatrixViewCoordinate.init(false, "proj_shadow_matrix_view_coordinate",
                                         "ビュー座標系をシェーダに送る", this);

    mSsaoWidthScale.init(0.5, "ssao_width_scale", "SSAOバッファのスケール", this);
    mSsaoIsDepthFull.init(false, "ssao_is_depth_full", "SSAOのデプスをフル解像度", this);
    mLinearLightingEnable.init(false, "linear_lighting_enable", "リニアライティング有効", this);
    mHizExpandEnable.init(true, "hiz_expand_enable", "Hi-Z Expand有効", this);
    mNldEnable.init(true, "nld_enable", "NormalizedLinearDepth生成", this);
    mNld32Bit.init(false, "nld_32bit", "NormalizedLinearDepthを32bit", this);
    mNldHalf32Bit.init(false, "nld_half_32bit", "NormalizedLinearDepth(Half)を32bit", this);
    mDepthReduce.init(false, "depth_reduce", "デプスの縮小をmaxで計算", this);
    mZPrePassSelectable.init(false, "z_pre_pass_selectable", "Zプリパスを選択式にする", this);
    mDepthClear.init(true, "depth_clear", "Depth Clear有効", this);
    mIndirectBufferLDR.init(false, "indirect_buffer_LDR", "インダイレクトバッファLDR", this);

    mReducedBuffer16Bit.init(false, "reduced_buffer_16bit", "縮小バッファ16bit", this);
    mReducedBufferEdgeAdjustBake.init(false, "reduced_buffer_edge_adjust_bake",
                                      "縮小バッファエッジ補正をテクスチャ焼付け", this);
    mReducedBufferBlurAdjustBake.init(false, "reduced_buffer_blur_adjust_bake",
                                      "縮小バッファブラー補正をテクスチャ焼付け", this);
    mReducedBufferEdgeAdjust.init(false, "reduced_buffer_edge_adjust", "縮小バッファエッジ補正有効",
                                  this);
    mReducedBufferEdgeAdjustCoeff.init(2.0, "reduced_buffer_edge_adjust_coeff",
                                       "縮小バッファエッジ補正係数", this);

    mBaseResoWidth.init(0x500, "base_reso_width", "基準解像度の幅", this);
    mBaseResoHeight.init(0x2D0, "base_reso_height", "基準解像度の高さ", this);

    mGBufferAlbedoSrgb.init(false, "g_buffer_albedo_srgb", "GBufferのアルベドsRGB", this);
    mGBufferAlbedoReduceNearest.init(false, "g_buffer_albedo_reduce_nearest",
                                     "GBufferのアルベド縮小をポイントサンプル", this);

    mGBufferNormal8Bit.init(false, "g_buffer_normal_8bit", "GBufferのノーマル8bit", this);
    mGBufferNormalDisableReduce.init(false, "g_buffer_normal_disable_reduce", "GBufferの縮小停止",
                                     this);
    mGBufferNormalZSignW.init(false, "g_buffer_normal_z_sign_w",
                              "GBufferのノーマルのZを符号だけWに格納", this);
    mGBufferNormalReduceNearest.init(false, "g_buffer_normal_reduce_nearest",
                                     "GBufferのノーマル縮小をポイントサンプル", this);

    mGBufferDepth.init(false, "g_buffer_depth", "GBufferでマテリアルIDを使用", this);
    mGBufferMaterialIdFormat.init(0, "g_buffer_material_id_format", "マテリアルIDフォーマット",
                                  this);

    mGpuStressAnalyzerEnable.init(false, "gpu_stress_analyzer_enable", "GPU Stress Analyzer有効",
                                  this);
    mGpuStressAnalyzerReduceBufferenable.init(
        true, "gpu_stress_analyzer_reduce_bufferenable",
        "GPU Stress Analyzerでレンダーバッファのサイズを変える", this);

    mEnableDrcFilterAa.init(true, "enable_drc_filter_aa", "FilterAAが有効の時DRCも有効にする",
                            this);
    mInitFilterAaSmaaResTextures.init(false, "init_filter_aa_smaa_res_textures",
                                      "FilterAAの初期化時にSMAAのリソーステクスチャを生成する",
                                      this);

    mCubemapArray.init(true, "cubemap_array", "キューブマップを配列で扱う", this);
    mCubemapDynamicRange.init(1024.0, "cubemap_dynamic_range", "キューブマップのダイナミックレンジ",
                              this);
    mCubemapHdrComposePower.init(4.0, "cubemap_hdr_compose_power", "キューブマップの圧縮乗数",
                                 this);
    mCubemapMaxModelUnitNum.init(0x400, "cubemap_max_model_unit_num",
                                 "キューブマップの最大モデルユニット数", this);
    mCubemapMaxShapeNum.init(0x1000, "cubemap_max_shape_num", "キューブマップの最大シェイプ数",
                             this);
    mCubemapDisableEncode.init(false, "cubemap_disable_encode", "キューブマップを圧縮しない", this);

    mModelSceneEnvDataSetNum.init(1, "model_scene_env_data_set_num",
                                  "シーン環境で管理する genv の数", "Min=1, Max=4, Mode=MinMaxLock",
                                  this);

    mEnvObjPointLightNum.init(0x400, "env_obj_point_light_num", "ポイントライト数",
                              "Min=0 ,Max=1024", this);
    mEnvObjPointLightRigNum.init(0x80, "env_obj_point_light_rig_num", "ポイントライトリグ数",
                                 "Min=0 ,Max=1024", this);
    mEnvObjSpotLightNum.init(0x200, "env_obj_spot_light_num", "スポットライト数", "Min=0 ,Max=1024",
                             this);
    mEnvObjSpotLightRigNum.init(0x20, "env_obj_spot_light_rig_num", "スポットライトリグ数",
                                "Min=0 ,Max=1024", this);
    mEnvObjMaskedSpotLightNum.init(50, "env_obj_masked_spot_light_num", "マスクドライト数",
                                   "Min=0 ,Max=1024", this);
    mEnvObjMaskedSpotLightRigNum.init(5, "env_obj_masked_spot_light_rig_num",
                                      "マスクドライトリグ数", "Min=0 ,Max=1024", this);
    mEnvObjMaskedProjLightNum.init(3, "env_obj_masked_proj_light_num",
                                   "マスクドプロジェクションライト数", "Min=0 ,Max=1024", this);

    mOfxNumLensFlare.init(10, "ofx_num_lens_flare", "レンズフレア数", "Min=0,Max=32", this);
    mOfxNumLensFlarePreset.init(5, "ofx_num_lens_flare_preset", "レンズフレアPreset数",
                                "Min=0,Max=32", this);
    mOfxNumLensFlareDynamic.init(10, "ofx_num_lens_flare_dynamic", "プログラム用レンズフレア数",
                                 "Min=0,Max=32", this);
    mOfxNumLensFlareDynamicPreset.init(5, "ofx_num_lens_flare_dynamic_preset",
                                       "プログラム用レンズフレアPreset数", "Min=0,Max=32", this);
    mOfxNumLensFlareRig.init(8, "ofx_num_lens_flare_rig", "レンズフレアRig数", "Min=0,Max=32",
                             this);
    mOfxNumLensFlareRigObj.init(0x18, "ofx_num_lens_flare_rig_obj", "Rig用レンズフレア数",
                                "Min=0,Max=32", this);
    mOfxNumLensFlareRigPreset.init(5, "ofx_num_lens_flare_rig_preset", "Rig用レンズフレアPreset数",
                                   "Min=0,Max=32", this);
    mOfxNumLargeLensFlareRig.init(2, "ofx_num_large_lens_flare_rig", "LargeレンズフレアRig数",
                                  "Min=0,Max=16", this);
    mOfxNumLargeLensFlareRigObj.init(2, "ofx_num_large_lens_flare_rig_obj",
                                     "Rig用Largeレンズフレア数", "Min=0,Max=16", this);
    mOfxNumLargeLensFlareRigPreset.init(10, "ofx_num_large_lens_flare_rig_preset",
                                        "Rig用LargeレンズフレアPreset数", "Min=0,Max=16", this);

    mModelNum.init(0x2000, "model_num", "エントリーモデル数", "Min=0 ,Max=16000", this);
    mModelUnitNum.init(0x4000, "model_unit_num", "エントリーモデルユニット数", "Min=0 ,Max=16000",
                       this);
    mShapeNum.init(0x1000, "shape_num", "キューイングシェイプ数", "Min=0 ,Max=16000", this);
    mOcclusionQueryNum.init(0x100, "occlusion_query_num", "オクルージョンクエリ最大数",
                            "Min=0 ,Max=16000", this);

    for (int i = 0; i < mUserVisualizeClrNames.size(); ++i) {
        static constexpr sead::SafeArray<const char*, 8> names = {
            "user_visualize_clr_name_0", "user_visualize_clr_name_1", "user_visualize_clr_name_2",
            "user_visualize_clr_name_3", "user_visualize_clr_name_4", "user_visualize_clr_name_5",
            "user_visualize_clr_name_6", "user_visualize_clr_name_7",
        };
        static constexpr sead::SafeArray<const char*, 8> labels = {
            "ユーザーカラー可視化[0]", "ユーザーカラー可視化[1]", "ユーザーカラー可視化[2]",
            "ユーザーカラー可視化[3]", "ユーザーカラー可視化[4]", "ユーザーカラー可視化[5]",
            "ユーザーカラー可視化[6]", "ユーザーカラー可視化[7]",
        };
        mUserVisualizeClrNames[i].init(sead::SafeString::cEmptyString, names[i], labels[i],
                                       "AcceptReturn=true", this);
    }

    for (int i = 0; i < mUserVisualizeTexNames.size(); ++i) {
        static constexpr sead::SafeArray<const char*, 8> names = {
            "user_visualize_tex_name_0", "user_visualize_tex_name_1", "user_visualize_tex_name_2",
            "user_visualize_tex_name_3", "user_visualize_tex_name_4", "user_visualize_tex_name_5",
            "user_visualize_tex_name_6", "user_visualize_tex_name_7",
        };
        static constexpr sead::SafeArray<const char*, 8> labels = {
            "ユーザーテクスチャ可視化[0]", "ユーザーテクスチャ可視化[1]",
            "ユーザーテクスチャ可視化[2]", "ユーザーテクスチャ可視化[3]",
            "ユーザーテクスチャ可視化[4]", "ユーザーテクスチャ可視化[5]",
            "ユーザーテクスチャ可視化[6]", "ユーザーテクスチャ可視化[7]",
        };
        mUserVisualizeTexNames[i].init(sead::SafeString::cEmptyString, names[i], labels[i],
                                       "AcceptReturn=true", this);
    }

    for (auto it = mDeferredShadingModels.begin(), end = mDeferredShadingModels.end(); it != end;
         ++it) {
        auto i = int(-(&*mDeferredShadingModels.begin() - &*it));

        static constexpr sead::SafeArray<const char*, 8> labels = {
            "デファードシェーディング用モデル0", "デファードシェーディング用モデル1",
            "デファードシェーディング用モデル2", "デファードシェーディング用モデル3",
            "デファードシェーディング用モデル4", "デファードシェーディング用モデル5",
            "デファードシェーディング用モデル6", "デファードシェーディング用モデル7",
        };
        it->init(sead::SafeString::cEmptyString,
                 i == 0 ? sead::FormatFixedSafeString<256>("deferred_shading_model") :
                          sead::FormatFixedSafeString<256>("deferred_shading_model%d", i),
                 labels(i), "AcceptReturn=false", this);
    }

    mSceneMaterialModel.init(sead::SafeString::cEmptyString, "scene_material_model",
                             "シーンマテリアルモデル名", "AcceptReturn=false", this);

#ifdef SEAD_DEBUG
    setNodeName("コンフィグ");
#endif

    ORUtil::setNodeMetaIcon(this, ORUtil::Icon::_b,
                            agl::detail::PrivateResource::instance()->getDebugHeap());
}

int ModelSceneConfig::getStaticDepthShadowDepthFormat() const {
    return mStaticSdwDepthFormat;
}

int ModelSceneConfig::getStaticDepthShadowDepthShadowMapFormat() const {
    return mStaticSdwShadowMapFormat;
}

bool ModelSceneConfig::preRead_() {
    return !_1798 && !_1799;
}

bool ModelSceneConfig::preWrite_() const {
    mStaticSdwDepthFormatName->copy(DepthFormat(mStaticSdwDepthFormat).text());
    mStaticSdwShadowMapFormatName->copy(DepthShadowMapFormat(mStaticSdwShadowMapFormat).text());
    return true;
}

template <typename T>
static T convertToEnum(const sead::SafeString& str_value, T default_value) {
    T value;
    return value.fromText(str_value) ? value : default_value;
}

void ModelSceneConfig::postRead_() {
    _1799 = true;

    for (int i = 0; i < NumFeatures; ++i) {
        if (!sModelSceneFeatures[i]._10)
            *mEnabledFeatures[i] = *mShouldCreateFeatures[i];
    }

    mEnvObjMgrInitArg.setContainMax(LightRigObj<PointLight>::sTypeInfo, *mEnvObjPointLightNum);
    mEnvObjMgrInitArg.setContainMax(PointLightRig::sTypeInfo, *mEnvObjPointLightRigNum);

    mEnvObjMgrInitArg.setContainMax(LightRigObj<SpotLight>::sTypeInfo, *mEnvObjSpotLightNum);
    mEnvObjMgrInitArg.setContainMax(SpotLightRig::sTypeInfo, *mEnvObjSpotLightRigNum);

    mEnvObjMgrInitArg.setContainMax(LightRigObj<MaskedSpotLight>::sTypeInfo,
                                    *mEnvObjMaskedSpotLightNum);
    mEnvObjMgrInitArg.setContainMax(MaskedSpotLightRig::sTypeInfo, *mEnvObjMaskedSpotLightRigNum);

    mEnvObjMgrInitArg.setContainMax(MaskedProjLight::sTypeInfo, *mEnvObjMaskedProjLightNum);

    mEnvObjMgrInitArg.setContainMax(agl::fx::OfxLensFlare::sTypeInfo, *mOfxNumLensFlare);
    mEnvObjMgrInitArg.setContainMax(agl::fx::OfxLensFlare::Preset::sTypeInfo,
                                    *mOfxNumLensFlarePreset);

    mEnvObjMgrInitArg.setContainMax(agl::fx::OfxLensFlareDynamic::sTypeInfo,
                                    *mOfxNumLensFlareDynamic);
    mEnvObjMgrInitArg.setContainMax(agl::fx::OfxLensFlareDynamic::Preset::sTypeInfo,
                                    *mOfxNumLensFlareDynamicPreset);

    mEnvObjMgrInitArg.setContainMax(OfxLensFlareRig::sTypeInfo, *mOfxNumLensFlareRig);
    mEnvObjMgrInitArg.setContainMax(OfxLensFlareImpl::sTypeInfo, *mOfxNumLensFlareRigObj);
    mEnvObjMgrInitArg.setContainMax(OfxLensFlareImpl::Preset::sTypeInfo,
                                    *mOfxNumLensFlareRigPreset);

    mEnvObjMgrInitArg.setContainMax(OfxLargeLensFlareRig::sTypeInfo, *mOfxNumLargeLensFlareRig);
    mEnvObjMgrInitArg.setContainMax(OfxLargeLensFlareImpl::sTypeInfo, *mOfxNumLargeLensFlareRigObj);
    mEnvObjMgrInitArg.setContainMax(OfxLargeLensFlareImpl::Preset::sTypeInfo,
                                    *mOfxNumLargeLensFlareRigPreset);

    mEnvObjBufferAllocateArg.setContainMax(agl::env::AmbientLight::sTypeInfo,
                                           *mLightMapAmbientLight);
    mEnvObjBufferAllocateArg.setContainMax(agl::env::HemisphereLight::sTypeInfo,
                                           *mLightMapHemiSphereLight);
    mEnvObjBufferAllocateArg.setContainMax(agl::env::DirectionalLight::sTypeInfo,
                                           *mLightMapDirectionalLight);

    if (*mDepthShadowTexHeight < 1)
        *mDepthShadowTexHeight = *mDepthShadowTexWidth;

    mStaticSdwDepthFormat = convertToEnum<DepthFormat>(*mStaticSdwDepthFormatName, 60);
    mStaticSdwShadowMapFormat =
        convertToEnum<DepthShadowMapFormat>(*mStaticSdwShadowMapFormatName, 38);

    IParameterObj::postRead_();
}

ModelSceneConfig::EnvObjSetTemplate& ModelSceneConfig::getEnvObjSetTemplate_(int index) const {
    SEAD_ASSERT(mpConfigList != nullptr);
    return mpConfigList->mEnvObjSetTemplates[index];
}

ModelSceneConfig::EnvObjSetTemplate::EnvObjSetTemplate()
    : enable(false, "enable", "有効", this), num(8, "num", "Num", "Min=0,Max=16", this),
      ambient_light_num(1, "ambient_light_num", "Ambient Light Num", "Min=0,Max=8", this),
      directional_light_num(1, "directional_light_num", "Directional Light Num", "Min=0,Max=8",
                            this),
      hemisphere_light_num(1, "hemisphere_light_num", "Hemisphere Light Num", "Min=0,Max=8", this),
      fog_num(1, "fog_num", "Fog Num", "Min=0,Max=8", this),
      light_map_obj_num(1, "light_map_obj_num", "Light Map Obj Num", "Min=0,Max=8", this),
      template_name({"Tepmlate Name"} /* sic */, "template_name", "Template Name",
                    "Mode=TextBoxOnly, Comment=template_name, AcceptReturn=False", this) {}

ModelSceneConfigList::ModelSceneConfigList() : agl::utl::IParameterIO("gmsconf", 0) {
#ifdef SEAD_DEBUG
    setNodeName("シーンコンフィグ");
#endif
    ORUtil::setNodeMeta(this, ORUtil::Category::_0, ORUtil::Attribute::_2,
                        agl::detail::PrivateResource::instance()->getDebugHeap());

    addObj(&mNameArrayObj, "name_array");

    addList(&mEnvObjSetTemplateList, "env_obj_set_template");
    for (int i = 0; i < mEnvObjSetTemplates.size(); ++i) {
        mEnvObjSetTemplateList.addObj(&mEnvObjSetTemplates[i], sead::FormatFixedSafeString<32>(
                                                                   "env_obj_set_template_%02d", i));
    }
    *mEnvObjSetTemplates[0].enable = true;

    for (int i = 0; i < mConfigNames.size(); ++i) {
        const auto param = sead::FormatFixedSafeString<32>("config_%02d", i);
        const auto default_name = sead::FixedSafeString<32>("");
        mConfigNames[i].init(default_name, param, "コンフィグ名", &mNameArrayObj);
        mConfigs[i].mpConfigList = this;
    }
}

void ModelSceneConfigList::applyResouce(const void* resource) {
    mResource = resource;
    applyResParameterArchive(agl::utl::ResParameterArchive(resource));
}

const ModelSceneConfig& ModelSceneConfigList::setup(const sead::SafeString& config_name) {
    sead::SafeString name = &sead::SafeString::cNullChar;
    int index = 0;
    if (mCurrentConfigIndex != -1) {
        name = *mConfigNames[mCurrentConfigIndex];  // NOLINT(cppcoreguidelines-slicing)
        index = mCurrentConfigIndex;
    } else {
        for (int i = 0; i < mConfigs.size(); ++i) {
            if (*mConfigNames[i] == config_name) {
                name = *mConfigNames[i];  // NOLINT(cppcoreguidelines-slicing)
                index = i;
            }
        }
    }

    if (name.isEmpty()) {
        name = *mConfigNames[0];  // NOLINT(cppcoreguidelines-slicing)
        index = 0;
    }

    reload(name);
    return mConfigs[index];
}

void ModelSceneConfigList::reload(const sead::SafeString& config_name) {
    for (int i = 0; i < mConfigs.size(); ++i) {
        if (*mConfigNames[i] != "" && *mConfigNames[i] == config_name) {
            mConfigs[i]._1799 = false;
        }
    }

    applyResouce(mResource);
}

bool ModelSceneConfigList::preWrite_() const {
    // eww
    auto* mutable_this = const_cast<ModelSceneConfigList*>(this);

    mutable_this->clearObj();
    mutable_this->addObj(&mutable_this->mNameArrayObj, "name_array");

#ifdef SEAD_DEBUG
    for (int i = 0; i < mConfigs.size(); ++i) {
        if (!mConfigs[i].isAppended())
            mutable_this->addObj(&mutable_this->mConfigs[i], *mConfigNames[i]);
    }
#endif

    return true;
}

bool ModelSceneConfigList::preRead_() {
    if (_821e4) {
        clearObj();
        addObj(&mNameArrayObj, "name_array");
    }
    return true;
}

// NON_MATCHING: reordering fest
void ModelSceneConfigList::postRead_() {
    if (!_821e4) {
        _821e4 = true;
        // TODO: debug stuff
        // sead::hostio::InvalidateNode(this, true);
        return;
    }

    for (int i = 0; i < mConfigs.size(); ++i) {
        const auto& name = *mConfigNames[i];
        if (name == "")
            continue;

        addObj(&mConfigs[i], name);
        mConfigs[i].mIndex1 = i;
        mConfigs[i].mIndex2 = i;
        mConfigs[i].mConfigName = &name;
    }

    _821e4 = false;
    applyResouce(mResource);
}

ModelSceneConfigList::EnvObjSetTemplateList::EnvObjSetTemplateList() = default;

bool ModelSceneConfigList::EnvObjSetTemplateList::preRead_() {
    return !unk;
}

}  // namespace gsys
