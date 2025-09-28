
//-------------------- lange Wege -------------------------------------------------------------------

void quartischwegdiffp (ckomplexk x1s, ckomplexk x2s, ckomplexk x3s, ckomplexk& x4s)
  {
  ckomplexk aq, bq, cq, dq, pq, qq, rq, ak, bk, ck, pk, qk, ad, bd, pd, x1l, y1d, y2d, ad2, x1d, x2d, xd, z1k, z2k, z3k, y1k, y2k, y3k, ak3, x1k, x2k, x3k, xk;
  ckomplexk z, u, a1, a2, b1, b2, y1q, y2q, y3q, y4q, aq4, x1q, x2q, x3q, x4q;
  ckomplexk dpyq, dpyk, dpyd, x1ks, x2ks, x3ks, bla, x1ds, x2ds;

  // normal -> zentriert: aq, bq, cq, dq -> pq, qq, rq
  pq= aq*aq*3/-8 + bq;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Parameter der kubischen Resolvente diffp aus den zentrierten quartischen Parametern: qpp, qqp, qrp -> akp, bkp, ckp
  ak= -pq;
  bk= rq*-4;
  ck= pq*rq*4 - qq*qq;

  // normal -> reduziert
  pk= ak*ak/-3 + bk;
  qk= ak*(ak*ak/real (4.5) - bk)/3 + ck;

  // Parameter der quadratischen Resolvente
  ad= qk;
  bd= pk*pk*pk/-27;

  // Parameter der reduzierten quadratischen Gleichung aus den Parametern der normalen quadratischen Gleichung
  pd= bd - ad*ad/4;

  // Lösung der normalen linearen Gleichung aus den Parametern der reduzierten quadratischen Gleichung
  x1l= -pd;

  // Rückübergabe der linearen Lösungen an die quadratischen Lösungen
  y1d=  sqrtv (x1l);
  y2d= -sqrtv (x1l);

  // Rücktransformation der Lösungen der reduzierten quadratischen Gleichung in die Lösungen der normalen quadratischen Gleichung
  ad2= ad/2;
  x1d= y1d - ad2;
  x2d= y2d - ad2;

  // Rückübergabe der quadratischen Lösungen an die kubischen Lösungen
  xd= x1d;
  cbrtv (xd, z1k, z2k, z3k);
  y1k= z1k - pk/(z1k*3);
  y2k= z2k - pk/(z2k*3);
  y3k= z3k - pk/(z3k*3);

  // Rücktransformation der Lösungen der reduzierten kubischen Gleichung in die Lösungen der normalen kubischen Gleichung
  ak3= ak/3;
  x1k= y1k - ak3;
  x2k= y2k - ak3;
  x3k= y3k - ak3;

  // Rückübergabe der kubischen Lösungen an die quartischen Lösungen (diffp)
  xk= x1k;

  z= xk;
  u= sqrtv (z - pq);

  a1=  u;
  a2= -u;
  b1= (z - qq/u)/2;
  b2= (z + qq/u)/2;

  quadratisch1 (a1, b1, y1q, y2q);
  quadratisch1 (a2, b2, y3q, y4q);

  // Rücktransformation der zentrierten quartischen Lösungen in die Lösungen der normalen quartischen Gleichung
  aq4= aq/4;
  x1q= y1q - aq4;
  x2q= y2q - aq4;
  x3q= y3q - aq4;
  x4q= y4q - aq4;
  }

