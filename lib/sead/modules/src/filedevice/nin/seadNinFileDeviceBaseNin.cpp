#include "filedevice/nin/seadNinFileDeviceBaseNin.h"
#include "filedevice/seadPath.h"

namespace sead
{
struct NinFileDeviceBase::FileHandleInner
{
    nn::fs::FileHandle mHandle;
    s64 mOffset;
    bool mIsWriteMode;
    bool mDoNotFlushOnClose;
};

struct NinFileDeviceBase::DirectoryHandleInner
{
    nn::fs::DirectoryHandle mHandle;
};

NinFileDeviceBase::NinFileDeviceBase(const SafeString& name, const SafeString& mount_point)
    : FileDevice(name), mMountPoint(mount_point)
{
}

bool NinFileDeviceBase::doIsAvailable_() const
{
    return true;
}

// NON_MATCHING: inverted branching for should_set_size
FileDevice* NinFileDeviceBase::doOpen_(FileHandle* handle, const SafeString& path,
                                       FileDevice::FileOpenFlag flag)
{
    static constexpr u32 sModes[4] = {
        nn::fs::OpenMode_Read,
        nn::fs::OpenMode_Write | nn::fs::OpenMode_Append,
        nn::fs::OpenMode_ReadWrite | nn::fs::OpenMode_Append,
        nn::fs::OpenMode_Write | nn::fs::OpenMode_Append,
    };
    const u32 mode = flag <= 3u ? sModes[s32(flag)] : u32(nn::fs::OpenMode_Read);

    FixedSafeString<256> fs_path;
    if (!formatPathForFS_(&fs_path, path))
    {
        mLastError = nn::fs::ResultUnexpected();
        SEAD_WARN("invalid path. path = %s", fs_path.cstr());
        return nullptr;
    }

    bool should_set_size = true;
    if ((flag | cFileOpenFlag_ReadWrite) == cFileOpenFlag_Create)
    {
        bool is_file = false;
        nn::fs::DirectoryEntryType type;
        const auto result = nn::fs::GetEntryType(&type, fs_path.cstr());
        if (result.IsSuccess())
        {
            is_file = type == nn::fs::DirectoryEntryType_File;
        }
        else if (!nn::fs::ResultPathNotFound().Includes(result))
        {
            SEAD_WARN("nn::fs::GetEntryType failed. module = %d desc = %d inner_value = 0x%08x "
                      "path = %s",
                      result.GetModule(), result.GetDescription(), result.GetInnerValueForDebug(),
                      fs_path.cstr());
            mLastError = result;
            return nullptr;
        }

        should_set_size = flag == cFileOpenFlag_Create || !is_file;
        if (flag == cFileOpenFlag_Create || !is_file)
        {
            if (is_file)
            {
                mLastError = nn::fs::ResultPathAlreadyExists();
                return nullptr;
            }
            const auto create_result = nn::fs::CreateFile(fs_path.cstr(), 0);
            if (create_result.IsFailure())
            {
                SEAD_WARN("nn::fs::CreateFile failed. module = %d desc = %d inner_value = 0x%08x "
                          "path = %s",
                          create_result.GetModule(), create_result.GetDescription(),
                          create_result.GetInnerValueForDebug(), fs_path.cstr());
                mLastError = create_result;
                return nullptr;
            }
        }
    }

    auto* handle_inner = getFileHandleInner_(handle, true);
    handle_inner->mOffset = 0;
    handle_inner->mIsWriteMode = (mode >> 1) & 1;
    handle_inner->mDoNotFlushOnClose = false;

    const auto open_result = nn::fs::OpenFile(&handle_inner->mHandle, fs_path.cstr(), mode);
    mLastError = open_result;
    if (open_result.IsFailure())
    {
        if (!nn::fs::ResultPathNotFound().Includes(open_result))
            SEAD_WARN(
                "nn::fs::OpenFile failed. module = %d desc = %d inner_value = 0x%08x path = %s",
                open_result.GetModule(), open_result.GetDescription(),
                open_result.GetInnerValueForDebug(), fs_path.cstr());
        return nullptr;
    }

    if (flag == cFileOpenFlag_WriteOnly && !should_set_size)
    {
        const auto set_result = nn::fs::SetFileSize(handle_inner->mHandle, 0);
        if (set_result.IsFailure())
        {
            SEAD_WARN("nn::fs::SetFileSize failed. module = %d desc = %d inner_value = 0x%08x path "
                      "= %s",
                      set_result.GetModule(), set_result.GetDescription(),
                      set_result.GetInnerValueForDebug(), fs_path.cstr());
            nn::fs::CloseFile(handle_inner->mHandle);
            mLastError = set_result;
            return nullptr;
        }
    }

    return this;
}

bool NinFileDeviceBase::doClose_(FileHandle* handle)
{
    const auto* inner = getFileHandleInner_(handle);

    if (inner->mIsWriteMode && !inner->mDoNotFlushOnClose)
    {
        const auto result = nn::fs::FlushFile(inner->mHandle);
        if (result.IsFailure())
        {
            mLastError = result;
            nn::fs::CloseFile(inner->mHandle);
            return false;
        }
    }

    nn::fs::CloseFile(inner->mHandle);
    mLastError = nn::ResultSuccess();
    return true;
}

bool NinFileDeviceBase::doFlush_(FileHandle* handle)
{
    auto* inner = getFileHandleInner_(handle);

    mLastError = nn::fs::FlushFile(inner->mHandle);
    if (mLastError.IsFailure())
    {
        inner->mDoNotFlushOnClose = true;
        return false;
    }
    return true;
}

bool NinFileDeviceBase::doRemove_(const SafeString& path)
{
    FixedSafeString<256> fs_path;
    if (!formatPathForFS_(&fs_path, path))
    {
        mLastError = nn::fs::ResultUnexpected();
        SEAD_WARN("invalid path. path = %s.", path.cstr());
        return false;
    }

    mLastError = nn::fs::DeleteFile(fs_path.cstr());
    if (mLastError.IsFailure())
    {
        SEAD_WARN("nn::fs::DeleteFile failed. module = %d desc = %d inner_value = 0x%08x path = %s",
                  mLastError.GetModule(), mLastError.GetDescription(),
                  mLastError.GetInnerValueForDebug(), fs_path.cstr());
        return false;
    }
    return true;
}

bool NinFileDeviceBase::doRead_(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead)
{
    auto* inner = getFileHandleInner_(handle);

    u64 out_size = 0;
    mLastError = nn::fs::ReadFile(&out_size, inner->mHandle, inner->mOffset, outBuffer, bytesToRead,
                                  nn::fs::ReadOption{});
    if (mLastError.IsFailure())
    {
        SEAD_WARN("nn::fs::ReadFile failed. module = %d desc = %d inner_value = 0x%08x",
                  mLastError.GetModule(), mLastError.GetDescription(),
                  mLastError.GetInnerValueForDebug());
        return false;
    }

    inner->mOffset += out_size;
    if (bytesRead)
        *bytesRead = out_size;

    return true;
}

bool NinFileDeviceBase::doWrite_(u32* bytesWritten, FileHandle* handle, const u8* inBuffer,
                                 u32 bytesToWrite)
{
    auto* inner = getFileHandleInner_(handle);

    mLastError = nn::fs::WriteFile(inner->mHandle, inner->mOffset, inBuffer, bytesToWrite,
                                   nn::fs::WriteOption{});
    if (mLastError.IsSuccess())
    {
        inner->mOffset += bytesToWrite;
        if (bytesWritten)
            *bytesWritten = bytesToWrite;
        return true;
    }

    SEAD_WARN("nn::fs::WriteFile failed. module = %d desc = %d inner_value = 0x%08x",
              mLastError.GetModule(), mLastError.GetDescription(),
              mLastError.GetInnerValueForDebug());
    inner->mDoNotFlushOnClose = true;
    return false;
}

bool NinFileDeviceBase::doSeek_(FileHandle* handle, s32 offset, FileDevice::SeekOrigin origin)
{
    auto* inner = getFileHandleInner_(handle);
    switch (origin)
    {
    case FileDevice::cSeekOrigin_Begin:
        inner->mOffset = offset;
        return true;
    case FileDevice::cSeekOrigin_Current:
        inner->mOffset += offset;
        return true;
    case FileDevice::cSeekOrigin_End:
    {
        SEAD_ASSERT(offset <= 0);
        u32 file_size = 0;
        if (!doGetFileSize_(&file_size, handle))
            break;
        inner->mOffset = file_size + offset;
        return true;
    }
    }
    return false;
}

bool NinFileDeviceBase::doGetCurrentSeekPos_(u32* seekPos, FileHandle* handle)
{
    *seekPos = getFileHandleInner_(handle)->mOffset;
    return true;
}

bool NinFileDeviceBase::doGetFileSize_(u32* fileSize, const SafeString& path)
{
    FileHandle handle;
    if (!doOpen_(&handle, path, cFileOpenFlag_ReadOnly))
        return false;

    const bool ret = doGetFileSize_(fileSize, &handle);
    doClose_(&handle);
    return ret;
}

bool NinFileDeviceBase::doGetFileSize_(u32* fileSize, FileHandle* handle)
{
    const auto* inner = getFileHandleInner_(handle);
    s64 size = 0;
    mLastError = nn::fs::GetFileSize(&size, inner->mHandle);
    if (mLastError.IsSuccess())
    {
        *fileSize = size;
        return true;
    }

    SEAD_WARN("nn::fs::GetFileSize failed. module = %d desc = %d inner_value = 0x%08x",
              mLastError.GetModule(), mLastError.GetDescription(),
              mLastError.GetInnerValueForDebug());
    return false;
}

bool NinFileDeviceBase::doIsExistFile_(bool* exists, const SafeString& path)
{
    FixedSafeString<256> fs_path;
    if (!formatPathForFS_(&fs_path, path))
    {
        mLastError = nn::fs::ResultUnexpected();
        SEAD_WARN("invalid path. path = %s.", fs_path.cstr());
        return false;
    }

    nn::fs::DirectoryEntryType type;
    mLastError = nn::fs::GetEntryType(&type, fs_path.cstr());

    if (mLastError.IsSuccess())
    {
        *exists = type == nn::fs::DirectoryEntryType_File;
        return true;
    }

    if (nn::fs::ResultPathNotFound().Includes(mLastError))
    {
        *exists = false;
        return true;
    }

    SEAD_WARN("nn::fs::GetEntryType failed. module = %d desc = %d inner_value = 0x%08x path = %s",
              mLastError.GetModule(), mLastError.GetDescription(),
              mLastError.GetInnerValueForDebug(), fs_path.cstr());
    return false;
}

bool NinFileDeviceBase::doIsExistDirectory_(bool* exists, const SafeString& path)
{
    FixedSafeString<256> fs_path;
    if (!formatPathForFS_(&fs_path, path))
    {
        mLastError = nn::fs::ResultUnexpected();
        SEAD_WARN("invalid path. path = %s.", fs_path.cstr());
        return false;
    }

    nn::fs::DirectoryEntryType type;
    mLastError = nn::fs::GetEntryType(&type, fs_path.cstr());

    if (mLastError.IsSuccess())
    {
        *exists = type == nn::fs::DirectoryEntryType_Directory;
        return true;
    }

    if (nn::fs::ResultPathNotFound().Includes(mLastError))
    {
        *exists = false;
        return true;
    }

    SEAD_WARN("nn::fs::GetEntryType failed. module = %d desc = %d inner_value = 0x%08x path = %s",
              mLastError.GetModule(), mLastError.GetDescription(),
              mLastError.GetInnerValueForDebug(), fs_path.cstr());
    return false;
}

FileDevice* NinFileDeviceBase::doOpenDirectory_(DirectoryHandle* handle, const SafeString& path)
{
    auto* inner = getDirectoryHandleInner_(handle, true);

    FixedSafeString<256> fs_path;
    if (!formatPathForFS_(&fs_path, path))
    {
        mLastError = nn::fs::ResultUnexpected();
        SEAD_WARN("invalid path. path = %s.", fs_path.cstr());
        return nullptr;
    }

    mLastError =
        nn::fs::OpenDirectory(&inner->mHandle, fs_path.cstr(), nn::fs::OpenDirectoryMode_All);
    if (mLastError.IsSuccess())
        return this;

    if (nn::fs::ResultPathNotFound().Includes(mLastError))
        return nullptr;

    SEAD_WARN("nn::fs::OpenDirectory failed. module = %d desc = %d inner_value = 0x%08x path = %s",
              mLastError.GetModule(), mLastError.GetDescription(),
              mLastError.GetInnerValueForDebug(), fs_path.cstr());
    return nullptr;
}

bool NinFileDeviceBase::doCloseDirectory_(DirectoryHandle* handle)
{
    nn::fs::CloseDirectory(getDirectoryHandleInner_(handle)->mHandle);
    return true;
}

bool NinFileDeviceBase::doReadDirectory_(u32* entries_read, DirectoryHandle* handle,
                                         DirectoryEntry* entries, u32 num_entries)
{
    const auto* inner = getDirectoryHandleInner_(handle);

    for (u32 i = 0; i < num_entries; ++i)
    {
        nn::fs::DirectoryEntry entry;
        s64 count = 0;
        mLastError = nn::fs::ReadDirectory(&count, &entry, inner->mHandle, 1);
        if (mLastError.IsFailure())
        {
            SEAD_WARN("nn::fs::ReadDirectory failed. module = %d desc = %d inner_value = 0x%08x",
                      mLastError.GetModule(), mLastError.GetDescription(),
                      mLastError.GetInnerValueForDebug());
            return false;
        }

        // No more entries to read.
        if (count != 1)
        {
            if (entries_read)
                *entries_read = i;
            return true;
        }

        entries[i].name = entry.name;
        entries[i].is_directory = entry.type == nn::fs::DirectoryEntryType_Directory;
    }

    if (entries_read)
        *entries_read = num_entries;
    return true;
}

bool NinFileDeviceBase::doMakeDirectory_(const SafeString& path, u32)
{
    FixedSafeString<256> fs_path;
    if (!formatPathForFS_(&fs_path, path))
    {
        mLastError = nn::fs::ResultUnexpected();
        SEAD_WARN("invalid path. path = %s.", fs_path.cstr());
        return false;
    }

    const auto result = nn::fs::CreateDirectory(fs_path.cstr());
    mLastError = result;
    if (result.IsSuccess())
        return true;

    SEAD_WARN("nn::fs::CreateDirectory[%s] failed. module = %d desc = %d inner_value = 0x%08x",
              fs_path.cstr(), result.GetModule(), result.GetDescription(),
              result.GetInnerValueForDebug());
    return false;
}

s32 NinFileDeviceBase::doGetLastRawError_() const
{
    return mLastError.GetInnerValueForDebug();
}

void NinFileDeviceBase::doResolvePath_(BufferedSafeString* out, const SafeString& path) const
{
    formatPathForFS_(out, path);
}

bool NinFileDeviceBase::formatPathForFS_(BufferedSafeString* out, const SafeString& path) const
{
    out->format("%s:/%s", mMountPoint.cstr(), path.cstr());
    Path::changeDelimiter(out, '/');
    return true;
}

NinFileDeviceBase::FileHandleInner* NinFileDeviceBase::getFileHandleInner_(HandleBase* handle,
                                                                           bool construct) const
{
    auto* buffer = getHandleBaseHandleBuffer_(handle).getBufferPtr();
    static_assert(sizeof(FileHandleInner) <= sizeof(HandleBuffer));
    static_assert(alignof(FileHandleInner) <= alignof(HandleBase));
    if (construct)
        return new (buffer) FileHandleInner;
    return reinterpret_cast<FileHandleInner*>(buffer);
}

NinFileDeviceBase::DirectoryHandleInner*
NinFileDeviceBase::getDirectoryHandleInner_(HandleBase* handle, bool construct) const
{
    auto* buffer = getHandleBaseHandleBuffer_(handle).getBufferPtr();
    static_assert(sizeof(DirectoryHandleInner) <= sizeof(HandleBuffer));
    static_assert(alignof(DirectoryHandleInner) <= alignof(HandleBase));
    if (construct)
        return new (buffer) DirectoryHandleInner;
    return reinterpret_cast<DirectoryHandleInner*>(buffer);
}
}  // namespace sead
