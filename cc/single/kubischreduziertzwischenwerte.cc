
void kubischreduziertzwischenwerte (ckomplexk x1, ckomplexk x2, ckomplexk& x3) //***********************************************************************
  {
  ckomplexk  x3, p, q, d, d_17p, d_21p, uh3_l, vh3_l, d_ql, dq, bed;
  ckomplexk  u31x, u32x, u33x, v31x, v32x, v33x, uh3x, vh3x;
  ckomplexk  D21_lm, D21_pm, uh3_21pm, vh3_21pm, L1_21pm, L2_21pm, L3_21pm;
  ckomplexk  D21_l, D21_p, uh3_21p, vh3_21p, L1_21p, L2_21p, L3_21p;
  ckomplexk  D17_l, D17_p, uh3_17p, vh3_17p, L1_17p, L2_17p, L3_17p;
  ckomplexk  D1_lm, D1_pm, uh3_1pm, vh3_1pm, L1_1pm, L2_1pm, L3_1pm;
  ckomplexk  D1_l, D1_p, uh3_1p, vh3_1p, L1_1p, L2_1p, L3_1p;
  ckomplexk  D3_lm, D3_pm, uh3_3pm, vh3_3pm, L1_3pm, L2_3pm, L3_3pm;

  // Ermittlung x3 für reduzierte Gleichung
  x3= -(x1 + x2);

  // Koeffizienten aus den Lösungen
  p= x1*x2 + x2*x3 + x3*x1;
  q= -x1*x2*x3;

  d= (x1-x2)*(x2-x3)*(x3-x1);
  uh3_l= sqrtl (27)*ik*x1*x2*x3 + x1*x2*x2 + x2*x3*x3 + x3*x1*x1 - x1*x1*x2 - x2*x2*x3 - x3*x3*x1;
  vh3_l= sqrtl (27)*ik*x1*x2*x3 - x1*x2*x2 - x2*x3*x3 - x3*x1*x1 + x1*x1*x2 + x2*x2*x3 + x3*x3*x1;
  d_ql= uh3_l - vh3_l;
  dq= d*d;

  // Lösungen Faktor 2.18  D = -d²
  D21_lm= -dq;
  D21_pm= q*q*27 + p*p*p*4;
  uh3_21pm= -q*sqrtl (27) + sqrtv (D21_lm);
  vh3_21pm= -q*sqrtl (27) - sqrtv (D21_lm);
  bed= p*-cbrtl (4);
  uvaddition (uh3_21pm, vh3_21pm, bed, L1_21pm, L2_21pm, L3_21pm);
  L1_21pm= L1_21pm/cbrtl (sqrtl (108));  // = sqrtl (3)*cbrtl (2)
  L2_21pm= L2_21pm/cbrtl (sqrtl (108));
  L3_21pm= L3_21pm/cbrtl (sqrtl (108));

  // Lösungen Faktor 2.18i D = d²
  D21_l= dq;
  D21_p= q*q*-27 - p*p*p*4;
  uh3_21p= -q*sqrtl (27)*ik - sqrtv (D21_l);
  vh3_21p= -q*sqrtl (27)*ik + sqrtv (D21_l);
  d_21p= uh3_21p - vh3_21p;
  bed= -p*cbrtv (-4*einsk);
  uvaddition (uh3_21p, vh3_21p, bed, L1_21p, L2_21p, L3_21p);
  L1_21p= L1_21p/cbrtv (ik*sqrtl (108));
  L2_21p= L2_21p/cbrtv (ik*sqrtl (108));
  L3_21p= L3_21p/cbrtv (ik*sqrtl (108));

  // Lösungen Faktor 1.73i  D = d²/4
  D17_l= dq/4;
  D17_p= q*q*-27/vier - p*p*p;
  uh3_17p= -q/2*sqrtv (-27*einsk) + sqrtv (D17_l);
  vh3_17p= -q/2*sqrtv (-27*einsk) - sqrtv (D17_l);
  d_17p= uh3_17p - vh3_17p;
  bed= -p*cbrtv (-einsk);
  uvaddition (uh3_17p, vh3_17p, bed, L1_17p, L2_17p, L3_17p);
  L1_17p= L1_17p/cbrtv (ik*sqrtl (27));
  L2_17p= L2_17p/cbrtv (ik*sqrtl (27));
  L3_17p= L3_17p/cbrtv (ik*sqrtl (27));

  // Lösungen Faktor 1      D=d²/-108
  D1_lm= dq/-108;
  D1_pm= q*q/4 + p*p*p/27;
  uh3_1pm= -q/2 + sqrtv (D1_lm);
  vh3_1pm= -q/2 - sqrtv (D1_lm);
  bed= -p/3;
  uvaddition (uh3_1pm, vh3_1pm, bed, L1_1pm, L2_1pm, L3_1pm);

  // Lösungen Faktor i     D= d²/108
  D1_l= dq/108;
  D1_p= q*q/-4 - p*p*p/27;
  uh3_1p= -q/2*ik + sqrtv (D1_l);
  vh3_1p= -q/2*ik - sqrtv (D1_l);
  bed= p/3;
  uvaddition (uh3_1p, vh3_1p, bed, L1_1p, L2_1p, L3_1p);
  L1_1p= L1_1p*ik;
  L2_1p= L2_1p*ik;
  L3_1p= L3_1p*ik;

  // Lösungen Faktor 3    D= -6.75 d²
  D3_lm= dq*-6.75;
  D3_pm= q*q*182.25 + p*p*p*27;
  uh3_3pm= -13.5*q + sqrtv (D3_lm);
  vh3_3pm= -13.5*q - sqrtv (D3_lm);
  bed= -3*p;
  uvaddition (uh3_3pm, vh3_3pm, bed, L1_3pm, L2_3pm, L3_3pm);
  L1_3pm= L1_3pm/3;
  L2_3pm= L2_3pm/3;
  L3_3pm= L3_3pm/3;

  // die 3 Lösungen für u aus den Lösungen 27u³
  u31x= (x1     + e32*x2 + e31*x3);
  u32x= (e31*x1 +     x2 + e32*x3);
  u33x= (e32*x1 + e31*x2 +     x3);
  uh3x= u31x*u31x*u31x;

  // die 3 Lösungen für v aus den Lösungen 27v³
  v31x= (x1     + e31*x2 + e32*x3);
  v32x= (e32*x1 +     x2 + e31*x3);
  v33x= (e31*x1 + e32*x2 +     x3);
  vh3x= v31x*v31x*v31x;

  printf ("-------------------------------- das Differenzenprodukt d -----------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("p          ", p, 0);
  printvektor2komplex ("q          ", q, 0);
  printf ("\n");
  printvektor2komplex ("d          ", d, 1);
  printvektor2komplex ("d_ql       ", d_ql, 1);
  printvektor2komplex ("d_17p      ", d_17p, 1);
  printvektor2komplex ("d_21p      ", d_21p, 1);
  printf ("\n");
  printf ("-------------------------------- die Werte u³, v³ aus den Lösungen ---------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("3u³p       ", uh3_l, 1);
  printvektor2komplex ("3v³p       ", vh3_l, 1);
  printf ("\n");
  printf ("-------------------------------- u³, v³  mit Faktor 27 ---------------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("uh3x       ", uh3x, 1);
  printvektor2komplex ("vh3x       ", vh3x, 1);
  printf ("\n");
  printf ("-------------------------------- die Werte u³, v³ mit Faktor -2.18 -d  ---------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("3u³p       ", uh3_21pm, 1);
  printvektor2komplex ("3v³p       ", vh3_21pm, 1);
  printf ("\n");
  printf ("-------------------------------- die Werte u³, v³ mit Faktor  2.18---------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("3u³p       ", uh3_21p, 1);
  printvektor2komplex ("3v³p       ", vh3_21p, 1);
  printf ("\n");
  printf ("-------------------------------- die Werte u³, v³ mit Faktor  1.73 ---------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("3u³p       ", uh3_17p, 1);
  printvektor2komplex ("3v³p       ", vh3_17p, 1);
  printf ("\n");
  printf ("-------------------------------- die Werte u³, v³ mit Faktor -1 ------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("u³p        ", uh3_1pm, 1);
  printvektor2komplex ("v³p        ", vh3_1pm, 1);
  printf ("\n");
  printf ("-------------------------------- die Werte u³, v³ mit Faktor  1 ------------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("u³p        ", uh3_1p, 1);
  printvektor2komplex ("v³p        ", vh3_1p, 1);
  printf ("\n");
  printf ("-------------------------------- die Lösungen aus Faktor -2.18 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_21pm, 1);
  printvektor2komplex ("x0p D0     ", L2_21pm, 1);
  printvektor2komplex ("x0p D0     ", L3_21pm, 1);
  printf ("\n");
  printf ("-------------------------------- die Lösungen aus Faktor 2.18 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_21p, 1);
  printvektor2komplex ("x0p D0     ", L2_21p, 1);
  printvektor2komplex ("x0p D0     ", L3_21p, 1);
  printf ("\n");
  printf ("-------------------------------- die Lösungen aus Faktor 1.73 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_17p, 1);
  printvektor2komplex ("x0p D0     ", L2_17p, 1);
  printvektor2komplex ("x0p D0     ", L3_17p, 1);
  printf ("\n");
  printf ("-------------------------------- die Lösungen aus Faktor -1 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_1pm, 1);
  printvektor2komplex ("x0p D0     ", L2_1pm, 1);
  printvektor2komplex ("x0p D0     ", L3_1pm, 1);
  printf ("\n");
  printf ("-------------------------------- die Lösungen aus Faktor  1 ----------------------------------------------------------------------------------------------------------------------------\n");
  printvektor2komplex ("x0p D0     ", L1_1p, 1);
  printvektor2komplex ("x0p D0     ", L2_1p, 1);
  printvektor2komplex ("x0p D0     ", L3_1p, 1);
  printf ("\n");
  }

