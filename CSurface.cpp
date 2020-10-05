
#include "CSurface.h"
#include "Define.h"

CSurface::CSurface() 
{
    
}

SDL_Surface* CSurface::Load(std::string File, bool alpha) 
{    
    SDL_Surface* STemp = NULL;
    SDL_Surface* SReturn = NULL;
    
    if((STemp = IMG_Load(File.c_str())) == NULL)
        return NULL;
    
    if (alpha)
        SReturn = SDL_DisplayFormatAlpha(STemp);
    else
    {
        SReturn = SDL_DisplayFormat(STemp);
        
        // Set Transparency color to RGB(255,0,255)
        Transparent(SReturn, 255, 0, 255);
    }
    
    SDL_FreeSurface(STemp);
    STemp = NULL;
    
    return SReturn;
}

bool CSurface::Draw(SDL_Surface* SDest, SDL_Surface* SSrc, int X, int Y) 
{
    if(SDest == NULL || SSrc == NULL)
        return false;
    
    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_BlitSurface(SSrc, NULL, SDest, &DestR);

    return true;
}


bool CSurface::Draw(SDL_Surface* SDest, SDL_Surface* SSrc, int X, int Y, int X2, int Y2, int W, int H) 
{
    if(SDest == NULL || SSrc == NULL) 
        return false;
    
    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_Rect SrcR;

    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;

    SDL_BlitSurface(SSrc, &SrcR, SDest, &DestR);

    return true;
}

bool CSurface::Transparent(SDL_Surface* SDest, int R, int G, int B) 
{
    if(SDest == NULL) 
        return false;
   
    SDL_SetColorKey(SDest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(SDest->format, R, G, B));

    return true;
}


Uint32 CSurface::getpixel(SDL_Surface *surface, int x, int y)
{
    SDL_LockSurface(surface);
    
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    SDL_UnlockSurface(surface);
    
    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void CSurface::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    // Bounds Check
    y = (y < 0) ? 0 : y;
    x = (x < 0) ? 0 : x;
    
    y = (y >= MAP_HEIGHT) ? MAP_HEIGHT - 1 : y;
    x = (x >= MAP_WIDTH) ? MAP_WIDTH - 1 : x;
    
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

// Code from FreeCiv
SDL_Surface* CSurface::mask_surface(SDL_Surface* pSrc, SDL_Surface* pMask, int mask_offset_x, int mask_offset_y)
{
  SDL_Surface *pDest = NULL;

  int row, col;  
  bool free_pMask = false;
  Uint32 *pSrc_Pixel = NULL;
  Uint32 *pDest_Pixel = NULL;
  Uint32 *pMask_Pixel = NULL;
  unsigned char src_alpha, mask_alpha;

  if (!pMask->format->Amask) {
    pMask = SDL_DisplayFormatAlpha(pMask);
    free_pMask = true;
  }
  
  pSrc = SDL_DisplayFormatAlpha(pSrc);
  pDest = SDL_DisplayFormatAlpha(pSrc);
  
  SDL_LockSurface(pSrc);
  SDL_LockSurface(pMask);  
  SDL_LockSurface(pDest);
  
  pSrc_Pixel = (Uint32 *)pSrc->pixels;
  pDest_Pixel = (Uint32 *)pDest->pixels;

  for (row = 0; row < pSrc->h; row++) {
      
    pMask_Pixel = (Uint32 *)pMask->pixels
                  + pMask->w * (row + mask_offset_y)
                  + mask_offset_x;
    
    for (col = 0; col < pSrc->w; col++) {
      src_alpha = (*pSrc_Pixel & pSrc->format->Amask) >> pSrc->format->Ashift;
      mask_alpha = (*pMask_Pixel & pMask->format->Amask) >> pMask->format->Ashift;
      
      *pDest_Pixel = (*pSrc_Pixel & ~pSrc->format->Amask)
                   | (((src_alpha * mask_alpha) / 255) << pDest->format->Ashift);
      
      pSrc_Pixel++; pDest_Pixel++; pMask_Pixel++;
    }
  }

  SDL_UnlockSurface(pDest);
  SDL_UnlockSurface(pMask);    
  SDL_UnlockSurface(pSrc);
  
  if (free_pMask) {
    SDL_FreeSurface(pMask);
  }

  SDL_FreeSurface(pSrc); /* result of SDL_DisplayFormatAlpha() */
  
  return pDest;
}

SDL_Surface* CSurface::GetRectFromSurface(SDL_Surface* Src, SDL_Rect rect)
{
    SDL_Surface* dest = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w,rect.h,32, Src->format->Rmask, Src->format->Gmask, Src->format->Bmask, Src->format->Amask);
    
    SDL_Rect DestR;

    DestR.x = 0;
    DestR.y = 0;

    if (Src->format->Amask)
        pygame_AlphaBlit(Src, &rect, dest, &DestR);
    else
        SDL_BlitSurface(Src, &rect, dest, &DestR);
    
    return dest;
}