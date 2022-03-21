#include <basis/seadNew.h>
#include <basis/seadRawPrint.h>
#include <filedevice/seadFileDevice.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/seadPath.h>
#include <heap/seadHeapMgr.h>
#include <math/seadMathCalcCommon.h>

namespace sead
{
bool FileHandle::close()
{
    if (!mOriginalDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mOriginalDevice->close(this);
}

bool FileHandle::tryClose()
{
    if (!mOriginalDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mOriginalDevice->tryClose(this);
}

bool FileHandle::flush()
{
    if (!mOriginalDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mOriginalDevice->flush(this);
}

bool FileHandle::tryFlush()
{
    if (!mOriginalDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mOriginalDevice->tryFlush(this);
}

u32 FileHandle::read(u8* outBuffer, u32 bytesToRead)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return 0;
    }
    return mDevice->read(this, outBuffer, bytesToRead);
}

bool FileHandle::tryRead(u32* actual_size, u8* data, u32 size)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mDevice->tryRead(actual_size, this, data, size);
}

u32 FileHandle::write(const u8* data, u32 size)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return 0;
    }
    return mDevice->write(this, data, size);
}

bool FileHandle::tryWrite(u32* actual_size, const u8* data, u32 size)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mDevice->tryWrite(actual_size, this, data, size);
}

bool FileHandle::seek(s32 offset, FileDevice::SeekOrigin origin)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mDevice->seek(this, offset, origin);
}

bool FileHandle::trySeek(s32 offset, FileDevice::SeekOrigin origin)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mDevice->trySeek(this, offset, origin);
}

u32 FileHandle::getCurrentSeekPos()
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return 0;
    }
    return mDevice->getCurrentSeekPos(this);
}

bool FileHandle::tryGetCurrentSeekPos(u32* pos)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mDevice->tryGetCurrentSeekPos(pos, this);
}

u32 FileHandle::getFileSize()
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return 0;
    }
    return mDevice->getFileSize(this);
}

bool FileHandle::tryGetFileSize(u32* size)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mDevice->tryGetFileSize(size, this);
}

