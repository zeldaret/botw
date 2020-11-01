#pragma once

#include <container/seadPtrArray.h>
#include <container/seadRingBuffer.h>
#include <limits>
#include <optional>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include <resource/seadResource.h>
#include "KingSystem/GameData/gdtFlag.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
class SaveMgr;
}

namespace ksys::res {

class GameSaveData : public sead::DirectResource {
public:
    struct SaveInfo {
        SaveInfo() = default;
        SaveInfo(const SaveInfo& other) { *this = other; }
        SaveInfo& operator=(const SaveInfo& other) {
            revision = other.revision;
            directory_num = other.directory_num;
            is_build_machine = other.is_build_machine;
            return *this;
        }

        s32 revision = 0;
        s32 directory_num = 0;
        bool is_build_machine = false;
    };
    KSYS_CHECK_SIZE_NX150(SaveInfo, 0xc);

    struct FileInfo {
        FileInfo() = default;
        FileInfo(const FileInfo& other) { *this = other; }
        FileInfo& operator=(const FileInfo& other) {
            name = other.name;
            is_common = other.is_common;
            is_common_at_same_account = other.is_common_at_same_account;
            is_save_secure_code = other.is_save_secure_code;
            return *this;
        }

        sead::FixedSafeString<32> name = sead::SafeString::cEmptyString;
        bool is_common = false;
        bool is_common_at_same_account = false;
        bool is_save_secure_code = false;
    };
    KSYS_CHECK_SIZE_NX150(FileInfo, 0x40);

    struct Flag {
        Flag() = default;
        Flag(const Flag& other) { *this = other; }
        Flag& operator=(const Flag& other) {
            _8 = other._8;
            kv = other.kv;
            type = other.type;
            return *this;
        }

        struct KeyValue {
            s32 name_hash = std::numeric_limits<int>::min();
            s32 value = std::numeric_limits<int>::min();
        };
        KeyValue kv;
        u32 _8 = 0;
        gdt::FlagType type = gdt::FlagType::Invalid;
    };
    KSYS_CHECK_SIZE_NX150(Flag, 0x10);

    struct File {
        void forEachFlag(const sead::Delegate1<SaveMgr, const Flag&>& delegate);
        void forEachFlag(const sead::Delegate1<SaveMgr, const Flag&>& delegate, s32 start, s32 end);
        void forEachFlag(const sead::Delegate1<SaveMgr, Flag&>& delegate);
        s32 findFlagIndex(u32 flag_name_hash) const;

        u32 name_hash = std::numeric_limits<int>::min();
        FileInfo* info = nullptr;
        sead::RingBuffer<Flag> flags;
    };
    KSYS_CHECK_SIZE_NX150(File, 0x28);

    GameSaveData() = default;
    ~GameSaveData() override { finalize(); }

    void finalize();

    void allocFiles(s32 count, sead::Heap* heap);
    void addFile(u32 hash, sead::Heap* heap);
    std::optional<File*> getFile(u32 hash) const;
    void allocFlags(u32 file_name_hash, s32 count, sead::Heap* heap);
    void copyFrom(const GameSaveData& src, sead::Heap* heap);
    void sortFlags();

    const sead::PtrArray<File>& getFiles() const { return mFiles; }

private:
    void doCreate_(u8* buffer, u32 size, sead::Heap* heap) override;

    SaveInfo* mSaveInfo = nullptr;
    sead::PtrArray<File> mFiles;
};
KSYS_CHECK_SIZE_NX150(GameSaveData, 0x38);

}  // namespace ksys::res
