#include "KingSystem/Resource/resResourceGameSaveData.h"
#include <algorithm>
#include <codec/seadHashCRC32.h>
#include <prim/seadContainerIterator.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::res {

void GameSaveData::File::forEachFlag(const sead::Delegate1<SaveMgr, const Flag&>& delegate) {
    for (const auto& flag : flags)
        delegate(flag);
}

void GameSaveData::File::forEachFlag(const sead::Delegate1<SaveMgr, const Flag&>& delegate,
                                     s32 start, s32 end) {
    if (start == end)
        return;

    for (auto it = flags.begin(start), it_end = flags.begin(end); it != it_end; ++it)
        delegate(*it);
}

void GameSaveData::File::forEachFlag(const sead::Delegate1<SaveMgr, Flag&>& delegate) {
    for (auto& flag : flags)
        delegate(flag);
}

s32 GameSaveData::File::findFlagIndex(u32 flag_name_hash) const {
    s32 a = 0;
    s32 b = flags.size() - 1;
    while (a < b) {
        const s32 m = (a + b) / 2;
        if (u32(flags[m].kv.name_hash) == flag_name_hash)
            return m;
        if (u32(flags[m].kv.name_hash) < flag_name_hash)
            a = m + 1;
        else
            b = m;
    }

    if (u32(flags[a].kv.name_hash) == flag_name_hash)
        return a;
    return -1;
}

// NON_MATCHING: cNullChar is loaded too late (which throws off a lot of things) and Clang is
// using a different register to access file->info
void GameSaveData::doCreate_(u8* buffer, u32, sead::Heap*) {
    auto* heap = gdt::Manager::instance()->getSaveAreaHeap();
    al::ByamlIter root_iter{buffer};
    al::ByamlIter file_info_iter;
    al::ByamlIter save_info_iter;
    al::ByamlIter flags_iter;

    {
        al::ByamlIter iter;
        if (root_iter.tryGetIterByKey(&iter, "file_list")) {
            iter.tryGetIterByIndex(&file_info_iter, 0);
            iter.tryGetIterByIndex(&flags_iter, 1);
        }
        al::ByamlIter iter2;
        if (root_iter.tryGetIterByKey(&iter2, "save_info"))
            iter2.tryGetIterByIndex(&save_info_iter, 0);
    }

    mFiles.allocBuffer(1, heap);

    mSaveInfo = new (heap) SaveInfo;
    save_info_iter.tryGetIntByKey(&mSaveInfo->revision, "revision");
    save_info_iter.tryGetIntByKey(&mSaveInfo->directory_num, "directory_num");
    save_info_iter.tryGetBoolByKey(&mSaveInfo->is_build_machine, "is_build_machine");

#ifdef MATCHING_HACK_NX_CLANG
    // This isn't required but makes the diff cleaner... cNullChar is loaded here in the original.
    *static_cast<volatile const char*>(&sead::SafeString::cNullChar);
#endif

    const auto num_flags = flags_iter.getSize();

    auto* file = new (heap) File;
    file->name_hash = std::numeric_limits<int>::min();
    file->info = new (heap) FileInfo;

    const char* file_name = "";
    file_info_iter.tryGetStringByKey(&file_name, "file_name");
    auto* file_name_str = new (heap) sead::FixedSafeString<64>;
    file_name_str->copy(file_name);
    file->info->name = file_name_str->cstr();

    file_info_iter.tryGetBoolByKey(&file->info->is_common, "IsCommon");
    file_info_iter.tryGetBoolByKey(&file->info->is_common_at_same_account, "IsCommonAtSameAccount");
    file_info_iter.tryGetBoolByKey(&file->info->is_save_secure_code, "IsSaveSecureCode");

    if (num_flags > 0) {
        file->flags.allocBuffer(num_flags, heap);
        for (s32 i = 0; i < num_flags; ++i) {
            al::ByamlIter iter;
            if (!flags_iter.tryGetIterByIndex(&iter, i))
                continue;

            Flag flag;
            iter.tryGetIntByKey(&flag.kv.name_hash, "HashValue");
            const char* data_name = "";
            iter.tryGetStringByKey(&data_name, "DataName");
            const s32 data_name_hash = sead::HashCRC32::calcStringHash(data_name);
            if (flag.kv.name_hash != data_name_hash)
                flag.kv.name_hash = data_name_hash;

            file->flags.pushBack(flag);
        }
    }

    mFiles.pushBack(file);
}

void GameSaveData::finalize() {
    if (mSaveInfo)
        delete mSaveInfo;

    if (mFiles.isBufferReady()) {
        for (auto it = mFiles.begin(), end = mFiles.end(); it != end; ++it) {
            it->flags.freeBuffer();
            delete &*it;
            [[maybe_unused]] auto next = it;
            ++next;
        }
        mFiles.freeBuffer();
    }
}

void GameSaveData::allocFiles(s32 count, sead::Heap* heap) {
    mFiles.allocBuffer(count, heap);
}

void GameSaveData::addFile(u32 hash, sead::Heap* heap) {
    if (!mFiles.isBufferReady())
        return;

    auto* file = new (heap) File;
    file->info = nullptr;
    file->name_hash = hash;
    mFiles.pushBack(file);
}

std::optional<GameSaveData::File*> GameSaveData::getFile(u32 hash) const {
    for (auto& file : mFiles)
        if (file.name_hash == hash)
            return &file;

    return std::nullopt;
}

void GameSaveData::allocFlags(u32 file_name_hash, s32 count, sead::Heap* heap) {
    if (!mFiles.isBufferReady())
        return;

    auto file = getFile(file_name_hash);
    if (!file)
        return;

    (*file)->flags.allocBuffer(count, heap);
}

void GameSaveData::copyFrom(const GameSaveData& src, sead::Heap* heap) {
    if (!mSaveInfo && src.mSaveInfo) {
        mSaveInfo = new (heap) SaveInfo;
        *mSaveInfo = *src.mSaveInfo;
    }

    if (!mFiles.isBufferReady())
        return;

    auto it = mFiles.begin(), end = mFiles.end();
    const File& src_file = *src.mFiles[0];
    for (; it != end; ++it) {
        const u32 other_hash = sead::HashCRC32::calcStringHash(src_file.info->name);
        if (it->name_hash != other_hash)
            continue;

        if (it->info == nullptr) {
            it->info = new (heap) FileInfo;
            auto* target = it->info;
            *target = *src_file.info;
        }

        for (auto flag = src_file.flags.begin(), e = src_file.flags.end(); flag != e; ++flag)
            it->flags.pushBack(*flag);
    }
}

[[gnu::noinline]] static void sortGameSaveDataFlags(sead::RingBuffer<GameSaveData::Flag>& flags) {
    const auto wrapper = sead::stdIterator(flags);
    std::sort(wrapper.begin(), wrapper.end(),
              [](const GameSaveData::Flag& lhs, const GameSaveData::Flag& rhs) {
                  return lhs.kv.name_hash < rhs.kv.name_hash;
              });
}

void GameSaveData::sortFlags() {
    if (!mFiles.isBufferReady())
        return;

    for (auto& file : mFiles)
        sortGameSaveDataFlags(file.flags);
}

}  // namespace ksys::res