bool DirectoryHandle::close()
{
    if (!mOriginalDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mOriginalDevice->closeDirectory(this);
}

bool DirectoryHandle::tryClose()
{
    if (!mOriginalDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mOriginalDevice->tryCloseDirectory(this);
}

u32 DirectoryHandle::read(DirectoryEntry* entries, u32 count)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mDevice->readDirectory(this, entries, count);
}

bool DirectoryHandle::tryRead(u32* actual_count, DirectoryEntry* entries, u32 count)
{
    if (!mDevice)
    {
        SEAD_ASSERT_MSG(false, "handle not opened");
        return false;
    }
    return mDevice->tryReadDirectory(actual_count, this, entries, count);
}

FileDevice::~FileDevice()
{
    if (FileDeviceMgr::instance() != NULL)
        FileDeviceMgr::instance()->unmount(this);
}

void FileDevice::traceFilePath(const SafeString& path) const
{
    doTracePath_(path);
}

void FileDevice::traceDirectoryPath(const SafeString& path) const
{
    doTracePath_(path);
}

void FileDevice::resolveFilePath(BufferedSafeString* out, const SafeString& path) const
{
    doResolvePath_(out, path);
}

void FileDevice::resolveDirectoryPath(BufferedSafeString* out, const SafeString& path) const
{
    doResolvePath_(out, path);
}

bool FileDevice::isMatchDevice_(const HandleBase* handle) const
{
    return handle->mDevice == this;
}

u8* FileDevice::doLoad_(LoadArg& arg)
{
    if (arg.buffer && arg.buffer_size == 0)
    {
        SEAD_WARN("arg.buffer is specified, but arg.buffer_size is zero");
        return nullptr;
    }

    if (arg.buffer_size_alignment % cBufferMinAlignment != 0)
    {
        SEAD_WARN(
            "arg.buffer_size_alignment[%u] is not multipe of FileDevice::cBufferMinAlignment[%u]",
            arg.buffer_size_alignment, cBufferMinAlignment);
        return nullptr;
    }

    FileHandle handle;
    if (!tryOpen(&handle, arg.path, FileDevice::cFileOpenFlag_ReadOnly, arg.div_size))
        return nullptr;

    u32 bytesToRead = arg.buffer_size;
    if (!arg.buffer || arg.check_read_entire_file)
    {
        u32 fileSize = 0;
        if (!tryGetFileSize(&fileSize, &handle))
            return nullptr;

        if (fileSize == 0)
        {
            SEAD_WARN("file_size is zero.[%s]", arg.path.cstr());
            return nullptr;
        }

        if (bytesToRead != 0)
        {
            if (bytesToRead < fileSize)
            {
                SEAD_WARN("arg.buffer_size[%u] is smaller than file size[%u]", bytesToRead,
                          fileSize);
                return nullptr;
            }

            if (arg.buffer_size_alignment && bytesToRead % arg.buffer_size_alignment != 0)
            {
                SEAD_WARN("arg.buffer_size[%u] is not multipe of arg.buffer_size_alignment[%u]",
                          bytesToRead, arg.buffer_size_alignment);
                return nullptr;
            }
        }
        else
        {
            if (arg.buffer_size_alignment)
            {
                bytesToRead = Mathu::roundUp(fileSize, arg.buffer_size_alignment);
            }
            else
            {
                bytesToRead = Mathi::roundUpPow2(fileSize, FileDevice::cBufferMinAlignment);
            }
        }
    }

    u8* buf = arg.buffer;
    bool allocated = false;

    if (buf == nullptr)
    {
        const s32 sign = (arg.alignment < 0) ? -1 : 1;
        s32 alignment = Mathi::abs(arg.alignment);
        alignment = sign * ((alignment < cBufferMinAlignment) ? cBufferMinAlignment : alignment);

        Heap* heap = arg.heap;
        if (!heap)
            heap = HeapMgr::instance()->getCurrentHeap();

        void* raw_buf = heap->tryAlloc(bytesToRead, alignment);
        if (!raw_buf)
        {
            if (arg.assert_on_alloc_fail)
            {
                SEAD_ASSERT_MSG(false, "alloc size[%u] failed in heap[%s] for file[%s]",
                                bytesToRead, heap->getName().cstr(), arg.path.cstr());
            }
            return nullptr;
        }
        buf = new (raw_buf) u8[bytesToRead];
        allocated = true;
    }

    u32 bytesRead = 0;
    if (!tryRead(&bytesRead, &handle, buf, bytesToRead))
    {
        if (allocated)
            delete[] buf;
        return nullptr;
    }

    if (!tryClose(&handle))
    {
        if (allocated)
            delete[] buf;
        return nullptr;
    }

    arg.read_size = bytesRead;
    arg.roundup_size = bytesToRead;
    arg.need_unload = allocated;

    return buf;
}

bool FileDevice::doSave_(FileDevice::SaveArg& arg)
{
    if (!arg.buffer)
    {
        SEAD_ASSERT_MSG(false, "arg.buffer must be set for save file[%s]", arg.path.cstr());
        return false;
    }

    FileHandle handle;
    if (!tryOpen(&handle, arg.path, cFileOpenFlag_WriteOnly))
        return false;

    const bool ret =
        arg.buffer_size == 0 || tryWrite(&arg.write_size, &handle, arg.buffer, arg.buffer_size);

    if (!tryClose(&handle))
        return false;

    return ret;
}

void FileDevice::doTracePath_(const SafeString& path) const
{
    SEAD_DEBUG_PRINT("[%s] %s\n", mDriveName.cstr(), path.cstr());
    FixedSafeString<512> out;
    doResolvePath_(&out, path);
    SEAD_DEBUG_PRINT("  -> %s\n", out.cstr());
}

void FileDevice::doResolvePath_(BufferedSafeString* out, const SafeString& path) const
{
    out->copy(path);
}

bool FileDevice::isAvailable() const
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    return doIsAvailable_();
}

u8* FileDevice::tryLoad(LoadArg& arg)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return NULL;

    return doLoad_(arg);
}

bool FileDevice::trySave(FileDevice::SaveArg& arg)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    return doSave_(arg);
}

FileDevice* FileDevice::tryOpen(FileHandle* handle, const SafeString& path, FileOpenFlag flag,
                                u32 divSize)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return nullptr;

    if (handle == nullptr)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return nullptr;
    }

    setFileHandleDivSize_(handle, divSize);
    FileDevice* device = doOpen_(handle, path, flag);
    setHandleBaseFileDevice_(handle, device);
    if (device)
        setHandleBaseOriginalFileDevice_(handle, this);

    return device;
}

