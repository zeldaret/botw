#include "gsys/gsysParticleConfig.h"

#include "gsys/gsysORUtil.h"

namespace gsys {

ParticleConfig::ParticleConfig()
    : IParameterIO("ptclconf", 0),
      mGpuParticleHeapSize(0x100000, "gpu_particle_heap_size", "GpuParticleHeapSize", &mData2),
      mEffectModelHeapSize(0x20000, "EffectModelHeapSize", "effect_model_heap_size", &mData2),
      mPtclEmitCallbackHeapSize(0x10000, "ptcl_emit_callback_heap_size", "PtclEmitCallbackHeapSize",
                                &mData2),
      mEnableParticleLinearDepth(true, "enable_particle_lineardepth", "EnableParticleLinearDepth",
                                 &mData2),
      mEnableBatchProcessStreamOut(true, "enable_batck_process_streamout",
                                   "EnableBatchProcessStreamOut", &mData2),  // typo: batck
      mLightMapName0(sead::FixedSafeString<0x40>("Default"), "light_map_name_0", "ライトマップ0",
                     &mData2),
      mLightMapName1(sead::FixedSafeString<0x40>("Default"), "light_map_name_1", "ライトマップ1",
                     &mData2),
      mLightMapName2(sead::FixedSafeString<0x40>("Default"), "light_map_name_2", "ライトマップ2",
                     &mData2),
      mLightMapName3(sead::FixedSafeString<0x40>("Default"), "light_map_name_3", "ライトマップ3",
                     &mData2),
      mLightMapName4(sead::FixedSafeString<0x40>("Default"), "light_map_name_4", "ライトマップ4",
                     &mData2),
      mLightMapName5(sead::FixedSafeString<0x40>("Default"), "light_map_name_5", "ライトマップ5",
                     &mData2),
      mLightMapName6(sead::FixedSafeString<0x40>("Default"), "light_map_name_6", "ライトマップ6",
                     &mData2),
      mLightMapName7(sead::FixedSafeString<0x40>("Default"), "light_map_name_7", "ライトマップ7",
                     &mData2) {
    addObj(&mData2, "ParticleConfig");
}

const char* ParticleConfig::getLightMapName(unsigned int index) const {
    switch (index) {
    case 0:
        return mLightMapName0->cstr();
    case 1:
        return mLightMapName1->cstr();
    case 2:
        return mLightMapName2->cstr();
    case 3:
        return mLightMapName3->cstr();
    case 4:
        return mLightMapName4->cstr();
    case 5:
        return mLightMapName5->cstr();
    case 6:
        return mLightMapName6->cstr();
    case 7:
        return mLightMapName7->cstr();
    default:
        return "";
    }
}

void ParticleConfig::initialize(sead::Heap* heap, sead::Heap* hio_heap) {
    ORUtil::setNodeMetaIcon(this, ORUtil::Icon::_b, hio_heap);
}

void ParticleConfig::applyResouce(const void* data) {
    applyResParameterArchive(agl::utl::ResParameterArchive{data});
}

}  // namespace gsys
