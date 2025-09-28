#include "../class/cschachio.h"

void spielepartie ()
  {
  cpartie* partie= new cpartie;
  cschachio* partieio= new cschachio ("brainchess.log");
  partieio->bindeanpartie (*partie);
  while (true)
    {
    cstellung* tempstellung= partie->stellung[partie->anzahlstellungen - 1];
    tempstellung->stellungszaehler= 0;
//    tempstellung->ermittleknotenwerts (1000, tempstellung->stellungszaehler);
    tempstellung->traversierestellung (0, tempstellung->stellungszaehler);
//    tempstellung->ermittleschlagbestwert (tempstellung->stellungszaehler);
//    tempstellung->ermittleknotenwertgemischt (2, tempstellung->stellungszaehler);
    partieio->stellungaufschirm ();
    partieio->zugeingabe ();
    }
  delete partieio;
  delete partie;
  }
  
int main ()
  {
  spielepartie ();
  return 0;
  }
