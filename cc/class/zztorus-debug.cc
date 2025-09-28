
//---------------------------------------------------  torus debug ------------------------------------------------------------------------------------------
//*
void cstorus::berechne (const cvektor3 &rv, cschnittpunkte &psp)
  {
  real rq, rvq, rov, ovq, A, B, C, D, E;
  real rx, ry, rz, ox, oy, oz;
  real rxq, ryq, rzq, oxq, oyq, ozq;
  ckomplexk x1, x2, x3, x4;

  rx= rv.x;
  ry= rv.y;
  rz= rv.z;
  ox= ov.x;
  oy= ov.y;
  oz= ov.z;
  rxq= q(rx);
  ryq= q(ry);
  rzq= q(rz);
  oxq= q(ox);
  oyq= q(oy);
  ozq= q(oz);

  rq= r*r;
  rvq= rv%rv;
  rov= rv%ov;
  ovq= ov%ov;

  A= q(rxq) + q(ryq) + q(rzq) + 2*(q(rx*ry) + q(ry*rz) + q(rz*rx));
  B= 4*(rxq*rx*ox + ryq*ry*oy + rzq*rz*oz + rx*ry*(rx*oy + ry*ox) + ry*rz*(ry*oz + rz*oy) + rz*rx*(rz*ox + rx*oz));
  C= 2*(3*(rxq*oxq + ryq*oyq + rzq*ozq) + (1-rq)*rvq + q(rx*oy + ry*ox) + 2*rx*oy*ry*ox + q(ry*oz + rz*oy) + 2*ry*oz*rz*oy + q(rz*ox + rx*oz) + 2*rz*ox*rx*oz - 2*(rxq + ryq));
  D= 4*(rx*oxq*ox + ry*oyq*oy + rz*ozq*oz + (1-rq)*rov + (rx*oy + ry*ox)*ox*oy + (ry*oz + rz*oy)*oy*oz + (rz*ox + rx*oz)*oz*ox - 2*(rx*ox + ry*oy));
  E= q(oxq) + q(oyq) + q(ozq) + (2-2*rq)*ovq + 2*(q(ox*oy) + q(oy*oz) + q(oz*ox)) + q(1-rq) - 4*(oxq + oyq);

  quartisch (B/A, C/A, D/A, E/A, x1, x2, x3, x4);

  if (ag (x1) < 1e-8)
    {
    psp.add (x1.x);
    cvektor3 p1= x1.x*rv + ov;
    printf ("p1.x: %20.10lf p1.y: %20.10lf p1.z: %20.10lf\n", p1.x, p1.y, p1.z);
    real t1= q(q(p1.x) + q(p1.y) + q(p1.z) + rq1) - 4*(q(p1.x) + q(p1.y));
    printf ("t1: %20.10lf\n", t1);
    }
  if (ag (x2) < 1e-8)
    {
    psp.add (x2.x);
    cvektor3 p2= x2.x*rv + ov;
    real t2= q(q(p2.x) + q(p2.y) + q(p2.z) + rq1) - 4*(q(p2.x) + q(p2.y));
    printf ("t2: %20.10lf\n", t2);
    }

  if (ag (x3) < 1e-8)
    {
    psp.add (x3.x);
    cvektor3 p3= x3.x*rv + ov;
    real t3= q(q(p3.x) + q(p3.y) + q(p3.z) + rq1) - 4*(q(p3.x) + q(p3.y));
    printf ("t3: %20.10lf\n", t3);
    }
  if (ag (x4) < 1e-8)
    {
    psp.add (x4.x);
    cvektor3 p4= x4.x*rv + ov;
    real t4= q(q(p4.x) + q(p4.y) + q(p4.z) + rq1) - 4*(q(p4.x) + q(p4.y));
    printf ("t4: %20.10lf\n", t4);
    }
//*/
