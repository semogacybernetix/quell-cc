
void vektor2eingabe1 (cvektor2& pp)
  {
  integer scanret;

  printf ("\n");
  printf ("a real:         ");
  scanret= scanf ("%Lf", &pp.x);
  printf ("a imaginär      ");
  scanret= scanf ("%Lf", &pp.y);
  printf ("\n");
  scanret++;        // scanret benutzen, damit der Compiler nicht meckert unused variable scanret
  }

void vektor2eingabe2 (cvektor2& pp, cvektor2& pq)
  {
  integer scanret;

  printf ("\n");
  printf ("p real:         ");
  scanret= scanf ("%Lf", &pp.x);
  printf ("p imaginär      ");
  scanret= scanf ("%Lf", &pp.y);
  printf ("\n");
  printf ("q real:         ");
  scanret= scanf ("%Lf", &pq.x);
  printf ("q imaginär      ");
  scanret= scanf ("%Lf", &pq.y);
  printf ("\n");
  scanret++;        // scanret benutzen, damit der Compiler nicht meckert unused variable scanret
  }

void vektor2eingabe3 (cvektor2& pr, cvektor2& ps, cvektor2& pt)
  {
  integer scanret;

  printf ("\n");
  printf ("r real:         ");
  scanret= scanf ("%Lf", &pr.x);
  printf ("r imaginär      ");
  scanret= scanf ("%Lf", &pr.y);
  printf ("s real:         ");
  scanret= scanf ("%Lf", &ps.x);
  printf ("s imaginär      ");
  scanret= scanf ("%Lf", &ps.y);
  printf ("t real:         ");
  scanret= scanf ("%Lf", &pt.x);
  printf ("t imaginär      ");
  scanret= scanf ("%Lf", &pt.y);
  printf ("\n");
  scanret++;        // scanret benutzen, damit der Compiler nicht meckert unused variable scanret
  }

