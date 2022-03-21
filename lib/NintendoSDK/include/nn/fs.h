/**
 * @file fs.h
 * @brief Filesystem implementation.
 */

#pragma once

#include <nn/account.h>
#include <nn/types.h>

namespace nn {
typedef u64 ApplicationId;

namespace fs {
using namespace ams::fs;

typedef u64 UserId;

struct DirectoryEntry {
    char name[0x300 + 1];
    char _x302[3];
    u8 type;
    char _x304;
    s64 fileSize;
};

struct FileHandle {
    void* handle;
};

struct DirectoryHandle {
    void* handle;
};

enum DirectoryEntryType { DirectoryEntryType_Directory, DirectoryEntryType_File };

enum OpenMode {
    OpenMode_Read = 1 << 0,
    OpenMode_Write = 1 << 1,
    OpenMode_Append = 1 << 2,

    OpenMode_ReadWrite = OpenMode_Read | OpenMode_Write
};

enum OpenDirectoryMode {
    OpenDirectoryMode_Directory = 1 << 0,
    OpenDirectoryMode_File = 1 << 1,
    OpenDirectoryMode_All = OpenDirectoryMode_Directory | OpenDirectoryMode_File,
};

struct ReadOption {
    u32 value;

    static const ReadOption None;
};
inline constexpr const ReadOption ReadOption::None = {0};

enum WriteOptionFlag {
    WriteOptionFlag_Flush = 1 << 0,
};

struct WriteOption {
    int flags;

    static WriteOption CreateOption(int flags) {
        WriteOption op;
        op.flags = flags;
        return op;
    }
};

// ROM
Result QueryMountRomCacheSize(size_t* size);
Result QueryMountRomCacheSize(size_t* size, nn::ApplicationId);
Result QueryMountAddOnContentCacheSize(size_t* size, int id);
Result MountRom(char const* name, void* cache, size_t cache_size);
Result MountAddOnContent(char const* name, int id, void* cache, size_t cache_size);
bool CanMountRomForDebug();
Result CanMountRom(nn::ApplicationId);
Result QueryMountRomOnFileCacheSize(u64*, nn::fs::FileHandle);
Result MountRomOnFile(char const*, nn::fs::FileHandle, void*, u64);

// SAVE
Result EnsureSaveData(nn::account::Uid const&);
Result MountSaveData(char const*, nn::fs::UserId);
Result MountSaveDataForDebug(char const*);
Result CommitSaveData(const char* path);

// FILE
Result GetEntryType(nn::fs::DirectoryEntryType* type, char const* path);
Result CreateFile(char const* filepath, s64 size);
Result OpenFile(nn::fs::FileHandle*, char const* path, s32);
Result SetFileSize(FileHandle fileHandle, s64 filesize);
void CloseFile(FileHandle fileHandle);
Result FlushFile(FileHandle fileHandle);
Result DeleteFile(char const* filepath);
Result ReadFile(u64* outSize, nn::fs::FileHandle handle, s64 offset, void* buffer, u64 bufferSize,
                const ReadOption& option);
Result ReadFile(u64* outSize, nn::fs::FileHandle handle, s64 offset, void* buffer, u64 bufferSize);
Result ReadFile(nn::fs::FileHandle handle, s64 offset, void* buffer, u64 bufferSize);
Result WriteFile(FileHandle handle, s64 fileOffset, void const* buff, u64 size,
                 WriteOption const& option);
Result GetFileSize(s64* size, FileHandle fileHandle);

// DIRECTORY
// there are three open modes; dir, file, all
Result OpenDirectory(DirectoryHandle* handle, char const* path, s32 openMode);
void CloseDirectory(DirectoryHandle directoryHandle);
Result ReadDirectory(s64*, DirectoryEntry*, DirectoryHandle directoryHandle, s64);
Result CreateDirectory(char const* directorypath);
Result GetDirectoryEntryCount(s64*, DirectoryHandle);

// SD
Result MountSdCard(char const*);
Result MountSdCardForDebug(char const*);
bool IsSdCardInserted();
Result FormatSdCard();
Result FormatSdCardDryRun();
bool IsExFatSupported();

Result MountHost(char const* mount, char const* path);
Result MountHostRoot();
Result UnmountHostRoot();

Result Unmount(char const* mount);

// BCAT
Result MountBcatSaveData(char const*, ApplicationId);
Result CreateBcatSaveData(ApplicationId, s64);

};  // namespace fs
};  // namespace nn
