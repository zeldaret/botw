project(sead CXX ASM)

option(SEAD_DEBUG "Enable debug assertions and warnings" OFF)
set(SEAD_PLATFORM "nin" CACHE STRING "Target platform (default: nin)")
set_property(
  CACHE SEAD_PLATFORM
  PROPERTY STRINGS "nin"
)

add_library(sead OBJECT
  include/basis/seadNew.h
  include/basis/seadRawPrint.h
  include/basis/seadTypes.h
  modules/src/basis/seadNew.cpp

  include/codec/seadBase64.h
  include/codec/seadHashCRC16.h
  include/codec/seadHashCRC32.h
  modules/src/codec/seadHashCRC16.cpp
  modules/src/codec/seadHashCRC32.cpp

  include/container/seadBuffer.h
  include/container/seadFreeList.h
  include/container/seadListImpl.h
  include/container/seadObjArray.h
  include/container/seadObjList.h
  include/container/seadOffsetList.h
  include/container/seadOrderedSet.h
  include/container/seadPtrArray.h
  include/container/seadRingBuffer.h
  include/container/seadSafeArray.h
  include/container/seadStrTreeMap.h
  include/container/seadTList.h
  include/container/seadTreeMap.h
  include/container/seadTreeNode.h
  modules/src/container/seadListImpl.cpp
  modules/src/container/seadPtrArray.cpp
  modules/src/container/seadTreeNode.cpp

  include/devenv/seadAssertConfig.h
  include/devenv/seadEnvUtil.h
  include/devenv/seadGameConfig.h
  include/devenv/seadStackTrace.h
  modules/src/devenv/seadAssertConfig.cpp
  modules/src/devenv/seadGameConfig.cpp
  modules/src/devenv/seadStackTrace.cpp

  include/filedevice/seadArchiveFileDevice.h
  include/filedevice/seadFileDevice.h
  include/filedevice/seadFileDeviceMgr.h
  include/filedevice/seadMainFileDevice.h
  include/filedevice/seadPath.h
  modules/src/filedevice/seadArchiveFileDevice.cpp
  modules/src/filedevice/seadFileDevice.cpp
  modules/src/filedevice/seadFileDeviceMgr.cpp
  modules/src/filedevice/seadMainFileDevice.cpp
  modules/src/filedevice/seadPath.cpp

  include/framework/seadCalculateTask.h
  include/framework/seadFramework.h
  include/framework/seadHeapPolicies.h
  include/framework/seadInfLoopChecker.h
  include/framework/seadMethodTree.h
  include/framework/seadMethodTreeMgr.h
  include/framework/seadProcessMeter.h
  include/framework/seadProcessMeterBar.h
  include/framework/seadTaskBase.h
  include/framework/seadTaskID.h
  include/framework/seadTaskMgr.h
  include/framework/seadTaskParameter.h
  modules/src/framework/seadCalculateTask.cpp
  modules/src/framework/seadMethodTree.cpp
  modules/src/framework/seadProcessMeterBar.cpp

  include/gfx/seadCamera.h
  include/gfx/seadColor.h
  include/gfx/seadDrawContext.h
  include/gfx/seadFrameBuffer.h
  include/gfx/seadPrimitiveRenderer.h
  include/gfx/seadPrimitiveRendererUtil.h
  include/gfx/seadProjection.h
  include/gfx/seadTexture.h
  modules/src/gfx/seadCamera.cpp
  modules/src/gfx/seadColor.cpp
  # modules/src/gfx/seadPrimitiveRenderer.cpp
  # modules/src/gfx/seadPrimitiveRendererUtil.cpp
  modules/src/gfx/seadProjection.cpp

  include/heap/seadArena.h
  include/heap/seadDisposer.h
  include/heap/seadExpHeap.h
  include/heap/seadFrameHeap.h
  include/heap/seadHeap.h
  include/heap/seadHeapMgr.h
  include/heap/seadMemBlock.h
  modules/src/heap/seadDisposer.cpp
  modules/src/heap/seadExpHeap.cpp
  modules/src/heap/seadHeap.cpp
  modules/src/heap/seadHeapMgr.cpp

  include/math/seadBoundBox.h
  include/math/seadBoundBox.hpp
  include/math/seadMathBase.h
  include/math/seadMathCalcCommon.h
  include/math/seadMathCalcCommon.hpp
  include/math/seadMathNumbers.h
  include/math/seadMathPolicies.h
  include/math/seadMatrix.h
  include/math/seadMatrix.hpp
  include/math/seadMatrixCalcCommon.h
  include/math/seadMatrixCalcCommon.hpp
  include/math/seadQuat.h
  include/math/seadQuat.hpp
  include/math/seadQuatCalcCommon.h
  include/math/seadQuatCalcCommon.hpp
  include/math/seadVector.h
  include/math/seadVector.hpp
  include/math/seadVectorCalcCommon.h
  include/math/seadVectorCalcCommon.hpp
  modules/src/math/seadBoundBox.cpp
  modules/src/math/seadMathCalcCommon.cpp
  modules/src/math/seadMatrix.cpp
  modules/src/math/seadQuat.cpp
  modules/src/math/seadVector.cpp

  include/mc/seadCoreInfo.h
  include/mc/seadJob.h
  include/mc/seadJobQueue.h
  include/mc/seadWorker.h
  include/mc/seadWorkerMgr.h
  modules/src/mc/seadCoreInfo.cpp
  modules/src/mc/seadJob.cpp
  modules/src/mc/seadJobQueue.cpp
  modules/src/mc/seadWorker.cpp
  modules/src/mc/seadWorkerMgr.cpp

  include/prim/seadBitFlag.h
  include/prim/seadBitUtil.h
  include/prim/seadContainerIterator.h
  include/prim/seadDelegate.h
  include/prim/seadDelegateEventSlot.h
  include/prim/seadEndian.h
  include/prim/seadEnum.h
  include/prim/seadFormatPrint.h
  include/prim/seadLongBitFlag.h
  include/prim/seadMemUtil.h
  include/prim/seadNamable.h
  include/prim/seadPtrUtil.h
  include/prim/seadRuntimeTypeInfo.h
  include/prim/seadSafeString.h
  include/prim/seadSafeString.hpp
  include/prim/seadScopedLock.h
  include/prim/seadScopeGuard.h
  include/prim/seadSizedEnum.h
  include/prim/seadStorageFor.h
  include/prim/seadStringBuilder.h
  include/prim/seadStringUtil.h
  include/prim/seadTypedBitFlag.h
  include/prim/seadTypedLongBitFlag.h
  modules/src/prim/seadBitFlag.cpp
  modules/src/prim/seadEndian.cpp
  modules/src/prim/seadEnum.cpp
  modules/src/prim/seadMemUtil.cpp
  modules/src/prim/seadSafeString.cpp
  modules/src/prim/seadStringBuilder.cpp
  modules/src/prim/seadStringUtil.cpp

  include/random/seadGlobalRandom.h
  include/random/seadRandom.h
  modules/src/random/seadGlobalRandom.cpp
  modules/src/random/seadRandom.cpp

  include/resource/seadArchiveRes.h
  include/resource/seadDecompressor.h
  include/resource/seadResource.h
  include/resource/seadResourceMgr.h
  include/resource/seadSharcArchiveRes.h
  include/resource/seadSZSDecompressor.h
  modules/src/resource/seadArchiveRes.cpp
  modules/src/resource/seadResource.cpp
  modules/src/resource/seadResourceMgr.cpp
  modules/src/resource/seadSharcArchiveRes.cpp
  modules/src/resource/seadSZSDecompressor.cpp

  include/stream/seadBufferStream.h
  include/stream/seadStream.h
  include/stream/seadStreamFormat.h
  include/stream/seadStreamSrc.h

  include/thread/seadAtomic.h
  include/thread/seadCriticalSection.h
  include/thread/seadDelegateThread.h
  include/thread/seadEvent.h
  include/thread/seadMessageQueue.h
  include/thread/seadMutex.h
  include/thread/seadReadWriteLock.h
  include/thread/seadSemaphore.h
  include/thread/seadSpinLock.h
  include/thread/seadThread.h
  include/thread/seadThreadLocalStorage.h
  include/thread/seadThreadUtil.h
  modules/src/thread/seadDelegateThread.cpp
  modules/src/thread/seadReadWriteLock.cpp
  modules/src/thread/seadSpinLock.cpp
  modules/src/thread/seadThread.cpp
  modules/src/thread/seadThreadUtil.cpp

  include/time/seadCalendarSpan.h
  include/time/seadCalendarTime.h
  include/time/seadDateSpan.h
  include/time/seadDateTime.h
  include/time/seadDateUtil.h
  include/time/seadTickSpan.h
  include/time/seadTickTime.h
  modules/src/time/seadCalendarTime.cpp
  modules/src/time/seadDateSpan.cpp
  modules/src/time/seadDateTime.cpp
  modules/src/time/seadDateTimeUtc.cpp
  modules/src/time/seadDateUtil.cpp
  modules/src/time/seadTickSpan.cpp
)

