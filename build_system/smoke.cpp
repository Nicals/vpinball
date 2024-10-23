#include <SDL3_image/SDL_image.h>
#include <FreeImage.h>
extern "C" {
#include <libavutil/avstring.h>
}
#include <altsound.h>

int main(int argc, char* argv[])
{
   IMG_Init(0x00);
   FreeImage_Initialise();
   av_strcasecmp("foo", "foo");
   AltsoundInit("foo", "bar");

   return 0;
}
