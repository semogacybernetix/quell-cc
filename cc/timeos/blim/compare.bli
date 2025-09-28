:pc        loopstart
:null              0
:eins              1
:minuseins        -1
:fgleich           1
:anz               9
:puffer            0
:loopscan  loopstart
:raus       ungleich
:araus          raus

:loopstart
     copy  puffer   :cblock1
                     block1
     sub   puffer   :cblock2
                     block2
     cond  weiter    puffer
     copy  pc       :weiter
                     raus
     copy  weiter    araus
     sub   cblock1   minuseins
     sub   cblock2   minuseins
     sub   anz       eins
     cond  cloop     anz
     copy  pc       :cloop
                     loopscan
     copy  pc        null

:ungleich
     copy  fgleich   null
     copy  pc        null

:block1
     2 34 -38 2349 16 8 22 407 675

:block2
     2 34 -38 2349 16 8 22 407 675
