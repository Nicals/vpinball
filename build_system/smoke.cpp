#include <iostream>

#include <SDL3_image/SDL_image.h>
#include <FreeImage.h>
extern "C" {
#include <libavutil/avstring.h>
}
#include <altsound.h>
#include <libpinmame.h>
#include <DOF/DOF.h>

int main(int argc, char* argv[])
{
   IMG_Init(0x00);
   FreeImage_Initialise();
   av_strcasecmp("foo", "foo");
   AltsoundInit("foo", "bar");
   std::cout << "Pinmame: " << !PinmameIsRunning() << std::endl;

   DOF::DOF dof;

   return 0;
}
