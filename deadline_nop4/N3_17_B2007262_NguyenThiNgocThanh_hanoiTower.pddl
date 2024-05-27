(define (domain hanoi)

    (:requirements :strips)
    ;thuoc tinh
    (:predicates    (clear ?x) ;tren x hog co dia nao- x la dia nho nhat
                    (on ?x ?y);dia x nam tren y
                    (larger ?x ?y);dia x > y ( small ?x ?y)_ y > x
    )
    ;di chuyen
    (:action move
        ;tham so
        :parameters (?disc ?from ?to) ;cai dia-cac cot cung duoc xem nhu dia lon nhat
        ;dieu kien tien quyet
        :precondition (and (larger ?to ?disc)  ;dia to > disc
        (on ?disc ?from);disc tren from 
        (clear ?disc);disc min
        (clear ?to)); dia to khong co dia nao o tren
        
        :effect (and (clear ?from) ;tren from ko co dia khac
        (on ?disc ?to) ;disc tren to
        (not(on ?disc ?from)) (not(clear ?to))
        )
    )
)