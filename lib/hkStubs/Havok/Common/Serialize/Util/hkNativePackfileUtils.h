#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Serialize/Resource/hkResource.h>

class hkTypeInfoRegistry;

namespace hkNativePackfileUtils {

hkResource* load(const void* packfileData, int dataSize,
                 const hkTypeInfoRegistry* userRegistry = nullptr);

int getRequiredBufferSize(const void* packfileData, int dataSize);

void* load(const void* packfileData, int dataSize, void* outBuffer, int outBufferSize,
           const hkTypeInfoRegistry* userRegistry = nullptr);

/// @warning A buffer that has been loaded in place cannot be loaded more than once!
void* loadInPlace(void* packfileData, int dataSize,
                  const hkTypeInfoRegistry* userRegistry = nullptr, const char** errOut = nullptr);

const char* getContentsClassName(const void* packfileData, int dataSize);

void getImportsExports(const void* loadedBuffer, hkArray<hkResource::Export>& expOut,
                       hkArray<hkResource::Import>& impOut);

void getImportsExportsInPlace(const void* loadedBuffer, hkArray<hkResource::Export>& expOut,
                              hkArray<hkResource::Import>& impOut);

void unload(void* loadedBuffer, int bufferSize);
void unloadInPlace(void* loadedBuffer, int bufferSize);

hkResult validatePackfileHeader(const void* packfileData, const char** errOut);

}  // namespace hkNativePackfileUtils
