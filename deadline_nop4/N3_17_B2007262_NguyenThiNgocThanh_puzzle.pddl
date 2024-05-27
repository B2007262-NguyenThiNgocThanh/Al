(define (domain strips-sliding-tile)
    ;yeu cau
    (:requirements :strips)
    ;thuoc tinh
    (:predicates 
        (tile ?x) (position ?x) (at ?t ?x ?y) ;o so , vi tri, o so dang o dong x cot y
        (blank ?x ?y) (inc ?p ?pp) (dec ?p ?pp) ;o trong odong x cot y, cong vi tri, tru vi tri 
    )
    
    ;co 4 hanh dong: 
    ;di chuyen len
    (:action move-up
        ;tham so
        :parameters (?ex ?ey ?t ?tx)
        ;dieu kien tien quyet
        :precondition 
        ;t-oso ,ex ey- vitri dongcot o trong, tx vitri dong tren t co giatri
        (and(tile ?t) (position ?ex) (position ?ey) (position ?tx)
        ;tx-ex, o trong dang o dong ex cot ey, t dang tai dong tx cot ey
        (dec ?ex ?tx) (blank ?ex ?ey) (at ?t ?tx ?ey))
        ;ket qua mong muon
        :effect (and (not(blank ?ex ?ey)) (blank ?tx ?ey)
        (not(at ?t ?tx ?ey)) (at ?t ?ex ?ey))
    )
    ;di chuyen xuong
    (:action move-down
        ;tham so
        :parameters (?ex ?ey ?t ?tx)
        ;dieu kien tien quyet
        :precondition (and (tile ?t) (position ?ex) (position ?ey) (position ?tx)
        (inc ?ex ?tx) (blank ?ex ?ey) (at ?t ?tx ?ey))
        ;ket qua mong muon
        :effect (and(not(blank ?ex ?ey)) (blank ?tx ?ey)
        (not(at ?t ?tx ?ey)) (at ?t ?ex ?ey))
    )
    ;di chuyen sang trai
    (:action move-left
        ;tham so
        :parameters (?t ?ex ?ey ?ty)
        ;dieu kien tien quyet
        :precondition (and (tile ?t) (position ?ex) (position ?ey) (position ?ty)
        (dec ?ey ?ty) (blank ?ex ?ey) (at ?t ?ex ?ty))
        :effect (and(not(blank ?ex ?ey)) (blank ?ex ?ty)
        (not(at ?t ?ex ?ty)) (at ?t ?ex ?ey))
    )
    ;di chuyen sang phai
    (:action right
        ;tham so
        :parameters (?t ?ex ?ey ?ty)
        ;dieu kien tien quyet
        :precondition (and(tile ?t) (position ?ex) (position ?ey) (position ?ty)
        (inc ?ey ?ty) (blank ?ex ?ey) (at ?t ?ex ?ty))
        ;ket qua mong doi
        :effect (and (not(blank ?ex ?ey)) (blank ?ex ?ty)
        (not(at ?t ?ex ?ty)) (at ?t ?ex ?ey))
        
    )
)