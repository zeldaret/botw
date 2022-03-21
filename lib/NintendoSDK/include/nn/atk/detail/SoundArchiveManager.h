/**
 * @file SoundArchiveManager.h
 * @brief Sound archive manager implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace atk {
class SoundHandle;
class SoundArchive;
class SoundDataManager;

namespace detail {
class AddonSoundArchiveContainer;

class SoundArchiveManager {
public:
    SoundArchiveManager();

    virtual ~SoundArchiveManager();

    void Initialize(nn::atk::SoundArchive const*, nn::atk::SoundDataManager const*);
    void ChangeTargetArchive(char const*);
    void Finalize();
    bool IsAvailable() const;
    nn::atk::detail::AddonSoundArchiveContainer* GetAddonSoundArchive(char const*) const;

    u64 _8;
    u64* _10;
    nn::atk::detail::AddonSoundArchiveContainer* _18;
    u64* _20;
    nn::atk::SoundArchive* mSoundArchive;  // _28
    u64 _30;
    u64 _38;
    u64 _40;
};
};  // namespace detail
};  // namespace atk
};  // namespace nn