:pc         start
:return         0
:awert        430
:anz           25
:incr         -11
:decr           1
:schl       start

:start
        sub     awert    incr
        sub     anz      decr
        cond    endschl  anz
        copy    pc      :endschl
                         schl
        copy    pc       return