target_sources(sead PRIVATE
  include/hostio/seadHostIOCurve.h
  modules/src/hostio/seadHostIOCurve.cpp
)
if(SEAD_DEBUG)
  target_sources(sead PRIVATE
    include/hostio/seadHostIOEventListener.h
    include/hostio/seadHostIOMgr.h
    include/hostio/seadHostIONode.h
    include/hostio/seadHostIOReflexible.h
    include/hostio/seadHostIOThreadLock.h
    modules/src/hostio/seadHostIOEventListener.cpp
    modules/src/hostio/seadHostIONode.cpp
    modules/src/hostio/seadHostIOReflexible.cpp
    modules/src/hostio/seadHostIOThreadLock.cpp
  )
endif()

if(SEAD_PLATFORM STREQUAL "nin")
  if(NOT TARGET NintendoSDK)
    add_subdirectory(../NintendoSDK)
  endif()
  target_link_libraries(sead PUBLIC NintendoSDK)

  target_sources(sead PRIVATE
    include/filedevice/nin/seadNinAocFileDeviceNin.h
    include/filedevice/nin/seadNinContentFileDeviceNin.h
    include/filedevice/nin/seadNinFileDeviceBaseNin.h
    include/filedevice/nin/seadNinHostIOFileDevice.h
    include/filedevice/nin/seadNinSaveFileDeviceNin.h
    include/filedevice/nin/seadNinSDFileDeviceNin.h
    modules/src/filedevice/nin/seadNinAocFileDeviceNin.cpp
    modules/src/filedevice/nin/seadNinContentFileDeviceNin.cpp
    modules/src/filedevice/nin/seadNinFileDeviceBaseNin.cpp
    modules/src/filedevice/nin/seadNinHostIOFileDevice.cpp
    modules/src/filedevice/nin/seadNinSaveFileDeviceNin.cpp
    modules/src/filedevice/nin/seadNinSDFileDeviceNin.cpp

    include/thread/nin/seadThreadLocalStorageNin.hpp
    modules/src/thread/nin/seadCriticalSectionNin.cpp
    modules/src/thread/nin/seadEventNin.cpp
    modules/src/thread/nin/seadMessageQueueNin.cpp
    modules/src/thread/nin/seadMutexNin.cpp
    modules/src/thread/nin/seadSemaphoreNin.cpp
    modules/src/thread/nin/seadThreadNin.cpp
  )
endif()

target_compile_options(sead PRIVATE -fno-exceptions)
target_compile_options(sead PRIVATE -fno-strict-aliasing)
target_compile_options(sead PRIVATE -Wall -Wextra -Wdeprecated)
target_compile_options(sead PRIVATE -Wno-invalid-offsetof)
target_include_directories(sead PUBLIC include/)

if(SEAD_DEBUG)
  target_compile_definitions(sead PUBLIC SEAD_DEBUG=1)
endif()
