// --------------------------------------------  quadratischnormal --------------------------------------------------------------------------------

void quadratisch1 (ckomplexk a, ckomplexk b, ckomplexk& x1, ckomplexk& x2)
  {
  ckomplexk a2, D;

  a2= -a/2;
  D= sqrtv (a2*a2 - b);

  x1= a2 + D;
  x2= a2 - D;
  }

// --------------------------------------------  quadratische Resolventen --------------------------------------------------------------------------------

void quadratischeresolvente1 (ckomplexk p, ckomplexk q, ckomplexk& z1, ckomplexk& z2)
  {
  ckomplexk ad, bd;

  ad= q;
  bd= -(p*p*p)/27;

  quadratisch (ad, bd, z1, z2);
  }

void quadratischeresolvente3 (ckomplexk p, ckomplexk q, ckomplexk& z1, ckomplexk& z2)
  {
  ckomplexk ad, bd;

  ad= q*27;
  bd= -(p*p*p)*27;

  quadratisch (ad, bd, z1, z2);
  }

// --------------------------------------------  kubischreduziert --------------------------------------------------------------------------------

void uvaddition (ckomplexk z1, ckomplexk z2, ckomplexk bed, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk u1, u2, u3, v[3];
  integer   vindex[3];

  // die 3 Lösungen für u, v
  cbrtv (z1, u1, u2, u3);
  cbrtv (z2, v[0], v[2], v[1]);

  // Standardzuordnung der u's und v's (keine Verschiebung)
  vindex[0]= 0;
  vindex[1]= 1;
  vindex[2]= 2;

  // Die Bedingung u*v = bed muss erfüllt sein
  // Die v-Sequenz einen Schritt rückwärts rotieren falls das u[0], v[1] Paar richtig ist
  if ((absv (u1*v[1] - bed) < absv (u1*v[0] - bed)) && (absv (u1*v[1] -bed) < absv (u1*v[2] - bed)))
    {
    vindex[0]= 1;
    vindex[1]= 2;
    vindex[2]= 0;
    }

  // Die v-Sequenz um einen Schritt vorwärts rotieren falls das u[0], v[2] Paar richtig ist
  if ((absv (u1*v[2] - bed) < absv (u1*v[0] - bed)) && (absv (u1*v[2] - bed) < absv (u1*v[1] - bed)))
    {
    vindex[0]= 2;
    vindex[1]= 0;
    vindex[2]= 1;
    }

  // Bestimmung der Summen durch Addition der korrekt zueinander verschobenen u- und v-Sequenzen
  y1= (u1 + v[vindex[0]]);
  y2= (u2 + v[vindex[1]]);
  y3= (u3 + v[vindex[2]]);
  }

void kubischreduziertcardano (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk  bed, z1, z2;

  quadratischeresolvente1 (p, q, z1, z2);

  bed= -p;
  uvaddition (z1, z2, bed, y1, y2, y3);
  }

void kubischreduziertcardano3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk  bed, z1, z2;

  quadratischeresolvente3 (p, q, z1, z2);

  bed= -p*3;
  uvaddition (z1, z2, bed, y1, y2, y3);
  }

void kubischreduziertvtransr1 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk  u1, u2, u, z1, z2, z3;

  quadratischeresolvente1 (p, q, u1, u2);

  u= u1;
  if (absv (u2) > absv (u))                   // die betragsmäßig größere Lösung nehmen um von der Division durch 0 wegzukommen
    u= u2;

  cbrtv (u, z1, z2, z3);

  y1= z1 - p/(z1*3);
  y2= z2 - p/(z2*3);
  y3= z3 - p/(z3*3);
  }

void kubischreduziertvtransr3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk  D, u1, u2, u, z1, z2, z3;

  quadratischeresolvente3 (p, q, u1, u2);

  u= u1;
  if (absv (u2) > absv (u))                 // die betragsmäßig größere Lösung nehmen um von der Division durch 0 wegzukommen
    u= u2;

  cbrtv (u, z1, z2, z3);

  y1= z1/3 - p/z1;
  y2= z2/3 - p/z2;
  y3= z3/3 - p/z3;
  }

