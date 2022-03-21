#include <filedevice/seadPath.h>
#include <prim/seadSafeString.h>

namespace sead
{
bool Path::getDriveName(BufferedSafeString* driveName, const SafeString& path)
{
    SEAD_ASSERT_MSG(driveName, "destination buffer is null");

    driveName->trim(0);

    const s32 index = path.findIndex(":");
    if (index == -1)
        return false;

    driveName->copy(path, index);
    return true;
}

void Path::getPathExceptDrive(BufferedSafeString* pathNoDrive, const SafeString& path)
{
    SEAD_ASSERT_MSG(pathNoDrive, "destination buffer is null");

    pathNoDrive->trim(0);

    s32 index = path.findIndex("://");
    if (index == -1)
        pathNoDrive->copyAt(0, path);

    else
        pathNoDrive->copyAt(0, path.getPart(index + 3));
}

namespace
{
s32 rfindCharIndex(const SafeString& path, char c)
{
    const s32 length = path.calcLength();
    const char* cstr = path.cstr();
    for (s32 i = length; i >= 0; --i)
        if (cstr[i] == c)
            return i;
    return -1;
}

char getLastChar(const SafeString& str)
{
    return str.at(str.calcLength() - 1);
}
}  // namespace

// NON_MATCHING: redundant checks for dot_index < 0 in SafeString::getPart() are optimized out
bool Path::getExt(BufferedSafeString* ext, const SafeString& path)
{
    SEAD_ASSERT_MSG(ext, "destination buffer is null");

    ext->trim(0);

    const s32 dot_index = rfindCharIndex(path, '.');
    if (dot_index < 0)
        return false;

    if (path.getPart(dot_index).include('/') || path.getPart(dot_index).include('\\'))
        return false;

    ext->copy(path.getPart(dot_index + 1));
    return true;
}

bool Path::getFileName(BufferedSafeString* name, const SafeString& path)
{
    SEAD_ASSERT_MSG(name, "destination buffer is null");
    name->trim(0);

    const s32 slash_index = rfindCharIndex(path, '/');
    const s32 bslash_index = rfindCharIndex(path, '\\');
    const s32 idx = slash_index > bslash_index ? slash_index : bslash_index;
    name->copy(path.getPart(idx + 1));
    return true;
}

bool Path::getBaseFileName(BufferedSafeString* name, const SafeString& path)
{
    const s32 bslash_index = rfindCharIndex(path, '\\');
    const s32 slash_index = rfindCharIndex(path, '/');

    const s32 i = bslash_index > slash_index ? bslash_index : slash_index;
    const s32 part_idx = i < 0 ? 0 : i + 1;

    s32 dot_idx = rfindCharIndex(path, '.');
    if (dot_idx < 0)
        dot_idx = path.calcLength();

    name->copy(path.getPart(part_idx), dot_idx - part_idx);
    return true;
}

bool Path::getDirectoryName(BufferedSafeString* name, const SafeString& path)
{
    SEAD_ASSERT_MSG(name, "destination buffer is null");

    if (name == &path)
    {
        const s32 slash_index = rfindCharIndex(path, '/');
        const s32 bslash_index = rfindCharIndex(path, '\\');
        const s32 trim_index = slash_index > bslash_index ? slash_index : bslash_index;
        if (trim_index < 1)
            return false;

        name->trim(trim_index);
    }
    else
    {
        name->trim(0);

        const s32 slash_index = rfindCharIndex(path, '/');
        const s32 bslash_index = rfindCharIndex(path, '\\');
        const s32 trim_index = slash_index > bslash_index ? slash_index : bslash_index;
        if (trim_index < 1)
            return false;

        name->copy(path, trim_index);
    }
    return true;
}

void Path::join(BufferedSafeString* out, const char* path1, const char* path2)
{
    // Trivial case 1: path1 is empty.
    if (!path1 || !path1[0])
    {
        out->copy(path2);
        return;
    }

    // Trivial case 2: path2 is empty.
    if (!path2 || !path2[0])
    {
        out->copy(path1);
        return;
    }

    if (path2[0] == '\\' || path2[0] == '/')
    {
        // If path1 also ends with a slash, skip the slash in path2 to avoid getting "//".
        const char last_char1 = getLastChar(path1);
        if (last_char1 == '\\' || last_char1 == '/')
        {
            ++path2;
            if (!path2[0])
            {
                out->copy(path1);
                return;
            }
        }
        out->format("%s%s", path1, path2);
    }
    else
    {
        // If path1 already ends with a slash, do not insert "/" in the middle to avoid "//".
        const char last_char1 = getLastChar(path1);
        if (last_char1 == '\\' || last_char1 == '/')
            out->format("%s%s", path1, path2);
        else
            out->format("%s/%s", path1, path2);
    }
}

void Path::changeDelimiter(BufferedSafeString* out, char delimiter)
{
    const s32 length = out->calcLength();
    char* buffer = out->getBuffer();
    for (s32 i = 0; i < length; ++i)
    {
        const char c = (*out)[i];
        if (c == '\\' || c == '/')
            buffer[i] = delimiter;
    }
}
}  // namespace sead
