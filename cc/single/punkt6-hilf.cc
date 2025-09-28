
//-------------------------------------- 2 Drehspiegelungen ------------------------------------------------

void dreh2 ()
  {
  cvektor4 el1, el2;
  cvektor4liste qliste (lmax);
  cbasis3liste bliste (lmax);
  ccluster cluster (1000);
  cvektor3liste vliste (lmax);

  el1= winkelachseeingaberoh ();
  el2= winkelachseeingaberoh ();
  
  // negative Winkel bedeuten positiver Winkel + Inversion (Drehspiegelung)
  
  printtextobj ("# --------------------------------------------------------------------------------------------------------------\n");
  printtextobj ("# Körper\n\n");
  printtextobj ("# Drehung1: ");
  printvektor3perf (cvektor3 (el1.i, el1.j, el1.ij), 1);
  printtextobj (" ");
  printzahlobj (el1.r, 1);
  printtextobj ("°\n");
  printtextobj ("# Drehung2: ");
  printvektor3perf (cvektor3 (el2.i, el2.j, el2.ij), 1);
  printtextobj (" ");
  printzahlobj (el2.r, 1);
  printtextobj ("°\n");
  printtextobj ("\n");
  el1.r= el1.r/180*M_PIl;
  el2.r= el2.r/180*M_PIl;

  if (el1.r < 0)
    {
    el1.r= -el1.r;
    qliste.winkelachsehinzu (-el1);
    bliste.winkelachseihinzu (el1);
    }
    else
    {
    qliste.winkelachsehinzu (el1);
    bliste.winkelachsehinzu (el1);
    }
  if (el2.r < 0)
    {
    el2.r= -el2.r;
    qliste.winkelachsehinzu (-el2);
    bliste.winkelachseihinzu (el2);
    }
    else
    {
    qliste.winkelachsehinzu (el2);
    bliste.winkelachsehinzu (el2);
    }

  qliste.schliesseab ();
  bliste.schliesseab ();
  
  if (!qliste.uebergelaufen)
    {
    qliste.ermittleordnung ();
    qliste.sortierenachordnung ();
    qliste.ermittlepaarung ();
    }
  if (!bliste.uebergelaufen)
    {
    bliste.ermittleordnung ();
    bliste.sortierenachordnung ();
//    bliste.ermittlepaarung ();
    }

  printtext ("-- Anfang -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  printv4liste (qliste);
  getchar ();
  printb3liste (bliste);
  getchar ();
  cluster.gruppe->kopiere (bliste);
  cluster.vervollstaendige ();

  printtext ("Gruppe:\n");
  printb3liste (*cluster.gruppe);
  getchar ();
  printtext ("Kern:\n");
  printb3liste (*cluster.kern);
  getchar ();
  printtext ("maxord Gruppe:   ");
  printinteger (cluster.gruppe->maxord);
  printtext ("maxord Kern:   ");
  printinteger (cluster.kern->maxord);
  printtext ("\nPartliste:\n");
  printv3liste (*cluster.partliste);
  printtext ("maximale Zähligkeit:   ");
  printreal (cluster.gruppe->maxord);
  printtext ("\n\n");

  printtext ("Kanten:\n");
  printv3liste (*cluster.kliste);
  printtext ("Ecken:\n");
  printv3liste (*cluster.eliste);
  printtext ("Flächen:\n");
  printv3liste (*cluster.fliste);

  printtext ("Spiegelungen:\n");
  printb3liste (*cluster.spieg);

  printtextobj ("# Gruppenordnung: ");
  printrealobj (bliste.anz);
  printtextobj ("\n");
  printtextobj ("# Drehungen: ");
  printrealobj (cluster.kern->anz);
  printtextobj ("\n");

  if (bliste.anz != cluster.kern->anz)
    {
    printtextobj ("# kleinster Drehinversionswinkel: ");
    printzahlobj (cluster.gruppe->miniwinkel/M_PIl*180,2);
    printtextobj ("°\n");
    printtextobj ("# Spiegelebenen: ");
    printrealobj (cluster.spieg->anz);
    printtextobj ("\n");
    }

  printtextobj ("\n");
  printtext ("Vektoreingabe:\n");
  cvektor3 vein;
  vektor3eingabe (vein);
  printtextobj ("# Körpervektor: ");
  printvektor3perf (vein, 10);
  printtextobj ("\n");
  cvektor3 nvein= normiere (vein);
  printtextobj ("# Körpervektor normiert: ");
  printvektor3perf (nvein, 10);
  printtextobj ("\n");
  printtextobj ("\n");
  cvektor3 efk= cluster.ermittleefkdreibein (nvein);
  cvektor3 vecke= cluster.fliste->v[(unsigned long long) (efk.x)];
  cvektor3 vflaeche= cluster.eliste->v[(unsigned long long) (efk.y)];
  cvektor3 vkante= cluster.kliste->v[(unsigned long long) (efk.z)];
  printtextobj ("# Eckenvektor:   ");
  printvektor3perf (vecke, 10);
  printtextobj ("\n");
  printtextobj ("# Flächenvektor: ");
  printvektor3perf (vflaeche, 10);
  printtextobj ("\n");
  printtextobj ("# Kantenvektor:  ");
  printvektor3perf (vkante, 10);
  printtextobj ("\n");
  cbasis3 divbasis= cbasis3 (vecke, vflaeche, vkante);
  printtextobj ("# Volumen EFK Dreibein:  ");
  printzahlobj (det (divbasis), 10);
  printtextobj ("\n\n");
  cvektor3 vlin= nvein/divbasis;
  cvektor3 rvlin= vlin.x*vecke + vlin.y * vflaeche + vlin.z * vkante;
  printtextobj ("# Faktoren Linearkombination (EFK):         ");
  printvektor3perf (vlin, 10);
  printtextobj ("\n");
  printtextobj ("# Körpervektor aus Linearkombination:       ");
  printvektor3perf (rvlin, 10);
  printtextobj ("\n");
  cvektor3 vlindif= rvlin - nvein;
  printtextobj ("# Differenz Körpervektor Linearkombination: ");
  printvektor3perf (vlindif, 10);
  printtextobj ("\n");

  printtextobj ("\n");
  // Vektor mit Gruppe zum Körper aufspannen
  vliste.elementhinzu (nvein, 1);
  vliste.schliesseab (bliste);
  printtextobj ("# Punkte: ");
  printrealobj (vliste.anz);
  printtextobj ("\n");
  printtextobj ("\n");
  printv3liste (vliste);
  printv3listeobj (vliste);
  printtext ("-- Ende -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  }