void kubischreduziertfaktor3 (ckomplexk p, ckomplexk q, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3)
  {
  ckomplexk  ad, bd, bed, z1, z2;

  ad= q*27;

  bed= -p*3;
  bd= bed*bed*bed;

  quadratisch (ad, bd, z1, z2);
  uvaddition (z1, z2, bed, y1, y2, y3);
  }

void kubischreduziertk (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& p, ckomplexk& q)
  {
  p= -(a*a)/3 + b;
  q= a*(a*a/real (4.5) - b)/3 + c;
  }

void kubisch (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3)
  {
  ckomplexk p, q, y1, y2, y3;

  kubischreduziertk (a, b, c, p, q);

//  kubischreduziertcardano3 (p, q, y1, y2, y3);
  kubischreduziertfaktor3 (p, q, y1, y2, y3);

  x1= (y1 - a)/3;
  x2= (y2 - a)/3;
  x3= (y3 - a)/3;
  }

// --------------------------------------------  kubische Resolventen --------------------------------------------------------------------------------

void kubischeresolventediffp (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk ak, bk, ck;

  ak= -p;
  bk= r*-4;
  ck= r*p*4 - q*q;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventebuch (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk ak, bk, ck;

  ak= p/-2;
  bk= -r;
  ck= r*p/2 - q*q/8;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventepdfw2 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk ak, bk, ck;

  ak= p*2;
  bk= p*p - r*4;
  ck= q*q*-1;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolventelagrange (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk ak, bk, ck;

  ak= p/2;
  bk= p*p/16 - r/4;
  ck= q*q/-64;

  kubisch (ak, bk, ck, z1, z2, z3);
  }

void kubischeresolvente1z (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk pk, qk;

  pk= (p*p + r*12)/-3;
  qk= p*(r*36 - p*p)/real (13.5) - q*q;

  kubischreduziertcardano (pk, qk, z1, z2, z3);
  }

void kubischeresolvente3z (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& z1, ckomplexk& z2, ckomplexk& z3)
  {
  ckomplexk pk, qk;

  pk= (p*p + r*12)/-3;
  qk= p*(r*36 - p*p)/real (13.5) - q*q;

  kubischreduziertcardano3 (pk, qk, z1, z2, z3);
  }

// --------------------------------------------  quartischreduziert --------------------------------------------------------------------------------

void quartischreduziertdiffpu (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolventediffp (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv (z - p);

  a1=  u;
  a2= -u;
  b1= (z - q/u)/2;
  b2= (z + q/u)/2;

  quadratisch1 (a1, b1, y1, y2);
  quadratisch1 (a2, b2, y3, y4);
  }

void quartischreduziertbuchu (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolventebuch (p, q, r, z1, z2, z3);

  z= z3;
  u= sqrtv (z*2 - p);

  a1=  u;
  a2= -u;
  b1= z - q/u/2;
  b2= z + q/u/2;

  quadratisch1 (a1, b1, y1, y2);
  quadratisch1 (a2, b2, y3, y4);
  }

void quartischreduziertbuchv (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolventebuch (p, q, r, z1, z2, z3);

  z= z2;
  v= sqrtv (z*z - r);

  a1= -q/v/2;
  a2=  q/v/2;
  b1= z + v;
  b2= z - v;

  quadratisch1 (a1, b1, y1, y2);
  quadratisch1 (a2, b2, y3, y4);
  }

void quartischreduziertbuchf (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolventebuch (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv (z*2 - p);

  a1=  u;
  a2= -u;

  v= sqrtv (z*z - r);

  // Bedingung -2uv = q
  bed= u*v*-2;
  if (absv (bed + q) < absv (bed - q))
    v= -v;

  b1= z + v;
  b2= z - v;

  quadratisch1 (a1, b1, y1, y2);
  quadratisch1 (a2, b2, y3, y4);
  }

void quartischreduziertpdfw2 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, a1, a2, b1, b2;

  kubischeresolventepdfw2 (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv (z);

  a1=  u;
  a2= -u;
  b1= (z + p - q/u)/2;
  b2= (z + p + q/u)/2;

  quadratisch1 (a1, b1, y1, y2);
  quadratisch1 (a2, b2, y3, y4);
  }

void quartischreduziertlagrange (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, u1, u2, u3, bed;

  kubischeresolventelagrange (p, q, r, z1, z2, z3);

  u1= sqrtv (z1);
  u2= sqrtv (z2);
  u3= sqrtv (z3);

  y1=  u1 + u2 + u3;
  y2=  u1 - u2 - u3;
  y3= -u1 + u2 - u3;
  y4= -u1 - u2 + u3;

  // Bedingung: -8*u1*u2*u3 = q
  bed= u1*u2*u3*-8;
  if (absv (bed + q) < absv (bed - q))
    {
    y1= -y1;
    y2= -y2;
    y3= -y3;
    y4= -y4;
    }
  }

void quartischreduziertbuch3 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, v, bed, a1, a2, b1, b2;

  kubischeresolvente3z (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv ((z - p*2)/3);

  a1=  u;
  a2= -u;

  v= z + p;
  v= sqrtv (v*v - r*36)/6;

  // Bedingung -2uv = q
  bed= u*v*-2;
  if (absv (bed + q) < absv (bed - q))
    v= -v;

  b1= (z + p)/6 + v;
  b2= (z + p)/6 - v;

  quadratisch1 (a1, b1, y1, y2);
  quadratisch1 (a2, b2, y3, y4);
  }

void quartischreduziertpdfw23 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, z, u, a1, a2, b1, b2;

  kubischeresolvente3z (p, q, r, z1, z2, z3);

  z= z1;
  u= sqrtv ((z - p*2)/3);

  a1=  u;
  a2= -u;
  b1= (z + p)/6 - q/u/2;
  b2= (z + p)/6 + q/u/2;

  quadratisch1 (a1, b1, y1, y2);
  quadratisch1 (a2, b2, y3, y4);
  }

void quartischreduziertlagrange3 (ckomplexk p, ckomplexk q, ckomplexk r, ckomplexk& y1, ckomplexk& y2, ckomplexk& y3, ckomplexk& y4)
  {
  ckomplexk z1, z2, z3, u1, u2, u3, bed;

  kubischeresolvente3z (p, q, r, z1, z2, z3);

  u1= sqrtv ((z1/2 - p)/6);
  u2= sqrtv ((z2/2 - p)/6);
  u3= sqrtv ((z3/2 - p)/6);

  y1=  u1 + u2 + u3;
  y2=  u1 - u2 - u3;
  y3= -u1 + u2 - u3;
  y4= -u1 - u2 + u3;

  // Bedingung: -8*u1*u2*u3 = q
  bed= u1*u2*u3*-8;
  if (absv (bed + q) < absv (bed - q))
    {
    y1= -y1;
    y2= -y2;
    y3= -y3;
    y4= -y4;
    }
  }

void quartischreduziertk (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& p, ckomplexk& q, ckomplexk& r)
  {
  p= a*a*3/-8 + b;
  q= a*(a*a - b*4)/8 + c;
  r= a*((a*b - c*4)*16 - a*a*a*3)/256 + d;
  }

void quartisch (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk d, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  ckomplexk p, q, r, y1, y2, y3, y4, a4;

  quartischreduziertk (a, b, c, d, p, q, r);
  quartischreduziertpdfw2 (p, q, r, y1, y2, y3, y4);

  a4= a/4;
  x1= y1 - a4;
  x2= y2 - a4;
  x3= y3 - a4;
  x4= y4 - a4;
  }
