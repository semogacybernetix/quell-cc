:pc     start
:return         0
:incr          -1
:anzahl         7
:decr           1
:schl       start

:start
        copy    :zcopy    bblock   :qcopy    ablock
        sub      zcopy    incr
        sub      qcopy    incr
        sub      anzahl   decr
        cond     endschl  anzahl
        copy     pc  :endschl  schl
        copy     pc   return
:ablock
        1 2 3 4 5 6 7 8 9 10 11
:bblock
        0 0 0 0 0 0 0 0 0  0  0
