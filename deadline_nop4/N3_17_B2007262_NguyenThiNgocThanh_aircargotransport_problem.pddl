(define (problem pb1)
    (:domain air-cargo) ;goiham
    ;doi tuong
    (:objects c1 c2 p1 p2 sfo jfk)
    ;khoi tao
    (:init
        ;type
        (Cargo c1) (Cargo c2) (Plane p1) (Plane p2) (Airport sfo) (Airport jfk)
        ;location
        (At c1 sfo) (At c2 jfk) (At p1 sfo) (At p2 jfk)
    )
    ;ket qua mong muon
    (:goal (and(At c1 jfk) (At c2 sfo)))
)