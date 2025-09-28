
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <linux/soundcard.h>

int main()
  {
  int fd = open("/dev/dsp", O_WRONLY);
  if (fd == -1)
    {
    perror("Fehler beim Öffnen von /dev/dsp");
    return 1;
    }

    // Setze Abtastrate und Format (optional)
    int fmt= 16; // 16-Bit
    int samplerate= 44100;
    int amplitude= 16000;

    ioctl(fd, SOUND_PCM_WRITE_BITS, &fmt);
    ioctl(fd, SOUND_PCM_WRITE_RATE, &samplerate);

    short  sample;
    double t= 0.0;
    ssize_t ret= 0;

    for (int i= 0; i < samplerate*5; i++)
      { // 5 Sekunden
      sample = (short)(amplitude * sin(2.0 * M_PI * 440.0 * t)); // 440 Hz Sinuswelle
      ret= write(fd, &sample, sizeof(sample));
      printf ("Bytes geschrieben: %5ld\n", ret);
      t+= 1.0/samplerate;
      }

    close(fd);
    return 0;
}
