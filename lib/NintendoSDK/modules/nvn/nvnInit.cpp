#include <nvn/nvn.h>

extern "C" {
void nvnLoadCProcs(const NVNdevice* device, nvnDeviceGetProcAddressFunction deviceGetProcAddress) {
    pfnc_nvnDeviceBuilderSetDefaults = (nvnDeviceBuilderSetDefaultsFunction)deviceGetProcAddress(
        device, "nvnDeviceBuilderSetDefaults");
    pfnc_nvnDeviceBuilderSetFlags =
        (nvnDeviceBuilderSetFlagsFunction)deviceGetProcAddress(device, "nvnDeviceBuilderSetFlags");
    pfnc_nvnDeviceInitialize =
        (nvnDeviceInitializeFunction)deviceGetProcAddress(device, "nvnDeviceInitialize");
    pfnc_nvnDeviceFinalize =
        (nvnDeviceFinalizeFunction)deviceGetProcAddress(device, "nvnDeviceFinalize");
    pfnc_nvnDeviceSetDebugLabel =
        (nvnDeviceSetDebugLabelFunction)deviceGetProcAddress(device, "nvnDeviceSetDebugLabel");
    pfnc_nvnDeviceGetProcAddress =
        (nvnDeviceGetProcAddressFunction)deviceGetProcAddress(device, "nvnDeviceGetProcAddress");
    pfnc_nvnDeviceGetInteger =
        (nvnDeviceGetIntegerFunction)deviceGetProcAddress(device, "nvnDeviceGetInteger");
    pfnc_nvnDeviceGetCurrentTimestampInNanoseconds =
        (nvnDeviceGetCurrentTimestampInNanosecondsFunction)deviceGetProcAddress(
            device, "nvnDeviceGetCurrentTimestampInNanoseconds");
    pfnc_nvnDeviceSetIntermediateShaderCache =
        (nvnDeviceSetIntermediateShaderCacheFunction)deviceGetProcAddress(
            device, "nvnDeviceSetIntermediateShaderCache");
    pfnc_nvnDeviceGetTextureHandle = (nvnDeviceGetTextureHandleFunction)deviceGetProcAddress(
        device, "nvnDeviceGetTextureHandle");
    pfnc_nvnDeviceGetTexelFetchHandle = (nvnDeviceGetTexelFetchHandleFunction)deviceGetProcAddress(
        device, "nvnDeviceGetTexelFetchHandle");
    pfnc_nvnDeviceGetImageHandle =
        (nvnDeviceGetImageHandleFunction)deviceGetProcAddress(device, "nvnDeviceGetImageHandle");
    pfnc_nvnDeviceInstallDebugCallback =
        (nvnDeviceInstallDebugCallbackFunction)deviceGetProcAddress(
            device, "nvnDeviceInstallDebugCallback");
    pfnc_nvnDeviceGenerateDebugDomainId =
        (nvnDeviceGenerateDebugDomainIdFunction)deviceGetProcAddress(
            device, "nvnDeviceGenerateDebugDomainId");
    pfnc_nvnDeviceSetWindowOriginMode = (nvnDeviceSetWindowOriginModeFunction)deviceGetProcAddress(
        device, "nvnDeviceSetWindowOriginMode");
    pfnc_nvnDeviceSetDepthMode =
        (nvnDeviceSetDepthModeFunction)deviceGetProcAddress(device, "nvnDeviceSetDepthMode");
    pfnc_nvnDeviceRegisterFastClearColor =
        (nvnDeviceRegisterFastClearColorFunction)deviceGetProcAddress(
            device, "nvnDeviceRegisterFastClearColor");
    pfnc_nvnDeviceRegisterFastClearColori =
        (nvnDeviceRegisterFastClearColoriFunction)deviceGetProcAddress(
            device, "nvnDeviceRegisterFastClearColori");
    pfnc_nvnDeviceRegisterFastClearColorui =
        (nvnDeviceRegisterFastClearColoruiFunction)deviceGetProcAddress(
            device, "nvnDeviceRegisterFastClearColorui");
    pfnc_nvnDeviceRegisterFastClearDepth =
        (nvnDeviceRegisterFastClearDepthFunction)deviceGetProcAddress(
            device, "nvnDeviceRegisterFastClearDepth");
    pfnc_nvnDeviceGetWindowOriginMode = (nvnDeviceGetWindowOriginModeFunction)deviceGetProcAddress(
        device, "nvnDeviceGetWindowOriginMode");
    pfnc_nvnDeviceGetDepthMode =
        (nvnDeviceGetDepthModeFunction)deviceGetProcAddress(device, "nvnDeviceGetDepthMode");
    pfnc_nvnDeviceGetTimestampInNanoseconds =
        (nvnDeviceGetTimestampInNanosecondsFunction)deviceGetProcAddress(
            device, "nvnDeviceGetTimestampInNanoseconds");
    pfnc_nvnDeviceApplyDeferredFinalizes =
        (nvnDeviceApplyDeferredFinalizesFunction)deviceGetProcAddress(
            device, "nvnDeviceApplyDeferredFinalizes");
    pfnc_nvnDeviceFinalizeCommandHandle =
        (nvnDeviceFinalizeCommandHandleFunction)deviceGetProcAddress(
            device, "nvnDeviceFinalizeCommandHandle");
    pfnc_nvnDeviceWalkDebugDatabase = (nvnDeviceWalkDebugDatabaseFunction)deviceGetProcAddress(
        device, "nvnDeviceWalkDebugDatabase");
    pfnc_nvnDeviceGetSeparateTextureHandle =
        (nvnDeviceGetSeparateTextureHandleFunction)deviceGetProcAddress(
            device, "nvnDeviceGetSeparateTextureHandle");
    pfnc_nvnDeviceGetSeparateSamplerHandle =
        (nvnDeviceGetSeparateSamplerHandleFunction)deviceGetProcAddress(
            device, "nvnDeviceGetSeparateSamplerHandle");
    pfnc_nvnDeviceIsExternalDebuggerAttached =
        (nvnDeviceIsExternalDebuggerAttachedFunction)deviceGetProcAddress(
            device, "nvnDeviceIsExternalDebuggerAttached");
    pfnc_nvnQueueGetError =
        (nvnQueueGetErrorFunction)deviceGetProcAddress(device, "nvnQueueGetError");
    pfnc_nvnQueueGetTotalCommandMemoryUsed =
        (nvnQueueGetTotalCommandMemoryUsedFunction)deviceGetProcAddress(
            device, "nvnQueueGetTotalCommandMemoryUsed");
    pfnc_nvnQueueGetTotalControlMemoryUsed =
        (nvnQueueGetTotalControlMemoryUsedFunction)deviceGetProcAddress(
            device, "nvnQueueGetTotalControlMemoryUsed");
    pfnc_nvnQueueGetTotalComputeMemoryUsed =
        (nvnQueueGetTotalComputeMemoryUsedFunction)deviceGetProcAddress(
            device, "nvnQueueGetTotalComputeMemoryUsed");
    pfnc_nvnQueueResetMemoryUsageCounts =
        (nvnQueueResetMemoryUsageCountsFunction)deviceGetProcAddress(
            device, "nvnQueueResetMemoryUsageCounts");
    pfnc_nvnQueueBuilderSetDevice =
        (nvnQueueBuilderSetDeviceFunction)deviceGetProcAddress(device, "nvnQueueBuilderSetDevice");
    pfnc_nvnQueueBuilderSetDefaults = (nvnQueueBuilderSetDefaultsFunction)deviceGetProcAddress(
        device, "nvnQueueBuilderSetDefaults");
    pfnc_nvnQueueBuilderSetFlags =
        (nvnQueueBuilderSetFlagsFunction)deviceGetProcAddress(device, "nvnQueueBuilderSetFlags");
    pfnc_nvnQueueBuilderSetCommandMemorySize =
        (nvnQueueBuilderSetCommandMemorySizeFunction)deviceGetProcAddress(
            device, "nvnQueueBuilderSetCommandMemorySize");
    pfnc_nvnQueueBuilderSetComputeMemorySize =
        (nvnQueueBuilderSetComputeMemorySizeFunction)deviceGetProcAddress(
            device, "nvnQueueBuilderSetComputeMemorySize");
    pfnc_nvnQueueBuilderSetControlMemorySize =
        (nvnQueueBuilderSetControlMemorySizeFunction)deviceGetProcAddress(
            device, "nvnQueueBuilderSetControlMemorySize");
    pfnc_nvnQueueBuilderGetQueueMemorySize =
        (nvnQueueBuilderGetQueueMemorySizeFunction)deviceGetProcAddress(
            device, "nvnQueueBuilderGetQueueMemorySize");
    pfnc_nvnQueueBuilderSetQueueMemory =
        (nvnQueueBuilderSetQueueMemoryFunction)deviceGetProcAddress(
            device, "nvnQueueBuilderSetQueueMemory");
    pfnc_nvnQueueBuilderSetCommandFlushThreshold =
        (nvnQueueBuilderSetCommandFlushThresholdFunction)deviceGetProcAddress(
            device, "nvnQueueBuilderSetCommandFlushThreshold");
    pfnc_nvnQueueInitialize =
        (nvnQueueInitializeFunction)deviceGetProcAddress(device, "nvnQueueInitialize");
    pfnc_nvnQueueFinalize =
        (nvnQueueFinalizeFunction)deviceGetProcAddress(device, "nvnQueueFinalize");
    pfnc_nvnQueueSetDebugLabel =
        (nvnQueueSetDebugLabelFunction)deviceGetProcAddress(device, "nvnQueueSetDebugLabel");
    pfnc_nvnQueueSubmitCommands =
        (nvnQueueSubmitCommandsFunction)deviceGetProcAddress(device, "nvnQueueSubmitCommands");
    pfnc_nvnQueueFlush = (nvnQueueFlushFunction)deviceGetProcAddress(device, "nvnQueueFlush");
    pfnc_nvnQueueFinish = (nvnQueueFinishFunction)deviceGetProcAddress(device, "nvnQueueFinish");
    pfnc_nvnQueuePresentTexture =
        (nvnQueuePresentTextureFunction)deviceGetProcAddress(device, "nvnQueuePresentTexture");
    pfnc_nvnQueueAcquireTexture =
        (nvnQueueAcquireTextureFunction)deviceGetProcAddress(device, "nvnQueueAcquireTexture");
    pfnc_nvnWindowBuilderSetDevice = (nvnWindowBuilderSetDeviceFunction)deviceGetProcAddress(
        device, "nvnWindowBuilderSetDevice");
    pfnc_nvnWindowBuilderSetDefaults = (nvnWindowBuilderSetDefaultsFunction)deviceGetProcAddress(
        device, "nvnWindowBuilderSetDefaults");
    pfnc_nvnWindowBuilderSetNativeWindow =
        (nvnWindowBuilderSetNativeWindowFunction)deviceGetProcAddress(
            device, "nvnWindowBuilderSetNativeWindow");
    pfnc_nvnWindowBuilderSetTextures = (nvnWindowBuilderSetTexturesFunction)deviceGetProcAddress(
        device, "nvnWindowBuilderSetTextures");
    pfnc_nvnWindowBuilderSetPresentInterval =
        (nvnWindowBuilderSetPresentIntervalFunction)deviceGetProcAddress(
            device, "nvnWindowBuilderSetPresentInterval");
    pfnc_nvnWindowBuilderGetNativeWindow =
        (nvnWindowBuilderGetNativeWindowFunction)deviceGetProcAddress(
            device, "nvnWindowBuilderGetNativeWindow");
    pfnc_nvnWindowBuilderGetPresentInterval =
        (nvnWindowBuilderGetPresentIntervalFunction)deviceGetProcAddress(
            device, "nvnWindowBuilderGetPresentInterval");
    pfnc_nvnWindowInitialize =
        (nvnWindowInitializeFunction)deviceGetProcAddress(device, "nvnWindowInitialize");
    pfnc_nvnWindowFinalize =
        (nvnWindowFinalizeFunction)deviceGetProcAddress(device, "nvnWindowFinalize");
    pfnc_nvnWindowSetDebugLabel =
        (nvnWindowSetDebugLabelFunction)deviceGetProcAddress(device, "nvnWindowSetDebugLabel");
    pfnc_nvnWindowAcquireTexture =
        (nvnWindowAcquireTextureFunction)deviceGetProcAddress(device, "nvnWindowAcquireTexture");
    pfnc_nvnWindowGetNativeWindow =
        (nvnWindowGetNativeWindowFunction)deviceGetProcAddress(device, "nvnWindowGetNativeWindow");
    pfnc_nvnWindowGetPresentInterval = (nvnWindowGetPresentIntervalFunction)deviceGetProcAddress(
        device, "nvnWindowGetPresentInterval");
    pfnc_nvnWindowSetPresentInterval = (nvnWindowSetPresentIntervalFunction)deviceGetProcAddress(
        device, "nvnWindowSetPresentInterval");
    pfnc_nvnWindowSetCrop =
        (nvnWindowSetCropFunction)deviceGetProcAddress(device, "nvnWindowSetCrop");
    pfnc_nvnWindowGetCrop =
        (nvnWindowGetCropFunction)deviceGetProcAddress(device, "nvnWindowGetCrop");
    pfnc_nvnProgramInitialize =
        (nvnProgramInitializeFunction)deviceGetProcAddress(device, "nvnProgramInitialize");
    pfnc_nvnProgramFinalize =
        (nvnProgramFinalizeFunction)deviceGetProcAddress(device, "nvnProgramFinalize");
    pfnc_nvnProgramSetDebugLabel =
        (nvnProgramSetDebugLabelFunction)deviceGetProcAddress(device, "nvnProgramSetDebugLabel");
    pfnc_nvnProgramSetShaders =
        (nvnProgramSetShadersFunction)deviceGetProcAddress(device, "nvnProgramSetShaders");
    pfnc_nvnMemoryPoolBuilderSetDevice =
        (nvnMemoryPoolBuilderSetDeviceFunction)deviceGetProcAddress(
            device, "nvnMemoryPoolBuilderSetDevice");
    pfnc_nvnMemoryPoolBuilderSetDefaults =
        (nvnMemoryPoolBuilderSetDefaultsFunction)deviceGetProcAddress(
            device, "nvnMemoryPoolBuilderSetDefaults");
    pfnc_nvnMemoryPoolBuilderSetStorage =
        (nvnMemoryPoolBuilderSetStorageFunction)deviceGetProcAddress(
            device, "nvnMemoryPoolBuilderSetStorage");
    pfnc_nvnMemoryPoolBuilderSetFlags = (nvnMemoryPoolBuilderSetFlagsFunction)deviceGetProcAddress(
        device, "nvnMemoryPoolBuilderSetFlags");
    pfnc_nvnMemoryPoolBuilderGetMemory =
        (nvnMemoryPoolBuilderGetMemoryFunction)deviceGetProcAddress(
            device, "nvnMemoryPoolBuilderGetMemory");
    pfnc_nvnMemoryPoolBuilderGetSize = (nvnMemoryPoolBuilderGetSizeFunction)deviceGetProcAddress(
        device, "nvnMemoryPoolBuilderGetSize");
    pfnc_nvnMemoryPoolBuilderGetFlags = (nvnMemoryPoolBuilderGetFlagsFunction)deviceGetProcAddress(
        device, "nvnMemoryPoolBuilderGetFlags");
    pfnc_nvnMemoryPoolInitialize =
        (nvnMemoryPoolInitializeFunction)deviceGetProcAddress(device, "nvnMemoryPoolInitialize");
    pfnc_nvnMemoryPoolSetDebugLabel = (nvnMemoryPoolSetDebugLabelFunction)deviceGetProcAddress(
        device, "nvnMemoryPoolSetDebugLabel");
    pfnc_nvnMemoryPoolFinalize =
        (nvnMemoryPoolFinalizeFunction)deviceGetProcAddress(device, "nvnMemoryPoolFinalize");
    pfnc_nvnMemoryPoolMap =
        (nvnMemoryPoolMapFunction)deviceGetProcAddress(device, "nvnMemoryPoolMap");
    pfnc_nvnMemoryPoolFlushMappedRange =
        (nvnMemoryPoolFlushMappedRangeFunction)deviceGetProcAddress(
            device, "nvnMemoryPoolFlushMappedRange");
    pfnc_nvnMemoryPoolInvalidateMappedRange =
        (nvnMemoryPoolInvalidateMappedRangeFunction)deviceGetProcAddress(
            device, "nvnMemoryPoolInvalidateMappedRange");
    pfnc_nvnMemoryPoolGetBufferAddress =
        (nvnMemoryPoolGetBufferAddressFunction)deviceGetProcAddress(
            device, "nvnMemoryPoolGetBufferAddress");
    pfnc_nvnMemoryPoolMapVirtual =
        (nvnMemoryPoolMapVirtualFunction)deviceGetProcAddress(device, "nvnMemoryPoolMapVirtual");
    pfnc_nvnMemoryPoolGetSize =
        (nvnMemoryPoolGetSizeFunction)deviceGetProcAddress(device, "nvnMemoryPoolGetSize");
    pfnc_nvnMemoryPoolGetFlags =
        (nvnMemoryPoolGetFlagsFunction)deviceGetProcAddress(device, "nvnMemoryPoolGetFlags");
    pfnc_nvnTexturePoolInitialize =
        (nvnTexturePoolInitializeFunction)deviceGetProcAddress(device, "nvnTexturePoolInitialize");
    pfnc_nvnTexturePoolSetDebugLabel = (nvnTexturePoolSetDebugLabelFunction)deviceGetProcAddress(
        device, "nvnTexturePoolSetDebugLabel");
    pfnc_nvnTexturePoolFinalize =
        (nvnTexturePoolFinalizeFunction)deviceGetProcAddress(device, "nvnTexturePoolFinalize");
    pfnc_nvnTexturePoolRegisterTexture =
        (nvnTexturePoolRegisterTextureFunction)deviceGetProcAddress(
            device, "nvnTexturePoolRegisterTexture");
    pfnc_nvnTexturePoolRegisterImage = (nvnTexturePoolRegisterImageFunction)deviceGetProcAddress(
        device, "nvnTexturePoolRegisterImage");
    pfnc_nvnTexturePoolGetMemoryPool = (nvnTexturePoolGetMemoryPoolFunction)deviceGetProcAddress(
        device, "nvnTexturePoolGetMemoryPool");
    pfnc_nvnTexturePoolGetMemoryOffset =
        (nvnTexturePoolGetMemoryOffsetFunction)deviceGetProcAddress(
            device, "nvnTexturePoolGetMemoryOffset");
    pfnc_nvnTexturePoolGetSize =
        (nvnTexturePoolGetSizeFunction)deviceGetProcAddress(device, "nvnTexturePoolGetSize");
    pfnc_nvnSamplerPoolInitialize =
        (nvnSamplerPoolInitializeFunction)deviceGetProcAddress(device, "nvnSamplerPoolInitialize");
    pfnc_nvnSamplerPoolSetDebugLabel = (nvnSamplerPoolSetDebugLabelFunction)deviceGetProcAddress(
        device, "nvnSamplerPoolSetDebugLabel");
    pfnc_nvnSamplerPoolFinalize =
        (nvnSamplerPoolFinalizeFunction)deviceGetProcAddress(device, "nvnSamplerPoolFinalize");
    pfnc_nvnSamplerPoolRegisterSampler =
        (nvnSamplerPoolRegisterSamplerFunction)deviceGetProcAddress(
            device, "nvnSamplerPoolRegisterSampler");
    pfnc_nvnSamplerPoolRegisterSamplerBuilder =
        (nvnSamplerPoolRegisterSamplerBuilderFunction)deviceGetProcAddress(
            device, "nvnSamplerPoolRegisterSamplerBuilder");
    pfnc_nvnSamplerPoolGetMemoryPool = (nvnSamplerPoolGetMemoryPoolFunction)deviceGetProcAddress(
        device, "nvnSamplerPoolGetMemoryPool");
    pfnc_nvnSamplerPoolGetMemoryOffset =
        (nvnSamplerPoolGetMemoryOffsetFunction)deviceGetProcAddress(
            device, "nvnSamplerPoolGetMemoryOffset");
    pfnc_nvnSamplerPoolGetSize =
        (nvnSamplerPoolGetSizeFunction)deviceGetProcAddress(device, "nvnSamplerPoolGetSize");
    pfnc_nvnBufferBuilderSetDevice = (nvnBufferBuilderSetDeviceFunction)deviceGetProcAddress(
        device, "nvnBufferBuilderSetDevice");
    pfnc_nvnBufferBuilderSetDefaults = (nvnBufferBuilderSetDefaultsFunction)deviceGetProcAddress(
        device, "nvnBufferBuilderSetDefaults");
    pfnc_nvnBufferBuilderSetStorage = (nvnBufferBuilderSetStorageFunction)deviceGetProcAddress(
        device, "nvnBufferBuilderSetStorage");
    pfnc_nvnBufferBuilderGetMemoryPool =
        (nvnBufferBuilderGetMemoryPoolFunction)deviceGetProcAddress(
            device, "nvnBufferBuilderGetMemoryPool");
    pfnc_nvnBufferBuilderGetMemoryOffset =
        (nvnBufferBuilderGetMemoryOffsetFunction)deviceGetProcAddress(
            device, "nvnBufferBuilderGetMemoryOffset");
    pfnc_nvnBufferBuilderGetSize =
        (nvnBufferBuilderGetSizeFunction)deviceGetProcAddress(device, "nvnBufferBuilderGetSize");
    pfnc_nvnBufferInitialize =
        (nvnBufferInitializeFunction)deviceGetProcAddress(device, "nvnBufferInitialize");
    pfnc_nvnBufferSetDebugLabel =
        (nvnBufferSetDebugLabelFunction)deviceGetProcAddress(device, "nvnBufferSetDebugLabel");
    pfnc_nvnBufferFinalize =
        (nvnBufferFinalizeFunction)deviceGetProcAddress(device, "nvnBufferFinalize");
    pfnc_nvnBufferMap = (nvnBufferMapFunction)deviceGetProcAddress(device, "nvnBufferMap");
    pfnc_nvnBufferGetAddress =
        (nvnBufferGetAddressFunction)deviceGetProcAddress(device, "nvnBufferGetAddress");
    pfnc_nvnBufferFlushMappedRange = (nvnBufferFlushMappedRangeFunction)deviceGetProcAddress(
        device, "nvnBufferFlushMappedRange");
    pfnc_nvnBufferInvalidateMappedRange =
        (nvnBufferInvalidateMappedRangeFunction)deviceGetProcAddress(
            device, "nvnBufferInvalidateMappedRange");
    pfnc_nvnBufferGetMemoryPool =
        (nvnBufferGetMemoryPoolFunction)deviceGetProcAddress(device, "nvnBufferGetMemoryPool");
    pfnc_nvnBufferGetMemoryOffset =
        (nvnBufferGetMemoryOffsetFunction)deviceGetProcAddress(device, "nvnBufferGetMemoryOffset");
    pfnc_nvnBufferGetSize =
        (nvnBufferGetSizeFunction)deviceGetProcAddress(device, "nvnBufferGetSize");
    pfnc_nvnBufferGetDebugID =
        (nvnBufferGetDebugIDFunction)deviceGetProcAddress(device, "nvnBufferGetDebugID");
    pfnc_nvnTextureBuilderSetDevice = (nvnTextureBuilderSetDeviceFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetDevice");
    pfnc_nvnTextureBuilderSetDefaults = (nvnTextureBuilderSetDefaultsFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetDefaults");
    pfnc_nvnTextureBuilderSetFlags = (nvnTextureBuilderSetFlagsFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetFlags");
    pfnc_nvnTextureBuilderSetTarget = (nvnTextureBuilderSetTargetFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetTarget");
    pfnc_nvnTextureBuilderSetWidth = (nvnTextureBuilderSetWidthFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetWidth");
    pfnc_nvnTextureBuilderSetHeight = (nvnTextureBuilderSetHeightFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetHeight");
    pfnc_nvnTextureBuilderSetDepth = (nvnTextureBuilderSetDepthFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetDepth");
    pfnc_nvnTextureBuilderSetSize1D = (nvnTextureBuilderSetSize1DFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetSize1D");
    pfnc_nvnTextureBuilderSetSize2D = (nvnTextureBuilderSetSize2DFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetSize2D");
    pfnc_nvnTextureBuilderSetSize3D = (nvnTextureBuilderSetSize3DFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetSize3D");
    pfnc_nvnTextureBuilderSetLevels = (nvnTextureBuilderSetLevelsFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetLevels");
    pfnc_nvnTextureBuilderSetFormat = (nvnTextureBuilderSetFormatFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetFormat");
    pfnc_nvnTextureBuilderSetSamples = (nvnTextureBuilderSetSamplesFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetSamples");
    pfnc_nvnTextureBuilderSetSwizzle = (nvnTextureBuilderSetSwizzleFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetSwizzle");
    pfnc_nvnTextureBuilderSetDepthStencilMode =
        (nvnTextureBuilderSetDepthStencilModeFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderSetDepthStencilMode");
    pfnc_nvnTextureBuilderGetStorageSize =
        (nvnTextureBuilderGetStorageSizeFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetStorageSize");
    pfnc_nvnTextureBuilderGetStorageAlignment =
        (nvnTextureBuilderGetStorageAlignmentFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetStorageAlignment");
    pfnc_nvnTextureBuilderSetStorage = (nvnTextureBuilderSetStorageFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetStorage");
    pfnc_nvnTextureBuilderSetPackagedTextureData =
        (nvnTextureBuilderSetPackagedTextureDataFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderSetPackagedTextureData");
    pfnc_nvnTextureBuilderSetPackagedTextureLayout =
        (nvnTextureBuilderSetPackagedTextureLayoutFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderSetPackagedTextureLayout");
    pfnc_nvnTextureBuilderSetStride = (nvnTextureBuilderSetStrideFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderSetStride");
    pfnc_nvnTextureBuilderSetGLTextureName =
        (nvnTextureBuilderSetGLTextureNameFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderSetGLTextureName");
    pfnc_nvnTextureBuilderGetStorageClass =
        (nvnTextureBuilderGetStorageClassFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetStorageClass");
    pfnc_nvnTextureBuilderGetFlags = (nvnTextureBuilderGetFlagsFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetFlags");
    pfnc_nvnTextureBuilderGetTarget = (nvnTextureBuilderGetTargetFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetTarget");
    pfnc_nvnTextureBuilderGetWidth = (nvnTextureBuilderGetWidthFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetWidth");
    pfnc_nvnTextureBuilderGetHeight = (nvnTextureBuilderGetHeightFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetHeight");
    pfnc_nvnTextureBuilderGetDepth = (nvnTextureBuilderGetDepthFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetDepth");
    pfnc_nvnTextureBuilderGetLevels = (nvnTextureBuilderGetLevelsFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetLevels");
    pfnc_nvnTextureBuilderGetFormat = (nvnTextureBuilderGetFormatFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetFormat");
    pfnc_nvnTextureBuilderGetSamples = (nvnTextureBuilderGetSamplesFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetSamples");
    pfnc_nvnTextureBuilderGetSwizzle = (nvnTextureBuilderGetSwizzleFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetSwizzle");
    pfnc_nvnTextureBuilderGetDepthStencilMode =
        (nvnTextureBuilderGetDepthStencilModeFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetDepthStencilMode");
    pfnc_nvnTextureBuilderGetPackagedTextureData =
        (nvnTextureBuilderGetPackagedTextureDataFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetPackagedTextureData");
    pfnc_nvnTextureBuilderGetStride = (nvnTextureBuilderGetStrideFunction)deviceGetProcAddress(
        device, "nvnTextureBuilderGetStride");
    pfnc_nvnTextureBuilderGetSparseTileLayout =
        (nvnTextureBuilderGetSparseTileLayoutFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetSparseTileLayout");
    pfnc_nvnTextureBuilderGetGLTextureName =
        (nvnTextureBuilderGetGLTextureNameFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetGLTextureName");
    pfnc_nvnTextureBuilderGetZCullStorageSize =
        (nvnTextureBuilderGetZCullStorageSizeFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetZCullStorageSize");
    pfnc_nvnTextureBuilderGetMemoryPool =
        (nvnTextureBuilderGetMemoryPoolFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetMemoryPool");
    pfnc_nvnTextureBuilderGetMemoryOffset =
        (nvnTextureBuilderGetMemoryOffsetFunction)deviceGetProcAddress(
            device, "nvnTextureBuilderGetMemoryOffset");
    pfnc_nvnTextureViewSetDefaults = (nvnTextureViewSetDefaultsFunction)deviceGetProcAddress(
        device, "nvnTextureViewSetDefaults");
    pfnc_nvnTextureViewSetLevels =
        (nvnTextureViewSetLevelsFunction)deviceGetProcAddress(device, "nvnTextureViewSetLevels");
    pfnc_nvnTextureViewSetLayers =
        (nvnTextureViewSetLayersFunction)deviceGetProcAddress(device, "nvnTextureViewSetLayers");
    pfnc_nvnTextureViewSetFormat =
        (nvnTextureViewSetFormatFunction)deviceGetProcAddress(device, "nvnTextureViewSetFormat");
    pfnc_nvnTextureViewSetSwizzle =
        (nvnTextureViewSetSwizzleFunction)deviceGetProcAddress(device, "nvnTextureViewSetSwizzle");
    pfnc_nvnTextureViewSetDepthStencilMode =
        (nvnTextureViewSetDepthStencilModeFunction)deviceGetProcAddress(
            device, "nvnTextureViewSetDepthStencilMode");
    pfnc_nvnTextureViewSetTarget =
        (nvnTextureViewSetTargetFunction)deviceGetProcAddress(device, "nvnTextureViewSetTarget");
    pfnc_nvnTextureViewGetLevels =
        (nvnTextureViewGetLevelsFunction)deviceGetProcAddress(device, "nvnTextureViewGetLevels");
    pfnc_nvnTextureViewGetLayers =
        (nvnTextureViewGetLayersFunction)deviceGetProcAddress(device, "nvnTextureViewGetLayers");
    pfnc_nvnTextureViewGetFormat =
        (nvnTextureViewGetFormatFunction)deviceGetProcAddress(device, "nvnTextureViewGetFormat");
    pfnc_nvnTextureViewGetSwizzle =
        (nvnTextureViewGetSwizzleFunction)deviceGetProcAddress(device, "nvnTextureViewGetSwizzle");
    pfnc_nvnTextureViewGetDepthStencilMode =
        (nvnTextureViewGetDepthStencilModeFunction)deviceGetProcAddress(
            device, "nvnTextureViewGetDepthStencilMode");
    pfnc_nvnTextureViewGetTarget =
        (nvnTextureViewGetTargetFunction)deviceGetProcAddress(device, "nvnTextureViewGetTarget");
    pfnc_nvnTextureViewCompare =
        (nvnTextureViewCompareFunction)deviceGetProcAddress(device, "nvnTextureViewCompare");
    pfnc_nvnTextureInitialize =
        (nvnTextureInitializeFunction)deviceGetProcAddress(device, "nvnTextureInitialize");
    pfnc_nvnTextureGetZCullStorageSize =
        (nvnTextureGetZCullStorageSizeFunction)deviceGetProcAddress(
            device, "nvnTextureGetZCullStorageSize");
    pfnc_nvnTextureFinalize =
        (nvnTextureFinalizeFunction)deviceGetProcAddress(device, "nvnTextureFinalize");
    pfnc_nvnTextureSetDebugLabel =
        (nvnTextureSetDebugLabelFunction)deviceGetProcAddress(device, "nvnTextureSetDebugLabel");
    pfnc_nvnTextureGetStorageClass = (nvnTextureGetStorageClassFunction)deviceGetProcAddress(
        device, "nvnTextureGetStorageClass");
    pfnc_nvnTextureGetViewOffset =
        (nvnTextureGetViewOffsetFunction)deviceGetProcAddress(device, "nvnTextureGetViewOffset");
    pfnc_nvnTextureGetFlags =
        (nvnTextureGetFlagsFunction)deviceGetProcAddress(device, "nvnTextureGetFlags");
    pfnc_nvnTextureGetTarget =
        (nvnTextureGetTargetFunction)deviceGetProcAddress(device, "nvnTextureGetTarget");
    pfnc_nvnTextureGetWidth =
        (nvnTextureGetWidthFunction)deviceGetProcAddress(device, "nvnTextureGetWidth");
    pfnc_nvnTextureGetHeight =
        (nvnTextureGetHeightFunction)deviceGetProcAddress(device, "nvnTextureGetHeight");
    pfnc_nvnTextureGetDepth =
        (nvnTextureGetDepthFunction)deviceGetProcAddress(device, "nvnTextureGetDepth");
    pfnc_nvnTextureGetLevels =
        (nvnTextureGetLevelsFunction)deviceGetProcAddress(device, "nvnTextureGetLevels");
    pfnc_nvnTextureGetFormat =
        (nvnTextureGetFormatFunction)deviceGetProcAddress(device, "nvnTextureGetFormat");
    pfnc_nvnTextureGetSamples =
        (nvnTextureGetSamplesFunction)deviceGetProcAddress(device, "nvnTextureGetSamples");
    pfnc_nvnTextureGetSwizzle =
        (nvnTextureGetSwizzleFunction)deviceGetProcAddress(device, "nvnTextureGetSwizzle");
    pfnc_nvnTextureGetDepthStencilMode =
        (nvnTextureGetDepthStencilModeFunction)deviceGetProcAddress(
            device, "nvnTextureGetDepthStencilMode");
    pfnc_nvnTextureGetStride =
        (nvnTextureGetStrideFunction)deviceGetProcAddress(device, "nvnTextureGetStride");
    pfnc_nvnTextureGetTextureAddress = (nvnTextureGetTextureAddressFunction)deviceGetProcAddress(
        device, "nvnTextureGetTextureAddress");
    pfnc_nvnTextureGetSparseTileLayout =
        (nvnTextureGetSparseTileLayoutFunction)deviceGetProcAddress(
            device, "nvnTextureGetSparseTileLayout");
    pfnc_nvnTextureWriteTexels =
        (nvnTextureWriteTexelsFunction)deviceGetProcAddress(device, "nvnTextureWriteTexels");
    pfnc_nvnTextureWriteTexelsStrided = (nvnTextureWriteTexelsStridedFunction)deviceGetProcAddress(
        device, "nvnTextureWriteTexelsStrided");
    pfnc_nvnTextureReadTexels =
        (nvnTextureReadTexelsFunction)deviceGetProcAddress(device, "nvnTextureReadTexels");
    pfnc_nvnTextureReadTexelsStrided = (nvnTextureReadTexelsStridedFunction)deviceGetProcAddress(
        device, "nvnTextureReadTexelsStrided");
    pfnc_nvnTextureFlushTexels =
        (nvnTextureFlushTexelsFunction)deviceGetProcAddress(device, "nvnTextureFlushTexels");
    pfnc_nvnTextureInvalidateTexels = (nvnTextureInvalidateTexelsFunction)deviceGetProcAddress(
        device, "nvnTextureInvalidateTexels");
    pfnc_nvnTextureGetMemoryPool =
        (nvnTextureGetMemoryPoolFunction)deviceGetProcAddress(device, "nvnTextureGetMemoryPool");
    pfnc_nvnTextureGetMemoryOffset = (nvnTextureGetMemoryOffsetFunction)deviceGetProcAddress(
        device, "nvnTextureGetMemoryOffset");
    pfnc_nvnTextureGetStorageSize =
        (nvnTextureGetStorageSizeFunction)deviceGetProcAddress(device, "nvnTextureGetStorageSize");
    pfnc_nvnTextureCompare =
        (nvnTextureCompareFunction)deviceGetProcAddress(device, "nvnTextureCompare");
    pfnc_nvnTextureGetDebugID =
        (nvnTextureGetDebugIDFunction)deviceGetProcAddress(device, "nvnTextureGetDebugID");
    pfnc_nvnSamplerBuilderSetDevice = (nvnSamplerBuilderSetDeviceFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderSetDevice");
    pfnc_nvnSamplerBuilderSetDefaults = (nvnSamplerBuilderSetDefaultsFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderSetDefaults");
    pfnc_nvnSamplerBuilderSetMinMagFilter =
        (nvnSamplerBuilderSetMinMagFilterFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderSetMinMagFilter");
    pfnc_nvnSamplerBuilderSetWrapMode = (nvnSamplerBuilderSetWrapModeFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderSetWrapMode");
    pfnc_nvnSamplerBuilderSetLodClamp = (nvnSamplerBuilderSetLodClampFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderSetLodClamp");
    pfnc_nvnSamplerBuilderSetLodBias = (nvnSamplerBuilderSetLodBiasFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderSetLodBias");
    pfnc_nvnSamplerBuilderSetCompare = (nvnSamplerBuilderSetCompareFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderSetCompare");
    pfnc_nvnSamplerBuilderSetBorderColor =
        (nvnSamplerBuilderSetBorderColorFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderSetBorderColor");
    pfnc_nvnSamplerBuilderSetBorderColori =
        (nvnSamplerBuilderSetBorderColoriFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderSetBorderColori");
    pfnc_nvnSamplerBuilderSetBorderColorui =
        (nvnSamplerBuilderSetBorderColoruiFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderSetBorderColorui");
    pfnc_nvnSamplerBuilderSetMaxAnisotropy =
        (nvnSamplerBuilderSetMaxAnisotropyFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderSetMaxAnisotropy");
    pfnc_nvnSamplerBuilderSetReductionFilter =
        (nvnSamplerBuilderSetReductionFilterFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderSetReductionFilter");
    pfnc_nvnSamplerBuilderSetLodSnap = (nvnSamplerBuilderSetLodSnapFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderSetLodSnap");
    pfnc_nvnSamplerBuilderGetMinMagFilter =
        (nvnSamplerBuilderGetMinMagFilterFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderGetMinMagFilter");
    pfnc_nvnSamplerBuilderGetWrapMode = (nvnSamplerBuilderGetWrapModeFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderGetWrapMode");
    pfnc_nvnSamplerBuilderGetLodClamp = (nvnSamplerBuilderGetLodClampFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderGetLodClamp");
    pfnc_nvnSamplerBuilderGetLodBias = (nvnSamplerBuilderGetLodBiasFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderGetLodBias");
    pfnc_nvnSamplerBuilderGetCompare = (nvnSamplerBuilderGetCompareFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderGetCompare");
    pfnc_nvnSamplerBuilderGetBorderColor =
        (nvnSamplerBuilderGetBorderColorFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderGetBorderColor");
    pfnc_nvnSamplerBuilderGetBorderColori =
        (nvnSamplerBuilderGetBorderColoriFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderGetBorderColori");
    pfnc_nvnSamplerBuilderGetBorderColorui =
        (nvnSamplerBuilderGetBorderColoruiFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderGetBorderColorui");
    pfnc_nvnSamplerBuilderGetMaxAnisotropy =
        (nvnSamplerBuilderGetMaxAnisotropyFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderGetMaxAnisotropy");
    pfnc_nvnSamplerBuilderGetReductionFilter =
        (nvnSamplerBuilderGetReductionFilterFunction)deviceGetProcAddress(
            device, "nvnSamplerBuilderGetReductionFilter");
    pfnc_nvnSamplerBuilderGetLodSnap = (nvnSamplerBuilderGetLodSnapFunction)deviceGetProcAddress(
        device, "nvnSamplerBuilderGetLodSnap");
    pfnc_nvnSamplerInitialize =
        (nvnSamplerInitializeFunction)deviceGetProcAddress(device, "nvnSamplerInitialize");
    pfnc_nvnSamplerFinalize =
        (nvnSamplerFinalizeFunction)deviceGetProcAddress(device, "nvnSamplerFinalize");
    pfnc_nvnSamplerSetDebugLabel =
        (nvnSamplerSetDebugLabelFunction)deviceGetProcAddress(device, "nvnSamplerSetDebugLabel");
    pfnc_nvnSamplerGetMinMagFilter = (nvnSamplerGetMinMagFilterFunction)deviceGetProcAddress(
        device, "nvnSamplerGetMinMagFilter");
    pfnc_nvnSamplerGetWrapMode =
        (nvnSamplerGetWrapModeFunction)deviceGetProcAddress(device, "nvnSamplerGetWrapMode");
    pfnc_nvnSamplerGetLodClamp =
        (nvnSamplerGetLodClampFunction)deviceGetProcAddress(device, "nvnSamplerGetLodClamp");
    pfnc_nvnSamplerGetLodBias =
        (nvnSamplerGetLodBiasFunction)deviceGetProcAddress(device, "nvnSamplerGetLodBias");
    pfnc_nvnSamplerGetCompare =
        (nvnSamplerGetCompareFunction)deviceGetProcAddress(device, "nvnSamplerGetCompare");
    pfnc_nvnSamplerGetBorderColor =
        (nvnSamplerGetBorderColorFunction)deviceGetProcAddress(device, "nvnSamplerGetBorderColor");
    pfnc_nvnSamplerGetBorderColori = (nvnSamplerGetBorderColoriFunction)deviceGetProcAddress(
        device, "nvnSamplerGetBorderColori");
    pfnc_nvnSamplerGetBorderColorui = (nvnSamplerGetBorderColoruiFunction)deviceGetProcAddress(
        device, "nvnSamplerGetBorderColorui");
    pfnc_nvnSamplerGetMaxAnisotropy = (nvnSamplerGetMaxAnisotropyFunction)deviceGetProcAddress(
        device, "nvnSamplerGetMaxAnisotropy");
    pfnc_nvnSamplerGetReductionFilter = (nvnSamplerGetReductionFilterFunction)deviceGetProcAddress(
        device, "nvnSamplerGetReductionFilter");
    pfnc_nvnSamplerCompare =
        (nvnSamplerCompareFunction)deviceGetProcAddress(device, "nvnSamplerCompare");
    pfnc_nvnSamplerGetDebugID =
        (nvnSamplerGetDebugIDFunction)deviceGetProcAddress(device, "nvnSamplerGetDebugID");
    pfnc_nvnBlendStateSetDefaults =
        (nvnBlendStateSetDefaultsFunction)deviceGetProcAddress(device, "nvnBlendStateSetDefaults");
    pfnc_nvnBlendStateSetBlendTarget = (nvnBlendStateSetBlendTargetFunction)deviceGetProcAddress(
        device, "nvnBlendStateSetBlendTarget");
    pfnc_nvnBlendStateSetBlendFunc = (nvnBlendStateSetBlendFuncFunction)deviceGetProcAddress(
        device, "nvnBlendStateSetBlendFunc");
    pfnc_nvnBlendStateSetBlendEquation =
        (nvnBlendStateSetBlendEquationFunction)deviceGetProcAddress(
            device, "nvnBlendStateSetBlendEquation");
    pfnc_nvnBlendStateSetAdvancedMode = (nvnBlendStateSetAdvancedModeFunction)deviceGetProcAddress(
        device, "nvnBlendStateSetAdvancedMode");
    pfnc_nvnBlendStateSetAdvancedOverlap =
        (nvnBlendStateSetAdvancedOverlapFunction)deviceGetProcAddress(
            device, "nvnBlendStateSetAdvancedOverlap");
    pfnc_nvnBlendStateSetAdvancedPremultipliedSrc =
        (nvnBlendStateSetAdvancedPremultipliedSrcFunction)deviceGetProcAddress(
            device, "nvnBlendStateSetAdvancedPremultipliedSrc");
    pfnc_nvnBlendStateSetAdvancedNormalizedDst =
        (nvnBlendStateSetAdvancedNormalizedDstFunction)deviceGetProcAddress(
            device, "nvnBlendStateSetAdvancedNormalizedDst");
    pfnc_nvnBlendStateGetBlendTarget = (nvnBlendStateGetBlendTargetFunction)deviceGetProcAddress(
        device, "nvnBlendStateGetBlendTarget");
    pfnc_nvnBlendStateGetBlendFunc = (nvnBlendStateGetBlendFuncFunction)deviceGetProcAddress(
        device, "nvnBlendStateGetBlendFunc");
    pfnc_nvnBlendStateGetBlendEquation =
        (nvnBlendStateGetBlendEquationFunction)deviceGetProcAddress(
            device, "nvnBlendStateGetBlendEquation");
    pfnc_nvnBlendStateGetAdvancedMode = (nvnBlendStateGetAdvancedModeFunction)deviceGetProcAddress(
        device, "nvnBlendStateGetAdvancedMode");
    pfnc_nvnBlendStateGetAdvancedOverlap =
        (nvnBlendStateGetAdvancedOverlapFunction)deviceGetProcAddress(
            device, "nvnBlendStateGetAdvancedOverlap");
    pfnc_nvnBlendStateGetAdvancedPremultipliedSrc =
        (nvnBlendStateGetAdvancedPremultipliedSrcFunction)deviceGetProcAddress(
            device, "nvnBlendStateGetAdvancedPremultipliedSrc");
    pfnc_nvnBlendStateGetAdvancedNormalizedDst =
        (nvnBlendStateGetAdvancedNormalizedDstFunction)deviceGetProcAddress(
            device, "nvnBlendStateGetAdvancedNormalizedDst");
    pfnc_nvnColorStateSetDefaults =
        (nvnColorStateSetDefaultsFunction)deviceGetProcAddress(device, "nvnColorStateSetDefaults");
    pfnc_nvnColorStateSetBlendEnable = (nvnColorStateSetBlendEnableFunction)deviceGetProcAddress(
        device, "nvnColorStateSetBlendEnable");
    pfnc_nvnColorStateSetLogicOp =
        (nvnColorStateSetLogicOpFunction)deviceGetProcAddress(device, "nvnColorStateSetLogicOp");
    pfnc_nvnColorStateSetAlphaTest = (nvnColorStateSetAlphaTestFunction)deviceGetProcAddress(
        device, "nvnColorStateSetAlphaTest");
    pfnc_nvnColorStateGetBlendEnable = (nvnColorStateGetBlendEnableFunction)deviceGetProcAddress(
        device, "nvnColorStateGetBlendEnable");
    pfnc_nvnColorStateGetLogicOp =
        (nvnColorStateGetLogicOpFunction)deviceGetProcAddress(device, "nvnColorStateGetLogicOp");
    pfnc_nvnColorStateGetAlphaTest = (nvnColorStateGetAlphaTestFunction)deviceGetProcAddress(
        device, "nvnColorStateGetAlphaTest");
    pfnc_nvnChannelMaskStateSetDefaults =
        (nvnChannelMaskStateSetDefaultsFunction)deviceGetProcAddress(
            device, "nvnChannelMaskStateSetDefaults");
    pfnc_nvnChannelMaskStateSetChannelMask =
        (nvnChannelMaskStateSetChannelMaskFunction)deviceGetProcAddress(
            device, "nvnChannelMaskStateSetChannelMask");
    pfnc_nvnChannelMaskStateGetChannelMask =
        (nvnChannelMaskStateGetChannelMaskFunction)deviceGetProcAddress(
            device, "nvnChannelMaskStateGetChannelMask");
    pfnc_nvnMultisampleStateSetDefaults =
        (nvnMultisampleStateSetDefaultsFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetDefaults");
    pfnc_nvnMultisampleStateSetMultisampleEnable =
        (nvnMultisampleStateSetMultisampleEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetMultisampleEnable");
    pfnc_nvnMultisampleStateSetSamples =
        (nvnMultisampleStateSetSamplesFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetSamples");
    pfnc_nvnMultisampleStateSetAlphaToCoverageEnable =
        (nvnMultisampleStateSetAlphaToCoverageEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetAlphaToCoverageEnable");
    pfnc_nvnMultisampleStateSetAlphaToCoverageDither =
        (nvnMultisampleStateSetAlphaToCoverageDitherFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetAlphaToCoverageDither");
    pfnc_nvnMultisampleStateGetMultisampleEnable =
        (nvnMultisampleStateGetMultisampleEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetMultisampleEnable");
    pfnc_nvnMultisampleStateGetSamples =
        (nvnMultisampleStateGetSamplesFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetSamples");
    pfnc_nvnMultisampleStateGetAlphaToCoverageEnable =
        (nvnMultisampleStateGetAlphaToCoverageEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetAlphaToCoverageEnable");
    pfnc_nvnMultisampleStateGetAlphaToCoverageDither =
        (nvnMultisampleStateGetAlphaToCoverageDitherFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetAlphaToCoverageDither");
    pfnc_nvnMultisampleStateSetRasterSamples =
        (nvnMultisampleStateSetRasterSamplesFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetRasterSamples");
    pfnc_nvnMultisampleStateGetRasterSamples =
        (nvnMultisampleStateGetRasterSamplesFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetRasterSamples");
    pfnc_nvnMultisampleStateSetCoverageModulationMode =
        (nvnMultisampleStateSetCoverageModulationModeFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetCoverageModulationMode");
    pfnc_nvnMultisampleStateGetCoverageModulationMode =
        (nvnMultisampleStateGetCoverageModulationModeFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetCoverageModulationMode");
    pfnc_nvnMultisampleStateSetCoverageToColorEnable =
        (nvnMultisampleStateSetCoverageToColorEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetCoverageToColorEnable");
    pfnc_nvnMultisampleStateGetCoverageToColorEnable =
        (nvnMultisampleStateGetCoverageToColorEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetCoverageToColorEnable");
    pfnc_nvnMultisampleStateSetCoverageToColorOutput =
        (nvnMultisampleStateSetCoverageToColorOutputFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetCoverageToColorOutput");
    pfnc_nvnMultisampleStateGetCoverageToColorOutput =
        (nvnMultisampleStateGetCoverageToColorOutputFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetCoverageToColorOutput");
    pfnc_nvnMultisampleStateSetSampleLocationsEnable =
        (nvnMultisampleStateSetSampleLocationsEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetSampleLocationsEnable");
    pfnc_nvnMultisampleStateGetSampleLocationsEnable =
        (nvnMultisampleStateGetSampleLocationsEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetSampleLocationsEnable");
    pfnc_nvnMultisampleStateGetSampleLocationsGrid =
        (nvnMultisampleStateGetSampleLocationsGridFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetSampleLocationsGrid");
    pfnc_nvnMultisampleStateSetSampleLocationsGridEnable =
        (nvnMultisampleStateSetSampleLocationsGridEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetSampleLocationsGridEnable");
    pfnc_nvnMultisampleStateGetSampleLocationsGridEnable =
        (nvnMultisampleStateGetSampleLocationsGridEnableFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateGetSampleLocationsGridEnable");
    pfnc_nvnMultisampleStateSetSampleLocations =
        (nvnMultisampleStateSetSampleLocationsFunction)deviceGetProcAddress(
            device, "nvnMultisampleStateSetSampleLocations");
    pfnc_nvnPolygonStateSetDefaults = (nvnPolygonStateSetDefaultsFunction)deviceGetProcAddress(
        device, "nvnPolygonStateSetDefaults");
    pfnc_nvnPolygonStateSetCullFace = (nvnPolygonStateSetCullFaceFunction)deviceGetProcAddress(
        device, "nvnPolygonStateSetCullFace");
    pfnc_nvnPolygonStateSetFrontFace = (nvnPolygonStateSetFrontFaceFunction)deviceGetProcAddress(
        device, "nvnPolygonStateSetFrontFace");
    pfnc_nvnPolygonStateSetPolygonMode =
        (nvnPolygonStateSetPolygonModeFunction)deviceGetProcAddress(
            device, "nvnPolygonStateSetPolygonMode");
    pfnc_nvnPolygonStateSetPolygonOffsetEnables =
        (nvnPolygonStateSetPolygonOffsetEnablesFunction)deviceGetProcAddress(
            device, "nvnPolygonStateSetPolygonOffsetEnables");
    pfnc_nvnPolygonStateGetCullFace = (nvnPolygonStateGetCullFaceFunction)deviceGetProcAddress(
        device, "nvnPolygonStateGetCullFace");
    pfnc_nvnPolygonStateGetFrontFace = (nvnPolygonStateGetFrontFaceFunction)deviceGetProcAddress(
        device, "nvnPolygonStateGetFrontFace");
    pfnc_nvnPolygonStateGetPolygonMode =
        (nvnPolygonStateGetPolygonModeFunction)deviceGetProcAddress(
            device, "nvnPolygonStateGetPolygonMode");
    pfnc_nvnPolygonStateGetPolygonOffsetEnables =
        (nvnPolygonStateGetPolygonOffsetEnablesFunction)deviceGetProcAddress(
            device, "nvnPolygonStateGetPolygonOffsetEnables");
    pfnc_nvnDepthStencilStateSetDefaults =
        (nvnDepthStencilStateSetDefaultsFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateSetDefaults");
    pfnc_nvnDepthStencilStateSetDepthTestEnable =
        (nvnDepthStencilStateSetDepthTestEnableFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateSetDepthTestEnable");
    pfnc_nvnDepthStencilStateSetDepthWriteEnable =
        (nvnDepthStencilStateSetDepthWriteEnableFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateSetDepthWriteEnable");
    pfnc_nvnDepthStencilStateSetDepthFunc =
        (nvnDepthStencilStateSetDepthFuncFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateSetDepthFunc");
    pfnc_nvnDepthStencilStateSetStencilTestEnable =
        (nvnDepthStencilStateSetStencilTestEnableFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateSetStencilTestEnable");
    pfnc_nvnDepthStencilStateSetStencilFunc =
        (nvnDepthStencilStateSetStencilFuncFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateSetStencilFunc");
    pfnc_nvnDepthStencilStateSetStencilOp =
        (nvnDepthStencilStateSetStencilOpFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateSetStencilOp");
    pfnc_nvnDepthStencilStateGetDepthTestEnable =
        (nvnDepthStencilStateGetDepthTestEnableFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateGetDepthTestEnable");
    pfnc_nvnDepthStencilStateGetDepthWriteEnable =
        (nvnDepthStencilStateGetDepthWriteEnableFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateGetDepthWriteEnable");
    pfnc_nvnDepthStencilStateGetDepthFunc =
        (nvnDepthStencilStateGetDepthFuncFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateGetDepthFunc");
    pfnc_nvnDepthStencilStateGetStencilTestEnable =
        (nvnDepthStencilStateGetStencilTestEnableFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateGetStencilTestEnable");
    pfnc_nvnDepthStencilStateGetStencilFunc =
        (nvnDepthStencilStateGetStencilFuncFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateGetStencilFunc");
    pfnc_nvnDepthStencilStateGetStencilOp =
        (nvnDepthStencilStateGetStencilOpFunction)deviceGetProcAddress(
            device, "nvnDepthStencilStateGetStencilOp");
    pfnc_nvnVertexAttribStateSetDefaults =
        (nvnVertexAttribStateSetDefaultsFunction)deviceGetProcAddress(
            device, "nvnVertexAttribStateSetDefaults");
    pfnc_nvnVertexAttribStateSetFormat =
        (nvnVertexAttribStateSetFormatFunction)deviceGetProcAddress(
            device, "nvnVertexAttribStateSetFormat");
    pfnc_nvnVertexAttribStateSetStreamIndex =
        (nvnVertexAttribStateSetStreamIndexFunction)deviceGetProcAddress(
            device, "nvnVertexAttribStateSetStreamIndex");
    pfnc_nvnVertexAttribStateGetFormat =
        (nvnVertexAttribStateGetFormatFunction)deviceGetProcAddress(
            device, "nvnVertexAttribStateGetFormat");
    pfnc_nvnVertexAttribStateGetStreamIndex =
        (nvnVertexAttribStateGetStreamIndexFunction)deviceGetProcAddress(
            device, "nvnVertexAttribStateGetStreamIndex");
    pfnc_nvnVertexStreamStateSetDefaults =
        (nvnVertexStreamStateSetDefaultsFunction)deviceGetProcAddress(
            device, "nvnVertexStreamStateSetDefaults");
    pfnc_nvnVertexStreamStateSetStride =
        (nvnVertexStreamStateSetStrideFunction)deviceGetProcAddress(
            device, "nvnVertexStreamStateSetStride");
    pfnc_nvnVertexStreamStateSetDivisor =
        (nvnVertexStreamStateSetDivisorFunction)deviceGetProcAddress(
            device, "nvnVertexStreamStateSetDivisor");
    pfnc_nvnVertexStreamStateGetStride =
        (nvnVertexStreamStateGetStrideFunction)deviceGetProcAddress(
            device, "nvnVertexStreamStateGetStride");
    pfnc_nvnVertexStreamStateGetDivisor =
        (nvnVertexStreamStateGetDivisorFunction)deviceGetProcAddress(
            device, "nvnVertexStreamStateGetDivisor");
    pfnc_nvnCommandBufferInitialize = (nvnCommandBufferInitializeFunction)deviceGetProcAddress(
        device, "nvnCommandBufferInitialize");
    pfnc_nvnCommandBufferFinalize =
        (nvnCommandBufferFinalizeFunction)deviceGetProcAddress(device, "nvnCommandBufferFinalize");
    pfnc_nvnCommandBufferSetDebugLabel =
        (nvnCommandBufferSetDebugLabelFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetDebugLabel");
    pfnc_nvnCommandBufferSetMemoryCallback =
        (nvnCommandBufferSetMemoryCallbackFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetMemoryCallback");
    pfnc_nvnCommandBufferSetMemoryCallbackData =
        (nvnCommandBufferSetMemoryCallbackDataFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetMemoryCallbackData");
    pfnc_nvnCommandBufferAddCommandMemory =
        (nvnCommandBufferAddCommandMemoryFunction)deviceGetProcAddress(
            device, "nvnCommandBufferAddCommandMemory");
    pfnc_nvnCommandBufferAddControlMemory =
        (nvnCommandBufferAddControlMemoryFunction)deviceGetProcAddress(
            device, "nvnCommandBufferAddControlMemory");
    pfnc_nvnCommandBufferGetCommandMemorySize =
        (nvnCommandBufferGetCommandMemorySizeFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetCommandMemorySize");
    pfnc_nvnCommandBufferGetCommandMemoryUsed =
        (nvnCommandBufferGetCommandMemoryUsedFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetCommandMemoryUsed");
    pfnc_nvnCommandBufferGetCommandMemoryFree =
        (nvnCommandBufferGetCommandMemoryFreeFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetCommandMemoryFree");
    pfnc_nvnCommandBufferGetControlMemorySize =
        (nvnCommandBufferGetControlMemorySizeFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetControlMemorySize");
    pfnc_nvnCommandBufferGetControlMemoryUsed =
        (nvnCommandBufferGetControlMemoryUsedFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetControlMemoryUsed");
    pfnc_nvnCommandBufferGetControlMemoryFree =
        (nvnCommandBufferGetControlMemoryFreeFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetControlMemoryFree");
    pfnc_nvnCommandBufferBeginRecording =
        (nvnCommandBufferBeginRecordingFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBeginRecording");
    pfnc_nvnCommandBufferEndRecording = (nvnCommandBufferEndRecordingFunction)deviceGetProcAddress(
        device, "nvnCommandBufferEndRecording");
    pfnc_nvnCommandBufferCallCommands = (nvnCommandBufferCallCommandsFunction)deviceGetProcAddress(
        device, "nvnCommandBufferCallCommands");
    pfnc_nvnCommandBufferCopyCommands = (nvnCommandBufferCopyCommandsFunction)deviceGetProcAddress(
        device, "nvnCommandBufferCopyCommands");
    pfnc_nvnCommandBufferBindBlendState =
        (nvnCommandBufferBindBlendStateFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindBlendState");
    pfnc_nvnCommandBufferBindChannelMaskState =
        (nvnCommandBufferBindChannelMaskStateFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindChannelMaskState");
    pfnc_nvnCommandBufferBindColorState =
        (nvnCommandBufferBindColorStateFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindColorState");
    pfnc_nvnCommandBufferBindMultisampleState =
        (nvnCommandBufferBindMultisampleStateFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindMultisampleState");
    pfnc_nvnCommandBufferBindPolygonState =
        (nvnCommandBufferBindPolygonStateFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindPolygonState");
    pfnc_nvnCommandBufferBindDepthStencilState =
        (nvnCommandBufferBindDepthStencilStateFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindDepthStencilState");
    pfnc_nvnCommandBufferBindVertexAttribState =
        (nvnCommandBufferBindVertexAttribStateFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindVertexAttribState");
    pfnc_nvnCommandBufferBindVertexStreamState =
        (nvnCommandBufferBindVertexStreamStateFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindVertexStreamState");
    pfnc_nvnCommandBufferBindProgram = (nvnCommandBufferBindProgramFunction)deviceGetProcAddress(
        device, "nvnCommandBufferBindProgram");
    pfnc_nvnCommandBufferBindVertexBuffer =
        (nvnCommandBufferBindVertexBufferFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindVertexBuffer");
    pfnc_nvnCommandBufferBindVertexBuffers =
        (nvnCommandBufferBindVertexBuffersFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindVertexBuffers");
    pfnc_nvnCommandBufferBindUniformBuffer =
        (nvnCommandBufferBindUniformBufferFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindUniformBuffer");
    pfnc_nvnCommandBufferBindUniformBuffers =
        (nvnCommandBufferBindUniformBuffersFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindUniformBuffers");
    pfnc_nvnCommandBufferBindTransformFeedbackBuffer =
        (nvnCommandBufferBindTransformFeedbackBufferFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindTransformFeedbackBuffer");
    pfnc_nvnCommandBufferBindTransformFeedbackBuffers =
        (nvnCommandBufferBindTransformFeedbackBuffersFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindTransformFeedbackBuffers");
    pfnc_nvnCommandBufferBindStorageBuffer =
        (nvnCommandBufferBindStorageBufferFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindStorageBuffer");
    pfnc_nvnCommandBufferBindStorageBuffers =
        (nvnCommandBufferBindStorageBuffersFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindStorageBuffers");
    pfnc_nvnCommandBufferBindTexture = (nvnCommandBufferBindTextureFunction)deviceGetProcAddress(
        device, "nvnCommandBufferBindTexture");
    pfnc_nvnCommandBufferBindTextures = (nvnCommandBufferBindTexturesFunction)deviceGetProcAddress(
        device, "nvnCommandBufferBindTextures");
    pfnc_nvnCommandBufferBindImage = (nvnCommandBufferBindImageFunction)deviceGetProcAddress(
        device, "nvnCommandBufferBindImage");
    pfnc_nvnCommandBufferBindImages = (nvnCommandBufferBindImagesFunction)deviceGetProcAddress(
        device, "nvnCommandBufferBindImages");
    pfnc_nvnCommandBufferSetPatchSize = (nvnCommandBufferSetPatchSizeFunction)deviceGetProcAddress(
        device, "nvnCommandBufferSetPatchSize");
    pfnc_nvnCommandBufferSetInnerTessellationLevels =
        (nvnCommandBufferSetInnerTessellationLevelsFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetInnerTessellationLevels");
    pfnc_nvnCommandBufferSetOuterTessellationLevels =
        (nvnCommandBufferSetOuterTessellationLevelsFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetOuterTessellationLevels");
    pfnc_nvnCommandBufferSetPrimitiveRestart =
        (nvnCommandBufferSetPrimitiveRestartFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetPrimitiveRestart");
    pfnc_nvnCommandBufferBeginTransformFeedback =
        (nvnCommandBufferBeginTransformFeedbackFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBeginTransformFeedback");
    pfnc_nvnCommandBufferEndTransformFeedback =
        (nvnCommandBufferEndTransformFeedbackFunction)deviceGetProcAddress(
            device, "nvnCommandBufferEndTransformFeedback");
    pfnc_nvnCommandBufferPauseTransformFeedback =
        (nvnCommandBufferPauseTransformFeedbackFunction)deviceGetProcAddress(
            device, "nvnCommandBufferPauseTransformFeedback");
    pfnc_nvnCommandBufferResumeTransformFeedback =
        (nvnCommandBufferResumeTransformFeedbackFunction)deviceGetProcAddress(
            device, "nvnCommandBufferResumeTransformFeedback");
    pfnc_nvnCommandBufferDrawTransformFeedback =
        (nvnCommandBufferDrawTransformFeedbackFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDrawTransformFeedback");
    pfnc_nvnCommandBufferDrawArrays = (nvnCommandBufferDrawArraysFunction)deviceGetProcAddress(
        device, "nvnCommandBufferDrawArrays");
    pfnc_nvnCommandBufferDrawElements = (nvnCommandBufferDrawElementsFunction)deviceGetProcAddress(
        device, "nvnCommandBufferDrawElements");
    pfnc_nvnCommandBufferDrawElementsBaseVertex =
        (nvnCommandBufferDrawElementsBaseVertexFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDrawElementsBaseVertex");
    pfnc_nvnCommandBufferDrawArraysInstanced =
        (nvnCommandBufferDrawArraysInstancedFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDrawArraysInstanced");
    pfnc_nvnCommandBufferDrawElementsInstanced =
        (nvnCommandBufferDrawElementsInstancedFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDrawElementsInstanced");
    pfnc_nvnCommandBufferDrawArraysIndirect =
        (nvnCommandBufferDrawArraysIndirectFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDrawArraysIndirect");
    pfnc_nvnCommandBufferDrawElementsIndirect =
        (nvnCommandBufferDrawElementsIndirectFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDrawElementsIndirect");
    pfnc_nvnCommandBufferMultiDrawArraysIndirectCount =
        (nvnCommandBufferMultiDrawArraysIndirectCountFunction)deviceGetProcAddress(
            device, "nvnCommandBufferMultiDrawArraysIndirectCount");
    pfnc_nvnCommandBufferMultiDrawElementsIndirectCount =
        (nvnCommandBufferMultiDrawElementsIndirectCountFunction)deviceGetProcAddress(
            device, "nvnCommandBufferMultiDrawElementsIndirectCount");
    pfnc_nvnCommandBufferClearColor = (nvnCommandBufferClearColorFunction)deviceGetProcAddress(
        device, "nvnCommandBufferClearColor");
    pfnc_nvnCommandBufferClearColori = (nvnCommandBufferClearColoriFunction)deviceGetProcAddress(
        device, "nvnCommandBufferClearColori");
    pfnc_nvnCommandBufferClearColorui = (nvnCommandBufferClearColoruiFunction)deviceGetProcAddress(
        device, "nvnCommandBufferClearColorui");
    pfnc_nvnCommandBufferClearDepthStencil =
        (nvnCommandBufferClearDepthStencilFunction)deviceGetProcAddress(
            device, "nvnCommandBufferClearDepthStencil");
    pfnc_nvnCommandBufferDispatchCompute =
        (nvnCommandBufferDispatchComputeFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDispatchCompute");
    pfnc_nvnCommandBufferDispatchComputeIndirect =
        (nvnCommandBufferDispatchComputeIndirectFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDispatchComputeIndirect");
    pfnc_nvnCommandBufferSetViewport = (nvnCommandBufferSetViewportFunction)deviceGetProcAddress(
        device, "nvnCommandBufferSetViewport");
    pfnc_nvnCommandBufferSetViewports = (nvnCommandBufferSetViewportsFunction)deviceGetProcAddress(
        device, "nvnCommandBufferSetViewports");
    pfnc_nvnCommandBufferSetViewportSwizzles =
        (nvnCommandBufferSetViewportSwizzlesFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetViewportSwizzles");
    pfnc_nvnCommandBufferSetScissor = (nvnCommandBufferSetScissorFunction)deviceGetProcAddress(
        device, "nvnCommandBufferSetScissor");
    pfnc_nvnCommandBufferSetScissors = (nvnCommandBufferSetScissorsFunction)deviceGetProcAddress(
        device, "nvnCommandBufferSetScissors");
    pfnc_nvnCommandBufferSetDepthRange =
        (nvnCommandBufferSetDepthRangeFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetDepthRange");
    pfnc_nvnCommandBufferSetDepthBounds =
        (nvnCommandBufferSetDepthBoundsFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetDepthBounds");
    pfnc_nvnCommandBufferSetDepthRanges =
        (nvnCommandBufferSetDepthRangesFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetDepthRanges");
    pfnc_nvnCommandBufferSetTiledCacheAction =
        (nvnCommandBufferSetTiledCacheActionFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetTiledCacheAction");
    pfnc_nvnCommandBufferSetTiledCacheTileSize =
        (nvnCommandBufferSetTiledCacheTileSizeFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetTiledCacheTileSize");
    pfnc_nvnCommandBufferBindSeparateTexture =
        (nvnCommandBufferBindSeparateTextureFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindSeparateTexture");
    pfnc_nvnCommandBufferBindSeparateSampler =
        (nvnCommandBufferBindSeparateSamplerFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindSeparateSampler");
    pfnc_nvnCommandBufferBindSeparateTextures =
        (nvnCommandBufferBindSeparateTexturesFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindSeparateTextures");
    pfnc_nvnCommandBufferBindSeparateSamplers =
        (nvnCommandBufferBindSeparateSamplersFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindSeparateSamplers");
    pfnc_nvnCommandBufferSetStencilValueMask =
        (nvnCommandBufferSetStencilValueMaskFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetStencilValueMask");
    pfnc_nvnCommandBufferSetStencilMask =
        (nvnCommandBufferSetStencilMaskFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetStencilMask");
    pfnc_nvnCommandBufferSetStencilRef =
        (nvnCommandBufferSetStencilRefFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetStencilRef");
    pfnc_nvnCommandBufferSetBlendColor =
        (nvnCommandBufferSetBlendColorFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetBlendColor");
    pfnc_nvnCommandBufferSetPointSize = (nvnCommandBufferSetPointSizeFunction)deviceGetProcAddress(
        device, "nvnCommandBufferSetPointSize");
    pfnc_nvnCommandBufferSetLineWidth = (nvnCommandBufferSetLineWidthFunction)deviceGetProcAddress(
        device, "nvnCommandBufferSetLineWidth");
    pfnc_nvnCommandBufferSetPolygonOffsetClamp =
        (nvnCommandBufferSetPolygonOffsetClampFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetPolygonOffsetClamp");
    pfnc_nvnCommandBufferSetAlphaRef = (nvnCommandBufferSetAlphaRefFunction)deviceGetProcAddress(
        device, "nvnCommandBufferSetAlphaRef");
    pfnc_nvnCommandBufferSetSampleMask =
        (nvnCommandBufferSetSampleMaskFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetSampleMask");
    pfnc_nvnCommandBufferSetRasterizerDiscard =
        (nvnCommandBufferSetRasterizerDiscardFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetRasterizerDiscard");
    pfnc_nvnCommandBufferSetDepthClamp =
        (nvnCommandBufferSetDepthClampFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetDepthClamp");
    pfnc_nvnCommandBufferSetConservativeRasterEnable =
        (nvnCommandBufferSetConservativeRasterEnableFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetConservativeRasterEnable");
    pfnc_nvnCommandBufferSetConservativeRasterDilate =
        (nvnCommandBufferSetConservativeRasterDilateFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetConservativeRasterDilate");
    pfnc_nvnCommandBufferSetSubpixelPrecisionBias =
        (nvnCommandBufferSetSubpixelPrecisionBiasFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetSubpixelPrecisionBias");
    pfnc_nvnCommandBufferCopyBufferToTexture =
        (nvnCommandBufferCopyBufferToTextureFunction)deviceGetProcAddress(
            device, "nvnCommandBufferCopyBufferToTexture");
    pfnc_nvnCommandBufferCopyTextureToBuffer =
        (nvnCommandBufferCopyTextureToBufferFunction)deviceGetProcAddress(
            device, "nvnCommandBufferCopyTextureToBuffer");
    pfnc_nvnCommandBufferCopyTextureToTexture =
        (nvnCommandBufferCopyTextureToTextureFunction)deviceGetProcAddress(
            device, "nvnCommandBufferCopyTextureToTexture");
    pfnc_nvnCommandBufferCopyBufferToBuffer =
        (nvnCommandBufferCopyBufferToBufferFunction)deviceGetProcAddress(
            device, "nvnCommandBufferCopyBufferToBuffer");
    pfnc_nvnCommandBufferClearBuffer = (nvnCommandBufferClearBufferFunction)deviceGetProcAddress(
        device, "nvnCommandBufferClearBuffer");
    pfnc_nvnCommandBufferClearTexture = (nvnCommandBufferClearTextureFunction)deviceGetProcAddress(
        device, "nvnCommandBufferClearTexture");
    pfnc_nvnCommandBufferClearTexturei =
        (nvnCommandBufferClearTextureiFunction)deviceGetProcAddress(
            device, "nvnCommandBufferClearTexturei");
    pfnc_nvnCommandBufferClearTextureui =
        (nvnCommandBufferClearTextureuiFunction)deviceGetProcAddress(
            device, "nvnCommandBufferClearTextureui");
    pfnc_nvnCommandBufferUpdateUniformBuffer =
        (nvnCommandBufferUpdateUniformBufferFunction)deviceGetProcAddress(
            device, "nvnCommandBufferUpdateUniformBuffer");
    pfnc_nvnCommandBufferReportCounter =
        (nvnCommandBufferReportCounterFunction)deviceGetProcAddress(
            device, "nvnCommandBufferReportCounter");
    pfnc_nvnCommandBufferResetCounter = (nvnCommandBufferResetCounterFunction)deviceGetProcAddress(
        device, "nvnCommandBufferResetCounter");
    pfnc_nvnCommandBufferReportValue = (nvnCommandBufferReportValueFunction)deviceGetProcAddress(
        device, "nvnCommandBufferReportValue");
    pfnc_nvnCommandBufferSetRenderEnable =
        (nvnCommandBufferSetRenderEnableFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetRenderEnable");
    pfnc_nvnCommandBufferSetRenderEnableConditional =
        (nvnCommandBufferSetRenderEnableConditionalFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetRenderEnableConditional");
    pfnc_nvnCommandBufferSetRenderTargets =
        (nvnCommandBufferSetRenderTargetsFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetRenderTargets");
    pfnc_nvnCommandBufferDiscardColor = (nvnCommandBufferDiscardColorFunction)deviceGetProcAddress(
        device, "nvnCommandBufferDiscardColor");
    pfnc_nvnCommandBufferDiscardDepthStencil =
        (nvnCommandBufferDiscardDepthStencilFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDiscardDepthStencil");
    pfnc_nvnCommandBufferDownsample = (nvnCommandBufferDownsampleFunction)deviceGetProcAddress(
        device, "nvnCommandBufferDownsample");
    pfnc_nvnCommandBufferTiledDownsample =
        (nvnCommandBufferTiledDownsampleFunction)deviceGetProcAddress(
            device, "nvnCommandBufferTiledDownsample");
    pfnc_nvnCommandBufferDownsampleTextureView =
        (nvnCommandBufferDownsampleTextureViewFunction)deviceGetProcAddress(
            device, "nvnCommandBufferDownsampleTextureView");
    pfnc_nvnCommandBufferTiledDownsampleTextureView =
        (nvnCommandBufferTiledDownsampleTextureViewFunction)deviceGetProcAddress(
            device, "nvnCommandBufferTiledDownsampleTextureView");
    pfnc_nvnCommandBufferBarrier =
        (nvnCommandBufferBarrierFunction)deviceGetProcAddress(device, "nvnCommandBufferBarrier");
    pfnc_nvnCommandBufferWaitSync =
        (nvnCommandBufferWaitSyncFunction)deviceGetProcAddress(device, "nvnCommandBufferWaitSync");
    pfnc_nvnCommandBufferFenceSync = (nvnCommandBufferFenceSyncFunction)deviceGetProcAddress(
        device, "nvnCommandBufferFenceSync");
    pfnc_nvnCommandBufferSetTexturePool =
        (nvnCommandBufferSetTexturePoolFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetTexturePool");
    pfnc_nvnCommandBufferSetSamplerPool =
        (nvnCommandBufferSetSamplerPoolFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetSamplerPool");
    pfnc_nvnCommandBufferSetShaderScratchMemory =
        (nvnCommandBufferSetShaderScratchMemoryFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetShaderScratchMemory");
    pfnc_nvnCommandBufferSaveZCullData =
        (nvnCommandBufferSaveZCullDataFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSaveZCullData");
    pfnc_nvnCommandBufferRestoreZCullData =
        (nvnCommandBufferRestoreZCullDataFunction)deviceGetProcAddress(
            device, "nvnCommandBufferRestoreZCullData");
    pfnc_nvnCommandBufferSetCopyRowStride =
        (nvnCommandBufferSetCopyRowStrideFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetCopyRowStride");
    pfnc_nvnCommandBufferSetCopyImageStride =
        (nvnCommandBufferSetCopyImageStrideFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetCopyImageStride");
    pfnc_nvnCommandBufferGetCopyRowStride =
        (nvnCommandBufferGetCopyRowStrideFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetCopyRowStride");
    pfnc_nvnCommandBufferGetCopyImageStride =
        (nvnCommandBufferGetCopyImageStrideFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetCopyImageStride");
    pfnc_nvnCommandBufferDrawTexture = (nvnCommandBufferDrawTextureFunction)deviceGetProcAddress(
        device, "nvnCommandBufferDrawTexture");
    pfnc_nvnProgramSetSubroutineLinkage =
        (nvnProgramSetSubroutineLinkageFunction)deviceGetProcAddress(
            device, "nvnProgramSetSubroutineLinkage");
    pfnc_nvnCommandBufferSetProgramSubroutines =
        (nvnCommandBufferSetProgramSubroutinesFunction)deviceGetProcAddress(
            device, "nvnCommandBufferSetProgramSubroutines");
    pfnc_nvnCommandBufferBindCoverageModulationTable =
        (nvnCommandBufferBindCoverageModulationTableFunction)deviceGetProcAddress(
            device, "nvnCommandBufferBindCoverageModulationTable");
    pfnc_nvnCommandBufferResolveDepthBuffer =
        (nvnCommandBufferResolveDepthBufferFunction)deviceGetProcAddress(
            device, "nvnCommandBufferResolveDepthBuffer");
    pfnc_nvnCommandBufferPushDebugGroupStatic =
        (nvnCommandBufferPushDebugGroupStaticFunction)deviceGetProcAddress(
            device, "nvnCommandBufferPushDebugGroupStatic");
    pfnc_nvnCommandBufferPushDebugGroupDynamic =
        (nvnCommandBufferPushDebugGroupDynamicFunction)deviceGetProcAddress(
            device, "nvnCommandBufferPushDebugGroupDynamic");
    pfnc_nvnCommandBufferPushDebugGroup =
        (nvnCommandBufferPushDebugGroupFunction)deviceGetProcAddress(
            device, "nvnCommandBufferPushDebugGroup");
    pfnc_nvnCommandBufferPopDebugGroup =
        (nvnCommandBufferPopDebugGroupFunction)deviceGetProcAddress(
            device, "nvnCommandBufferPopDebugGroup");
    pfnc_nvnCommandBufferPopDebugGroupId =
        (nvnCommandBufferPopDebugGroupIdFunction)deviceGetProcAddress(
            device, "nvnCommandBufferPopDebugGroupId");
    pfnc_nvnCommandBufferInsertDebugMarkerStatic =
        (nvnCommandBufferInsertDebugMarkerStaticFunction)deviceGetProcAddress(
            device, "nvnCommandBufferInsertDebugMarkerStatic");
    pfnc_nvnCommandBufferInsertDebugMarkerDynamic =
        (nvnCommandBufferInsertDebugMarkerDynamicFunction)deviceGetProcAddress(
            device, "nvnCommandBufferInsertDebugMarkerDynamic");
    pfnc_nvnCommandBufferInsertDebugMarker =
        (nvnCommandBufferInsertDebugMarkerFunction)deviceGetProcAddress(
            device, "nvnCommandBufferInsertDebugMarker");
    pfnc_nvnCommandBufferGetMemoryCallback =
        (nvnCommandBufferGetMemoryCallbackFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetMemoryCallback");
    pfnc_nvnCommandBufferGetMemoryCallbackData =
        (nvnCommandBufferGetMemoryCallbackDataFunction)deviceGetProcAddress(
            device, "nvnCommandBufferGetMemoryCallbackData");
    pfnc_nvnCommandBufferIsRecording = (nvnCommandBufferIsRecordingFunction)deviceGetProcAddress(
        device, "nvnCommandBufferIsRecording");
    pfnc_nvnSyncInitialize =
        (nvnSyncInitializeFunction)deviceGetProcAddress(device, "nvnSyncInitialize");
    pfnc_nvnSyncFinalize = (nvnSyncFinalizeFunction)deviceGetProcAddress(device, "nvnSyncFinalize");
    pfnc_nvnSyncSetDebugLabel =
        (nvnSyncSetDebugLabelFunction)deviceGetProcAddress(device, "nvnSyncSetDebugLabel");
    pfnc_nvnQueueFenceSync =
        (nvnQueueFenceSyncFunction)deviceGetProcAddress(device, "nvnQueueFenceSync");
    pfnc_nvnSyncWait = (nvnSyncWaitFunction)deviceGetProcAddress(device, "nvnSyncWait");
    pfnc_nvnQueueWaitSync =
        (nvnQueueWaitSyncFunction)deviceGetProcAddress(device, "nvnQueueWaitSync");
    pfnc_nvnEventBuilderSetDefaults = (nvnEventBuilderSetDefaultsFunction)deviceGetProcAddress(
        device, "nvnEventBuilderSetDefaults");
    pfnc_nvnEventBuilderSetStorage = (nvnEventBuilderSetStorageFunction)deviceGetProcAddress(
        device, "nvnEventBuilderSetStorage");
    pfnc_nvnEventInitialize =
        (nvnEventInitializeFunction)deviceGetProcAddress(device, "nvnEventInitialize");
    pfnc_nvnEventFinalize =
        (nvnEventFinalizeFunction)deviceGetProcAddress(device, "nvnEventFinalize");
    pfnc_nvnEventGetValue =
        (nvnEventGetValueFunction)deviceGetProcAddress(device, "nvnEventGetValue");
    pfnc_nvnEventSignal = (nvnEventSignalFunction)deviceGetProcAddress(device, "nvnEventSignal");
    pfnc_nvnCommandBufferWaitEvent = (nvnCommandBufferWaitEventFunction)deviceGetProcAddress(
        device, "nvnCommandBufferWaitEvent");
    pfnc_nvnCommandBufferSignalEvent = (nvnCommandBufferSignalEventFunction)deviceGetProcAddress(
        device, "nvnCommandBufferSignalEvent");
}
}
