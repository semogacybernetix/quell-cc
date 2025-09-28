#include <cstdio>

void berechnemline (unsigned long px, unsigned long py, float pf, bool fv)
  {
  float tb, ty, tx, cl;
  unsigned long xs, xe, xt, ys, ye, yt;
  unsigned long pe, xl, xm, xr, yl, ym, yr;
  if (fv)
    {
    tb= 1/pf;
    ty= (tb - 400e-6)/py;
    }
    else
    {
    ty= 1/pf;
    tb= ty*py + 400e-6;
    }
  tx= (ty - 4e-6)/px;
  cl= int (1/(tx*1e4) + 0.5)/100.;
  pe= int (1e6/cl + 0.5);
  xt= int (ty*cl*1e6 + 0.5);
  yt= int (tb*cl*1e6/xt + 0.5);
  xm= int (cl + 0.5);
  ym= int (100*cl/xt + 0.5);
  xs= px;
  ys= py;
  xe= px + xm;
  ye= py + ym;
  xr= 0;
  yr= 0;
  xl= xt - xe;
  yl= yt - ye;
  unsigned long fa;
  float frh= cl*1e6/(xt*1e3);
  float frv= cl*1e6/(xt*yt);
  fa= int (frv + 0.5);
  printf("\n");
  printf ("# D: %3.2f MHz  H: %3.2f kHz  V: %3.2f Hz\n", cl, frh, frv);
  printf ("Modeline \"%lux%lux%lu\" %4.2f %lu %lu %lu %lu %lu %lu %lu %lu -hsync -vsync\n",
           px, py, fa, cl, px, xs, xe, xt, py, ys, ye, yt);
  printf("\n");
  printf ("mode \"%lux%lux%lu\"\n", px, py, fa);
  printf ("    # D: %3.2f MHz  H: %3.2f kHz  V: %3.2f Hz\n", cl, frh, frv);
  printf ("    geometry %lu %lu %lu %lu 32\n", px, py, px, py);
  printf ("    timings %lu %lu %lu %lu %lu %lu %lu\n", pe, xl, xr, yl, yr, xm, ym);
  printf ("endmode\n");
  printf("\n");
  }

int main (int argc, char** argv)
  {
  if ((argc != 4) && (argc != 5))
    {
    printf ("    example:\n");
    printf ("    modeline 1024 768 85.4\n");
    printf ("    or:\n");
    printf ("    modeline 1024 768 63.9 h\n");
    return 0;
    }
  unsigned long screenx, screeny;
  float pf;
  sscanf (argv[1], "%lu", &screenx);
  sscanf (argv[2], "%lu", &screeny);
  sscanf (argv[3], "%f", &pf);
  if (argc == 4)
    berechnemline (screenx, screeny, pf, 1);
    else
    berechnemline (screenx, screeny, pf*1e3, 0);
  return 0;
  }
