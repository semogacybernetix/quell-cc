void kubischreduziertvieta (ckomplexk p, ckomplexk q, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3) //***********************************************************************  in cardano eingebaut
  {
  ckomplexk  m, n, u, v, z1, z2, z3;

  // Vieta-Transformation y= z - p/(3z), u= z³, u² + qu - p³/27 = 0
  m= q;
  n= -p*p*p/27;

  quadratisch (m, n, u, v);

  if (absv (v) > absv (u))                     // die betragsmäßig größere Lösung nehmen um von der Division durch 0 wegzukommen
    u= v;

  if (absv (u) == 0)                           // eine dreifache Lösung bei p = q = 0
    {
    x1= 0;
    x2= 0;
    x3= 0;
    return;
    }

  z1= cbrtv (u);
  z2= z1*e31;
  z3= z1*e32;

  // --------------------------- Rücktransformation
  x1= z1 - p/(3*z1);
  x2= z2 - p/(3*z2);
  x3= z3 - p/(3*z3);
  }
