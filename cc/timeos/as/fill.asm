:pc     start
:return         0
:incr          -1
:anzahl       200
:decr           1
:fuell        515
:schl     start

:start
        copy   :zblock
                block      fuell
        sub     zblock     incr
        sub     anzahl     decr
        cond    endschl    anzahl
        copy    pc        :endschl
                           schl
        copy    pc         return
:block
