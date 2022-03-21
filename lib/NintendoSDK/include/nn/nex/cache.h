/**
 * @file cache.h
 * @brief NEX Cache Mangement.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace nex {
class String;
class BasicCache;

class CacheManager {
public:
    CacheManager();
    ~CacheManager();

    nn::nex::BasicCache* GetCache(nn::nex::String const&);
};

class BasicCache {
public:
    BasicCache(nn::nex::String const&);

    virtual ~BasicCache();

    u64 _8;
    u8 _10;
};
};  // namespace nex
};  // namespace nn