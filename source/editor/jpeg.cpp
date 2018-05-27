#include <turbojpeg.h>
#include "common.h"

#define TPC_SIZE        0x1400
#define TPC_MAX_WIDTH   64
#define TPC_MAX_HEIGHT  104

#define TEXTURE_TRANSFER_FLAGS \
    (GX_TRANSFER_FLIP_VERT(1) | GX_TRANSFER_OUT_TILED(1) | GX_TRANSFER_RAW_COPY(0) | \
    GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGBA8) | \
    GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

static inline u32 Pow2(u32 x)
{
    if (x <= 2)
        return x;
    
    return 1u << (32- __builtin_clz(x - 1));
}

typedef struct jpeg_info
{
    unsigned width;
    unsigned height;
    void* image;
} jpeg_info;

jpeg_info decompress_jpeg(const void* buffer, long jpegSize)
{
    int jpegSubsamp, width, height;
    u64 texSize;
    u8* outbuf;
    
    tjhandle jpegDecompressor = tjInitDecompress();
    tjDecompressHeader2(jpegDecompressor, (unsigned char*)buffer, jpegSize, &width, &height, &jpegSubsamp); //For getting width & height of image

    texSize = TJBUFSIZE(width, height);
    outbuf = (u8 *)malloc(texSize);

    tjDecompress2(jpegDecompressor, (unsigned char*)buffer, jpegSize, outbuf, width, 0, height, TJPF_ABGR, TJFLAG_FASTDCT); //Decompress image

    jpeg_info jpeg = {static_cast<unsigned int>(width), static_cast<unsigned int>(height), outbuf};
    tjDestroy(jpegDecompressor);
    return jpeg;
}

static int  LoadJPEG(C3D_Tex **out, u16& width, u16& height, const void *tpcData)
{
    C3D_Tex *   tex;
    jpeg_info   jpeg = decompress_jpeg(tpcData, TPC_SIZE);
    // Check jpeg boundaries
    if (jpeg.width > TPC_MAX_WIDTH || jpeg.height > TPC_MAX_HEIGHT)
        return -1;
    // Pass the real size of the image for the C2D_Image
    width = jpeg.width;
    height = jpeg.height;
    // Create a new texture with valid sizes (pow2)
    tex = new C3D_Tex;
    C3D_TexInit(tex, Pow2(width), Pow2(height), GPU_RGBA8);
    // Set anti-aliasing params
    tex->param = GPU_TEXTURE_MAG_FILTER(GPU_LINEAR) | GPU_TEXTURE_MIN_FILTER(GPU_LINEAR)
        | GPU_TEXTURE_WRAP_S(GPU_CLAMP_TO_EDGE) | GPU_TEXTURE_WRAP_T(GPU_CLAMP_TO_EDGE);
    // Copy the data to texture tiled
    C3D_SyncDisplayTransfer((u32 *)jpeg.image, GX_BUFFER_DIM(tex->width, tex->height), \
        (u32 *)tex->data, GX_BUFFER_DIM(tex->width, tex->height), TEXTURE_TRANSFER_FLAGS);
    gspWaitForPPF();
    C3D_TexFlush(*out);
    // Release temporary buffer
    linearFree(jpeg.image);
    *out = tex;
    return 0;
}

C2D_Image LoadPlayerPicture(const void *tpcData)
{
    u16                 width, height;
    C2D_Image           image;
    Tex3DS_SubTexture * subtex = new Tex3DS_SubTexture;
    // Create the C3D_Tex
    LoadJPEG(&image.tex, width, height, tpcData);
    // Create the subtext coords
    subtex->width = width;
    subtex->height = height;
    subtex->left = 0.f;
    subtex->top = 0.f;
    subtex->right = (float)width / (float)image.tex->width;
    subtex->bottom = (float)height / (float)image.tex->height;
    image.subtex = subtex;
    return image;
}

void C2D_Image_Destroy(C2D_Image image)
{
    C3D_TexDelete(image.tex);
    delete image.tex;
    delete image.subtex;
}