void quartischwegpdfw2 (ckomplexk x1s, ckomplexk x2s, ckomplexk x3s, ckomplexk& x4s)
  {
  ckomplexk aq, bq, cq, dq, pq, qq, rq, ak, bk, ck, pk, qk, ad, bd, pd, x1l, y1d, y2d, ad2, x1d, x2d, xd, z1k, z2k, z3k, y1k, y2k, y3k, ak3, x1k, x2k, x3k, xk;
  ckomplexk z, u, a1, a2, b1, b2, y1q, y2q, y3q, y4q, aq4, x1q, x2q, x3q, x4q;
  ckomplexk dpyq, dpyk, dpyd, x1ks, x2ks, x3ks, bla, x1ds, x2ds;

  // zentrierte quartische Parameter aus den quartischen Parametern: aq, bq, cq, dq -> pq, qq, rq
  pq= aq*aq*3/-8 + bq;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Parameter der kubischen Resolvente pdfw2 aus den zentrierten quartischen Parametern: qpp, qqp, qrp -> akp, bkp, ckp
  ak= pq*2;
  bk= pq*pq - rq*4;
  ck= qq*qq*-1;

  // Parameter der reduzierten kubischen Gleichung aus den Parametern der kubischen Gleichung
  pk= ak*ak/-3 + bk;
  qk= ak*(ak*ak/real (4.5) - bk)/3 + ck;

  // Parameter der quadratischen Resolvente
  ad= qk;
  bd= pk*pk*pk/-27;

  // Parameter der reduzierten quadratischen Gleichung aus den Parametern der normalen quadratischen Gleichung
  pd= bd - ad*ad/4;

  // Lösung der normalen linearen Gleichung aus den Parametern der reduzierten quadratischen Gleichung
  x1l= -pd;

  // Rückübergabe der linearen Lösungen an die quadratischen Lösungen
  y1d=  sqrtv (x1l);
  y2d= -sqrtv (x1l);

  // Rücktransformation der Lösungen der reduzierten quadratischen Gleichung in die Lösungen der normalen quadratischen Gleichung
  ad2= ad/2;
  x1d= y1d - ad2;
  x2d= y2d - ad2;

  // Rückübergabe der quadratischen Lösungen an die kubischen Lösungen
  xd= x1d;
  cbrtv (xd, z1k, z2k, z3k);
  y1k= z1k - pk/(z1k*3);
  y2k= z2k - pk/(z2k*3);
  y3k= z3k - pk/(z3k*3);

  // Rücktransformation der Lösungen der reduzierten kubischen Gleichung in die Lösungen der normalen kubischen Gleichung
  ak3= ak/3;
  x1k= y1k - ak3;
  x2k= y2k - ak3;
  x3k= y3k - ak3;

  // Rückübergabe der kubischen Lösungen an die quartischen Lösungen (pdfw2)
  xk= x1k;

  z= xk;
  u= sqrtv (z);

  a1=  u;
  a2= -u;
  b1= (z + pq - qq/u)/2;
  b2= (z + pq + qq/u)/2;

  quadratisch1 (a1, b1, y1q, y2q);
  quadratisch1 (a2, b2, y3q, y4q);

  // Rücktransformation der zentrierten quartischen Lösungen in die Lösungen der normalen quartischen Gleichung
  aq4= aq/4;
  x1q= y1q - aq4;
  x2q= y2q - aq4;
  x3q= y3q - aq4;
  x4q= y4q - aq4;
  }

//-------------------- kurze Wege -------------------------------------------------------------------

void quartischwegdiffpkurz (ckomplexk aq, ckomplexk bq, ckomplexk cq, ckomplexk dq, ckomplexk& x1, ckomplexk& x2, ckomplexk& x3, ckomplexk& x4)
  {
  ckomplexk pq, qq, rq, pk, qk, xl, x1d, x2d, xd, z1k, z2k, z3k, x1k, x2k, x3k, xk;
  ckomplexk z, u, a1, a2, b1, b2, y1, y2, y3, y4;
  ckomplexk dpy, z1, z2, z3;

  // Parameter reduzierte quartische Gleichung
  pq= bq - aq*aq*3/8;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Parameter reduzierte kubische Gleichung
  pk= pq*pq/-3 - rq*4;
  qk= pq*(pq*pq/real (4.5) + rq*4)/-3 + pq*rq*4 - qq*qq;

  // Lösung normale lineare Gleichung
  xl= pk*pk*pk/27 + qk*qk/4;

  // Lösung normale quadratische Gleichung
  x1d= qk/-2 + sqrtv (xl);
  x2d= qk/-2 - sqrtv (xl);

  // Lösung normale kubische Gleichung
  xd= x1d;
  cbrtv (xd, z1k, z2k, z3k);

  x1k= z1k - pk/(z1k*3) + pq/3;
  x2k= z2k - pk/(z2k*3) + pq/3;
  x3k= z3k - pk/(z3k*3) + pq/3;

  // Lösungen reduzierte quartische Gleichung
  xk= x2k;

  z= xk;
  u= sqrtv (z - pq);

  a1=  u;
  a2= -u;
  b1= (z - qq/u)/2;
  b2= (z + qq/u)/2;

  quadratisch1 (a1, b1, y1, y2);
  quadratisch1 (a2, b2, y3, y4);

  // Lösungen normale quartische Gleichung
  x1= y1 - aq/4;
  x2= y2 - aq/4;
  x3= y3 - aq/4;
  x4= y4 - aq/4;
  }

