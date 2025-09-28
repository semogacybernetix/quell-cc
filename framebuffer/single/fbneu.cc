#include <sys/mman.h>    // mmap, munmap
#include <sys/ioctl.h>   // ioctl
#include <fcntl.h>       // open
#include <linux/fb.h>    // screeninfo
#include <unistd.h>      // close
#include <cstdio>        // printf
#include <cstring>       // memset
#include <cstdint>       // uint32_t

int main ()
  {
  uint32_t xanz, yanz, pixanz, bitspp, bytespp;

  // Öffnen des Gerätes
  int fd = open ("/dev/fb0", O_RDWR);

  // Informationen über den Framebuffer einholen
  struct fb_var_screeninfo screeninfo;
  ioctl (fd, FBIOGET_VSCREENINFO, &screeninfo);

  // Farbtiefe berechnen
  bitspp = screeninfo.bits_per_pixel;
  xanz= screeninfo.xres;
  yanz= screeninfo.yres;
  pixanz= xanz*yanz;

  bytespp= bitspp/8;
  printf ("Farbtiefe = %u Bits pro Pixel\n", bitspp);

  if (bitspp == 16)
    {
    // Zeiger auf den Framebufferspeicher anfordern
    uint16_t* data;
    data= (uint16_t*) mmap (0, pixanz*bytespp, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // In den Framebuffer-Speicher schreiben. Hier wird Pixel für Pixel auf
    // die Farbe 0x000000FF (Blau) gesetzt, da ein Pixel das AARRGGBB Format hat
    for (unsigned long laufp = 0; laufp < pixanz; laufp++)
      data[laufp]= 0x1f;      // 5r6g5b

    // Zeiger wieder freigeben
    munmap (data, pixanz*bytespp);
    }

  if (bitspp == 32)
    {
    // Zeiger auf den Framebufferspeicher anfordern
    uint32_t* data;
    data= (uint32_t*) mmap (0, pixanz*bytespp, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // In den Framebuffer-Speicher schreiben. Hier wird Pixel für Pixel auf
    // die Farbe 0x000000FF (Blau) gesetzt, da ein Pixel das AARRGGBB Format hat

//    memset (data, 0xff, pixanz*bytespp);

    for (unsigned long laufp = 0; laufp < pixanz; laufp++)
      data[laufp]= 0xff;

    // Zeiger wieder freigeben
    munmap (data, pixanz*bytespp);
    }

  // Gerät schließen
  close (fd);

  return 0;
  }
