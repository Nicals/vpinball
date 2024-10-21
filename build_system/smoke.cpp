#include <SDL3_image/SDL_image.h>
#include <FreeImage.h>

int main(int argc, char* argv[])
{
   IMG_Init(0x00);
   FreeImage_Initialise();

   return 0;
}