void quartischwegz1kurz (ckomplexk x1, ckomplexk x2, ckomplexk x3, ckomplexk& x4)
  {
  ckomplexk aq, bq, cq, dq, pq, qq, rq, pk, qk, xl, x1d, x2d, xd, z1k, z2k, z3k, y1k, y2k, y3k, yk;
  ckomplexk z, u, a1, a2, b1, b2, y1q, y2q, y3q, y4q, aq4, x1q, x2q, x3q, x4q;
  ckomplexk dpx, z1, z2, z3;

  // Parameter reduzierte quartische Gleichung
  pq= bq - aq*aq*3/8;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Parameter reduzierte kubische Gleichung
  pk= (pq*pq + rq*12)/-3;
  qk= pq*(rq*36 - pq*pq)/real (13.5) - qq*qq;

  // Lösung normale lineare Gleichung
  xl= pk*pk*pk/27 + qk*qk/4;

  // Lösung normale quadratische Gleichung
  x1d= qk/-2 + sqrtv (xl);
  x2d= qk/-2 - sqrtv (xl);

  // Lösung reduzierte kubische Gleichung
  xd= x2d;
  cbrtv (xd, z1k, z2k, z3k);

  y1k= z1k - pk/(z1k*3);
  y2k= z2k - pk/(z2k*3);
  y3k= z3k - pk/(z3k*3);

  // Lösungen reduzierte quartische Gleichung
  yk= y1k;

  z= yk;
  u= sqrtv (z - pq*2/3);

  a1=  u;
  a2= -u;
  b1= (z + pq/3 - qq/u)/2;
  b2= (z + pq/3 + qq/u)/2;

  quadratisch1 (a1, b1, y1q, y2q);
  quadratisch1 (a2, b2, y3q, y4q);

  // Lösungen normale quartische Gleichung
  aq4= aq/4;
  x1q= y1q - aq4;
  x2q= y2q - aq4;
  x3q= y3q - aq4;
  x4q= y4q - aq4;
  }

void quartischwegz3kurz (ckomplexk x1s, ckomplexk x2s, ckomplexk x3s, ckomplexk& x4s)
  {
  ckomplexk aq, bq, cq, dq, pq, qq, rq, pk, qk, xl, x1d, x2d, xd, z1k, z2k, z3k, y1k, y2k, y3k, yk;
  ckomplexk z, u, a1, a2, b1, b2, y1q, y2q, y3q, y4q, aq4, x1q, x2q, x3q, x4q;
  ckomplexk dpyq, dpyk, dpxd, x1ks, x2ks, x3ks, xks3, bla, x1ds, x2ds;

  // Parameter reduzierte quartische Gleichung
  pq= bq - aq*aq*3/8;
  qq= aq*(aq*aq - bq*4)/8 + cq;
  rq= aq*((aq*bq - cq*4)*16 - aq*aq*aq*3)/256 + dq;

  // Parameter reduzierte kubische Gleichung
  pk= -(pq*pq + rq*12)/3;
  qk= pq*(rq*36 - pq*pq)/real (13.5) - qq*qq;

  // Lösung normale lineare Gleichung
  xl= pk*pk*pk*27 + qk*qk*real (182.25);

  // Lösung normale quadratische Gleichung
  x1d= qk*real (-13.5) + sqrtv (xl);
  x2d= qk*real (-13.5) - sqrtv (xl);

  // Lösung reduzierte kubische Gleichung
  xd= x2d;
  cbrtv (xd, z1k, z2k, z3k);

  y1k= z1k - pk*3/z1k;
  y2k= z2k - pk*3/z2k;
  y3k= z3k - pk*3/z3k;

  // Lösungen reduzierte quartische Gleichung
  yk= y1k;

  z= yk;
  u= sqrtv ((z - pq*2)/3);

  a1=  u;
  a2= -u;
  b1= ((z + pq)/3 - qq/u)/2;
  b2= ((z + pq)/3 + qq/u)/2;

  quadratisch1 (a1, b1, y1q, y2q);
  quadratisch1 (a2, b2, y3q, y4q);

  // Lösungen normale quartische Gleichung
  aq4= aq/4;
  x1q= y1q - aq4;
  x2q= y2q - aq4;
  x3q= y3q - aq4;
  x4q= y4q - aq4;
  }