bool FileDevice::tryClose(FileHandle* handle)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (handle == nullptr)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return false;
    }

    if (!isMatchDevice_(handle))
    {
        SEAD_ASSERT_MSG(false, "handle device miss match");
        return false;
    }

    bool closed = doClose_(handle);
    if (closed)
    {
        setHandleBaseFileDevice_(handle, nullptr);
        setHandleBaseOriginalFileDevice_(handle, nullptr);
    }

    return closed;
}

bool FileDevice::tryFlush(FileHandle* handle)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (!handle)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return false;
    }

    if (!isMatchDevice_(handle))
    {
        SEAD_ASSERT_MSG(false, "handle device miss match");
        return false;
    }

    return doFlush_(handle);
}

bool FileDevice::tryRemove(const SafeString& str)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    return doRemove_(str);
}

bool FileDevice::tryRead(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (handle == nullptr)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return false;
    }

    if (!isMatchDevice_(handle))
    {
        SEAD_ASSERT_MSG(false, "handle device miss match");
        return false;
    }

    if (outBuffer == nullptr)
    {
        SEAD_ASSERT_MSG(false, "buf is null");
        return false;
    }

    if (handle->mDivSize == 0)
    {
        const bool ret = doRead_(bytesRead, handle, outBuffer, bytesToRead);
        SEAD_ASSERT_MSG(!bytesRead || *bytesRead <= bytesToRead, "buffer overflow");
        return ret;
    }

    u32 totalReadSize = 0;

    do
    {
        u32 size =
            (static_cast<s32>(bytesToRead) < handle->mDivSize) ? bytesToRead : handle->mDivSize;
        u32 readSize = 0;

        if (!doRead_(&readSize, handle, outBuffer, size))
        {
            if (bytesRead != NULL)
                *bytesRead = totalReadSize;

            return false;
        }

        totalReadSize += readSize;
        if (readSize < size)
            break;

        outBuffer += readSize;
        bytesToRead -= size;
    } while (bytesToRead != 0);

    if (bytesRead != NULL)
        *bytesRead = totalReadSize;

    return true;
}

bool FileDevice::tryWrite(u32* bytesWritten, FileHandle* handle, const u8* inBuffer,
                          u32 bytesToWrite)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (handle == nullptr)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return false;
    }

    if (inBuffer == nullptr)
    {
        SEAD_ASSERT_MSG(false, "buf is null");
        return false;
    }

    if (!isMatchDevice_(handle))
    {
        SEAD_ASSERT_MSG(false, "handle device miss match");
        return false;
    }

    return doWrite_(bytesWritten, handle, inBuffer, bytesToWrite);
}

bool FileDevice::trySeek(FileHandle* handle, s32 offset, FileDevice::SeekOrigin origin)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (handle == nullptr)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return false;
    }

    if (!isMatchDevice_(handle))
    {
        SEAD_ASSERT_MSG(false, "handle device miss match");
        return false;
    }

    return doSeek_(handle, offset, origin);
}

bool FileDevice::tryGetCurrentSeekPos(u32* seekPos, FileHandle* handle)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (handle == NULL)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return false;
    }

    if (!isMatchDevice_(handle))
    {
        SEAD_ASSERT_MSG(false, "handle device miss match");
        return false;
    }

    if (seekPos == NULL)
    {
        SEAD_ASSERT_MSG(false, "pos is null");
        return false;
    }

    return doGetCurrentSeekPos_(seekPos, handle);
}

bool FileDevice::tryGetFileSize(u32* fileSize, const SafeString& path)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (fileSize == NULL)
    {
        SEAD_ASSERT_MSG(false, "size is null");
        return false;
    }

    return doGetFileSize_(fileSize, path);
}

bool FileDevice::tryGetFileSize(u32* size, FileHandle* handle)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (handle == nullptr)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return false;
    }

    if (size == nullptr)
    {
        SEAD_ASSERT_MSG(false, "size is null");
        return false;
    }

    return doGetFileSize_(size, handle);
}

bool FileDevice::tryIsExistFile(bool* exists, const SafeString& path)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (exists == NULL)
    {
        SEAD_ASSERT_MSG(false, "is_exist is null");
        return false;
    }

    return doIsExistFile_(exists, path);
}

