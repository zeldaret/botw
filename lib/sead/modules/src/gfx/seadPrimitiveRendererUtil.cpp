#include <cmath>
#include <cstring>

#include <gfx/seadPrimitiveRendererUtil.h>
#include <prim/seadMemUtil.h>

namespace sead
{
namespace PrimitiveRendererUtil
{
void setQuadVertex(Vertex* vtx, u16* idx)
{
    static const Vertex cVtx[4] = {
        Vertex(Vector3f(-0.5f, 0.5f, 0.0f), Vector2f(0.0f, 1.0f), Color4f(0.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(0.5f, 0.5f, 0.0f), Vector2f(1.0f, 1.0f), Color4f(0.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(-0.5f, -0.5f, 0.0f), Vector2f(0.0f, 0.0f), Color4f(1.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(0.5f, -0.5f, 0.0f), Vector2f(1.0f, 0.0f), Color4f(1.0f, 0.0f, 0.0f, 0.0f))};

    static const u16 cIdx[6] = {0, 2, 1, 1, 2, 3};

    if (vtx != NULL)
        MemUtil::copy(vtx, cVtx, sizeof(cVtx));

    if (idx != NULL)
        MemUtil::copy(idx, cIdx, sizeof(cIdx));
}

void setLineVertex(Vertex* vtx, u16* idx)
{
    static const Vertex cVtx[2] = {
        Vertex(Vector3f(-0.5f, 0.0f, 0.0f), Vector2f(0.0f, 0.5f), Color4f(0.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(0.5f, 0.0f, 0.0f), Vector2f(1.0f, 0.5f), Color4f(1.0f, 0.0f, 0.0f, 0.0f))};

    static const u16 cIdx[2] = {0, 1};

    if (vtx != NULL)
        MemUtil::copy(vtx, cVtx, sizeof(cVtx));

    if (idx != NULL)
        MemUtil::copy(idx, cIdx, sizeof(cIdx));
}

void setCubeVertex(Vertex* vtx, u16* idx)
{
    static const Vertex cVtx[8] = {
        Vertex(Vector3f(-0.5f, -0.5f, -0.5f), Vector2f(0.0f, 0.0f),
               Color4f(1.0f / 3.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(-0.5f, 0.5f, -0.5f), Vector2f(0.0f, 1.0f), Color4f(0.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(-0.5f, 0.5f, 0.5f), Vector2f(1.0f, 1.0f),
               Color4f(1.0f / 3.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(-0.5f, -0.5f, 0.5f), Vector2f(1.0f, 0.0f),
               Color4f(2.0f / 3.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(0.5f, -0.5f, 0.5f), Vector2f(0.0f, 0.0f), Color4f(1.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(0.5f, 0.5f, 0.5f), Vector2f(0.0f, 1.0f),
               Color4f(2.0f / 3.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(0.5f, 0.5f, -0.5f), Vector2f(1.0f, 1.0f),
               Color4f(1.0f / 3.0f, 0.0f, 0.0f, 0.0f)),
        Vertex(Vector3f(0.5f, -0.5f, -0.5f), Vector2f(1.0f, 0.0f),
               Color4f(2.0f / 3.0f, 0.0f, 0.0f, 0.0f))};

    static const u16 cIdx[36] = {2, 1, 0, 3, 2, 0, 5, 2, 3, 4, 5, 3, 6, 5, 7, 7, 5, 4,
                                 1, 6, 0, 6, 7, 0, 0, 7, 3, 3, 7, 4, 1, 2, 6, 2, 5, 6};

    if (vtx != NULL)
        MemUtil::copy(vtx, cVtx, sizeof(cVtx));

    if (idx != NULL)
        MemUtil::copy(idx, cIdx, sizeof(cIdx));
}

void setWireCubeVertex(Vertex* vtx, u16* idx)
{
    setCubeVertex(vtx, NULL);

    static const u16 cIdx[17] = {0, 1, 2, 3, 0, 7, 6, 1, 2,
                                 5, 6, 7, 4, 5, 4, 3, 0

    };

    if (idx != NULL)
        MemUtil::copy(idx, cIdx, sizeof(cIdx));
}

void setSphereVertex(Vertex* vtx, u16* idx, s32 x, s32 y)
{
    if (vtx != NULL)
    {
        for (s32 i = 0; i < y; i++)
        {
            f32 angle_y = ((i + 1) / (y + 1.0f) - 0.5f) * M_PI;

            f32 pos_y = sinf(angle_y) * 0.5f;
            f32 radius = cosf(angle_y) * 0.5f;

            for (s32 j = 0; j < x; j++)
            {
                s32 pos = i * x + j;
                f32 angle_x = (M_PI * 2.0f) * j / x;
                if (i % 2 == 0)
                    angle_x -= (M_PI * 2.0f) / x / 2;

                f32 pos_x = cosf(angle_x) * radius;
                f32 pos_z = sinf(angle_x) * radius;

                vtx[pos].pos.x = pos_x;
                vtx[pos].pos.y = pos_y;
                vtx[pos].pos.z = pos_z;
                vtx[pos].uv.x = pos_y + 0.5f;
                vtx[pos].uv.y = static_cast<f32>(j) / x;
                vtx[pos].color.r = 0.5f - pos_y;
            }
        }

        {
            s32 pos = x * y;

            vtx[pos].pos.x = 0.0f;
            vtx[pos].pos.y = -0.5f;
            vtx[pos].pos.z = 0.0f;
            vtx[pos].uv.x = 0.0f;
            vtx[pos].uv.y = 0.5f;
            vtx[pos].color.r = 1.0f;
        }

        {
            s32 pos = x * y + 1;

            vtx[pos].pos.x = 0.0f;
            vtx[pos].pos.y = 0.5f;
            vtx[pos].pos.z = 0.0f;
            vtx[pos].uv.x = 1.0f;
            vtx[pos].uv.y = 0.5f;
            vtx[pos].color.r = 0.0f;
        }
    }

    if (idx != NULL)
    {
        for (s32 i = 0; i < x; i++)
        {
            idx[i * 3 + 0] = x * y;
            idx[i * 3 + 1] = i;
            idx[i * 3 + 2] = (i + 1) % x;
        }

        for (s32 i = 0; i < y - 1; i++)
        {
            for (s32 j = 0; j < x; j++)
            {
                s32 offset = i % 2;
                s32 pos = (i * x * 6) + j * 6 + x * 3;

                idx[pos + 0] = i * x + j;
                idx[pos + 1] = (i + 1) * x + ((j + offset) % x);
                idx[pos + 2] = i * x + ((j + 1) % x);
                idx[pos + 3] = (i + 1) * x + ((j + offset) % x);
                idx[pos + 4] = (i + 1) * x + ((j + 1 + offset) % x);
                idx[pos + 5] = i * x + ((j + 1) % x);
            }
        }

        for (s32 i = 0; i < x; i++)
        {
            s32 posOffs = 3 * x * (y - 1) * 2 + x * 3;

            idx[i * 3 + 0 + posOffs] = x * y + 1;
            idx[i * 3 + 1 + posOffs] = x * (y - 1) + ((i + 1) % x);
            idx[i * 3 + 2 + posOffs] = x * (y - 1) + i;
        }
    }
}

void setDiskVertex(Vertex* vtx, u16* idx, s32 div)
{
    if (vtx != NULL)
    {
        for (s32 i = 0; i < div; i++)
        {
            f32 angle = (M_PI * 2.0f) * i / div;

            vtx[i].pos.x = cosf(angle) * 0.5f;
            vtx[i].pos.y = sinf(angle) * 0.5f;
            vtx[i].pos.z = 0.0f;
            vtx[i].uv.x = vtx[i].pos.x;
            vtx[i].uv.y = 1.0f - vtx[i].pos.y;
            vtx[i].color.r = 1.0f;
        }

        {
            s32 i = div;

            vtx[i].pos.x = 0.0f;
            vtx[i].pos.y = 0.0f;
            vtx[i].pos.z = 0.0f;
            vtx[i].uv.x = 0.5f;
            vtx[i].uv.y = 0.5f;
            vtx[i].color.r = 0.0f;
        }
    }

    if (idx != NULL)
        for (s32 i = 0; i < div; i++)
        {
            idx[i * 3 + 0] = i;
            idx[i * 3 + 1] = (i + 1) % div;
            idx[i * 3 + 2] = div;
        }
}

void setCylinderVertex(Vertex* vtx, u16* idx, s32 div)
{
    if (vtx != NULL)
    {
        for (s32 i = 0; i < div; i++)
        {
            f32 angle = (M_PI * 2.0f) * i / div;

            vtx[i].pos.x = cosf(angle) * 0.5f;
            vtx[i].pos.z = -sinf(angle) * 0.5f;
            vtx[i].pos.y = 0.5f;
            vtx[i].uv.x = vtx[i].pos.x;
            vtx[i].uv.y = 1.0f - vtx[i].pos.z;
            vtx[i].color.r = 0.0f;

            s32 pos = i + div + 1;

            vtx[pos].pos.x = cosf(angle) * 0.5f;
            vtx[pos].pos.z = -sinf(angle) * 0.5f;
            vtx[pos].pos.y = -0.5f;
            vtx[pos].uv.x = vtx[i].pos.x;
            vtx[pos].uv.y = 1.0f - vtx[i].pos.z;
            vtx[pos].color.r = 1.0f;
        }

        {
            s32 pos = div;

            vtx[pos].pos.x = 0.0f;
            vtx[pos].pos.y = 0.5f;
            vtx[pos].pos.z = 0.0f;
            vtx[pos].uv.x = 0.5f;
            vtx[pos].uv.y = 0.5f;
            vtx[pos].color.r = 0.0f;
        }

        {
            s32 pos = div + div + 1;

            vtx[pos].pos.x = 0.0f;
            vtx[pos].pos.y = -0.5f;
            vtx[pos].pos.z = 0.0f;
            vtx[pos].uv.x = 0.5f;
            vtx[pos].uv.y = 0.5f;
            vtx[pos].color.r = 1.0f;
        }
    }

    if (idx != NULL)
    {
        for (s32 i = 0; i < div; i++)
        {
            idx[i * 3 + 0] = i;
            idx[i * 3 + 1] = (i + 1) - ((i + 1) % div);
            idx[i * 3 + 2] = div;

            s32 posOffs = div * 3;
            idx[i * 3 + 0 + posOffs] = i + (div + 1);
            idx[i * 3 + 1 + posOffs] = div + (div + 1);
            idx[i * 3 + 2 + posOffs] = ((i + 1) - ((i + 1) % div)) + (div + 1);
        }

        for (s32 i = 0; i < div; i++)
        {
            s32 posOffs = div * 6;

            idx[i * 6 + 0 + posOffs] = i;
            idx[i * 6 + 1 + posOffs] = i + (div + 1);
            idx[i * 6 + 2 + posOffs] = (i + 1) - ((i + 1) % div);
            idx[i * 6 + 3 + posOffs] = (i + 1) - ((i + 1) % div);
            idx[i * 6 + 4 + posOffs] = i + (div + 1);
            idx[i * 6 + 5 + posOffs] = ((i + 1) - ((i + 1) % div)) + (div + 1);
        }
    }
}

}  // namespace PrimitiveRendererUtil
}  // namespace sead
