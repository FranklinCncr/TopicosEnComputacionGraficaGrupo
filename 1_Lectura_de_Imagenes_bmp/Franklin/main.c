#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct bmpFileHeader
{
  uint32_t size;
  uint16_t resv1;
  uint16_t resv2;
  uint32_t offset;
} bmpFileHeader;

typedef struct bmpInfoHeader
{
  uint32_t headersize;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bpp;
  uint32_t compress;
  uint32_t imgsize;
  uint32_t bpmx;
  uint32_t bpmy;
  uint32_t colors;
  uint32_t imxtcolors;
} bmpInfoHeader;

void mostrar(bmpInfoHeader *info, unsigned char *img);
unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader);
int main()
{
  bmpInfoHeader info;
  unsigned char *img;
  img=LoadBMP("cubo.bmp", &info);
  mostrar(&info, img);
  return 0;
}

void mostrar(bmpInfoHeader *info, unsigned char *img)
{
  int x, y;
  int r,g,b;
  for (y=info->height; y>0; y=y-1){
      for (x=0; x<info->width; x=x+1)
    {
      b=(img[3*(x+y*info->width)]);
      g=(img[3*(x+y*info->width)+1]);
      r=(img[3*(x+y*info->width)+2]);

      if(r==255 && g==255 && b==255){
        printf(" ");
      }else{
        if(r>g && r>b){
            printf("r");
        }
        if(g>r && g>b){
            printf("g");
        }else{
            printf("b");
        }
      }
    }
      printf("\n");
    }
}
unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader){
  FILE *f;
  bmpFileHeader header;
  unsigned char *imgdata;
  uint16_t type;
  f=fopen (filename, "r");
  if (!f)
    return NULL;
  fread(&type, sizeof(uint16_t), 1, f);

  if (type !=0x4D42) {
      fclose(f);
      return NULL;
    }
  fread(&header, sizeof(bmpFileHeader), 1, f);
  fread(bInfoHeader, sizeof(bmpInfoHeader), 1, f);
  imgdata=(unsigned char*)malloc(bInfoHeader->imgsize);
  fseek(f, header.offset, SEEK_SET);
  fread(imgdata, bInfoHeader->imgsize,1, f);
  fclose(f);
  return imgdata;
}







