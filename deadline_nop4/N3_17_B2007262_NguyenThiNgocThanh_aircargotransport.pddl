(define (domain air-cargo)
    ;yeu cau
    (:requirements :strips)
    ;thuoc tinh
    (:predicates 
        (In ?obj ?place) (At ?obj ?place) ;doi tuong o dau va tai dau
        (Cargo ?obj) (Plane ?obj) (Airport ?obj); doi tuong la kien hang, may bay,san bay
    )
    ;co 3 hd: LOAD-len, UNLOAD-xuong, FLY-bay
    ;hanh dong dua kien hang len
    (:action LOAD
        ;tham so
        :parameters (?c ?p ?a);cargo - plane - Airport
        ;dieu kien tien quyet
        ;kien hang tai sanbay-maybay tai sanbay-kienhang?-maybay?-sanbay?
        :precondition (and (At ?c ?a) (At ?p ?a) (Cargo ?c) (Plane ?p) (Airport ?a))
        ;ket qua mong muon
        :effect (and (In ?c ?p) (not(At ?c ?a))); c o tren maybay, c khong o tai sanbay
    )
    ;hanh dong chuyen kein hang xuong
    (:action UNLOAD-xuong
        ;tham so
        :parameters (?c ?p ?a)
        ;dieu kien tien quyet
        :precondition (and(In ?c ?p) (At ?p ?a) (Cargo ?c) (Plane ?p) (Airport ?a))
        ;ket qua mong muon
        :effect (and (not(In ?c ?p)) (At ?c ?a))
    )
    
    ;hanh dong bay
    (:action FLY
        ;tham so
        :parameters (?p ?from ?to) ;sanbay-from,to; may bay; p
        ;dieu kien tien quyet
        :precondition (and (At ?p ?from) (Plane ?p) (Airport ?from) (Airport ?to))
        ;ket qua mong muon
        :effect (and(At ?p ?to) (not(At ?p ?from)))
    )
)