bool FileDevice::tryIsExistDirectory(bool* exists, const SafeString& path)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (exists == NULL)
    {
        SEAD_ASSERT_MSG(false, "is_exist is null");
        return false;
    }

    return doIsExistDirectory_(exists, path);
}

FileDevice* FileDevice::tryOpenDirectory(DirectoryHandle* handle, const SafeString& path)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return NULL;

    if (handle == NULL)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return NULL;
    }

    FileDevice* device = doOpenDirectory_(handle, path);
    setHandleBaseFileDevice_(handle, device);
    if (device != NULL)
        setHandleBaseOriginalFileDevice_(handle, this);

    return device;
}

bool FileDevice::tryCloseDirectory(DirectoryHandle* handle)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (handle == NULL)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return false;
    }

    if (!isMatchDevice_(handle))
    {
        SEAD_ASSERT_MSG(false, "handle device miss match");
        return false;
    }

    bool closed = doCloseDirectory_(handle);
    if (closed)
    {
        setHandleBaseFileDevice_(handle, NULL);
        setHandleBaseOriginalFileDevice_(handle, NULL);
    }

    return closed;
}

bool FileDevice::tryReadDirectory(u32* entriesRead, DirectoryHandle* handle,
                                  DirectoryEntry* entries, u32 entriesToRead)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    if (handle == NULL)
    {
        SEAD_ASSERT_MSG(false, "handle is null");
        return false;
    }

    if (!isMatchDevice_(handle))
    {
        SEAD_ASSERT_MSG(false, "handle device miss match");
        return false;
    }

    u32 readCount = 0;
    bool success = doReadDirectory_(&readCount, handle, entries, entriesToRead);

    if (entriesRead != NULL)
        *entriesRead = readCount;

    if (readCount > entriesToRead)
    {
        SEAD_ASSERT_MSG(false, "buffer overflow");
        return false;
    }

    return success;
}

bool FileDevice::tryMakeDirectory(const SafeString& path, u32 _)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    return doMakeDirectory_(path, _);
}

bool FileDevice::tryMakeDirectoryWithParent(const SafeString& path, u32 x)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    bool exists = false;
    if (!doIsExistDirectory_(&exists, path))
        return false;

    if (exists)
        return true;

    FixedSafeString<512> dir_name;
    int num_existing_parents = 1;
    bool should_trim = true;
    bool reached_end = !Path::getDirectoryName(&dir_name, path);
    while (!reached_end)
    {
        exists = false;
        if (!tryIsExistDirectory(&exists, dir_name))
            return false;

        if (exists)
        {
            should_trim = false;
            break;
        }

        reached_end = !Path::getDirectoryName(&dir_name, dir_name);
        ++num_existing_parents;
    }
    if (should_trim)
        dir_name.trim(0);

    int num_path_components = 0;
    auto counting_iterator = path.tokenBegin("/");
    const auto end = path.tokenEnd("/");
    for (; end != counting_iterator; ++counting_iterator)
        ++num_path_components;

    auto it = path.tokenBegin("/");
    int num_levels_to_create = num_path_components - num_existing_parents;
    for (; end != it; ++it)
    {
        if (num_levels_to_create >= 1)
        {
            --num_levels_to_create;
            continue;
        }

        FixedSafeString<128> component;
        it.get(&component);

        if (dir_name != "")
            dir_name.append("/");

        dir_name.append(component);

        if (!tryMakeDirectory(dir_name, x))
            return false;
    }

    return true;
}

s32 FileDevice::getLastRawError() const
{
    return doGetLastRawError_();
}

HandleBuffer& FileDevice::getHandleBaseHandleBuffer_(HandleBase* handle) const
{
    return handle->mHandleBuffer;
}

void FileDevice::setFileHandleDivSize_(FileHandle* handle, u32 divSize) const
{
    handle->mDivSize = divSize;
}

void FileDevice::setHandleBaseFileDevice_(HandleBase* handle, FileDevice* device) const
{
    handle->mDevice = device;
}

void FileDevice::setHandleBaseOriginalFileDevice_(HandleBase* handle, FileDevice* device) const
{
    handle->mOriginalDevice = device;
}

}  // namespace sead
