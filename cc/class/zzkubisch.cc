
void kubischelementar (ckomplexk a, ckomplexk b, ckomplexk c, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3)
  {
  real br, cr, dw;
  ckomplexk f1, f2, r1, r2;

  br= b.x;
  cr= c.x;

  dw= sqrtr (br*br*br*-4 + cr*cr*-27);

  // die f's aus den Koeffizienten real und imaginär getrennt berechnet
  f1= ckomplexk (cr*27/-2, dw*sqrtr (real (6.75)));
  f2= ckomplexk (cr*27/-2, dw*-sqrtr (real (6.75)));

  // die Kubikwurzeln der f's
  r1= cbrtr (f1);
  r2= cbrtr (f2);

  // die Lösungen aus den Koeffizienten
  x1= (r1 + r2)/3;
  x2= (r1*e32 + r2*e31)/3;
  x3= (r1*e31 + r2*e32)/3;

  printvektor2komplex ("f1", f1, 0);
  printvektor2komplex ("f2", f2, 0);
  printtext ("\n");

  printvektor2komplex ("r1", r1, 0);
  printvektor2komplex ("r2", r2, 0);
  printtext ("\n");

  printvektor2komplex ("x1", x1, 0);
  printvektor2komplex ("x2", x2, 0);
  printvektor2komplex ("x3", x3, 0);
  printtext ("\n");
  }

void kubischreduziertreellelementar (real p, real q, real& y)
  {
  real dw;
  ckomplexk f1, f2, r1, r2, y1, y2, y3;

  dw= sqrtr (p*p*p*-4 + q*q*-27);

  f1= ckomplexk (q*real (-13.5), dw*wu675);
  f2= ckomplexk (q*real (-13.5), dw*-wu675);
  r1= cbrtr (f1);
  r2= cbrtr (f2);
  y= (r1.x + r2.x)/3;

  //return;

  y1= (r1 + r2)/3;
  y2= (r1*e32 + r2*e31)/3;
  y3= (r1*e31 + r2*e32)/3;

  printtext ("-------------------------- kubischreduziertreellelementardebug ------------------------------------\n");
  printvektor2komplex ("f1", f1, 0);
  printvektor2komplex ("f2", f2, 0);
  printtext ("\n");

  printvektor2komplex ("r1", r1, 0);
  printvektor2komplex ("r2", r2, 0);
  printtext ("\n");

  printvektor2komplex ("y1", y1, 0);
  printvektor2komplex ("y2", y2, 0);
  printvektor2komplex ("y3", y3, 0);
  printtext ("---------------------------------------------------------------------------------------------------\n");
  printtext ("\n");
  }

