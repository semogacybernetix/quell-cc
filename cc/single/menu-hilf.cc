integer entscheidungseingabe ()
  {
  integer ent;
  printf ("\n");
  printf (" [1] Drehungen      [2] Drehmultiplikation  [3] Division                [4] Testespiegelung  [5] Testematrix     [6] 2 Drehspiegelungen      [66] EFK objDatei            [7] 3 Drehspiegelungen\n");
  printf (" [8] Dreh -> Spieg  [9] Spieg -> Dreh      [10] 3 Spiegelebenenwinkel  [11] 3 gleiche Spiegelebenenwinkel\n");
  printf ("[12]  2 Drehungen + Koordinatendrehung     [13] Ebenenwinkel -> Spiegelachsenwinkel   [14] 3 Drehebenenwinkel   [15] 3 Ebenespieg -> Dreh    [16] Testespiegelebenen     [17] Testeqv      ");
  printf ("[20] Generiere Polyeder    ");
  scanret= scanf ("%lld", &ent);
  return ent;
  }

/*

float         8 Stellen
double       16 Stellen
long double  20 Stellen
__float128   35 Stellen

*/


//--------------------- Hauptprogramm ----------------------------------------------

int main ()
  {
  integer ent (entscheidungseingabe ());
  switch (ent)
    {
    case 1:
      dreh1 ();
      //testedrehungen ();
      break;
    case 2:
      drehmul ();
      break;
    case 3:
      testedivision ();
      break;
    case 4:
      testespiegelung ();
      break;
    case 5:
      testematrix ();
      break;
    case 6:
      dreh2 ();
      break;
    case 66:
      dreh2efk ();
      break;
    case 20:
      generierepolyederobj ();
      break;
    case 7:
      dreh3 ();
      break;
    case 8:
      testekonvertierung23 ();
      break;
    case 9:
      testekonvertierung32 ();
      break;
    case 10:
      ebenenwinkel3 ();          // 3 Spiegelungen
      break;
    case 11:
      testestern ();
      break;
    case 12:
      dreh2k ();
      break;
    case 13:
      testespiegelebenen ();
      break;
    case 14:
      ebenenwinkel180 ();  // 3 180° Drehungen direkt
      break;
    case 15:
      ebenenachdreh ();
      break;
    case 16:
      testespiegelebenen2 ();
      break;
    case 17:
      testevektordreh ();
      break;
    }
  printtext ("");
  return 0;
  }

