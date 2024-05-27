(define (domain gripper-strips)
;thuoc tinh
    (:predicates    (room ?r) ;r phong
                    (ball ?b) ;b banh
                    (gripper ?g) ; g canh tay robot
                    (at-robby ?r) ; robot dang tai phong r
                    (at ?b ?r) ;banh dang tai phong r
                    (free ?g) ;canh tay robot dang trong
                    (carry ?o ?g) 
    )
    
    (:action move
        ;tham so 
        :parameters (?from ?to) ;tu phong from den phong to
        ;dk tien quyet : phong from-to, robot dang tai from
        :precondition (and (room ?from) (room ?to) (at-robby ?from))
        ;ket qua
        :effect (and (at-robby ?to) (not(at-robby ?from)))
    )
    ;hanh dong nhat len
    (:action pick
        ;tham so - banh-phong-canh tay robot
        :parameters (?obj ?room ?gripper)
        ;dk tien quyet:
        ;obj-banh, room-phong, gripper-canh tay robot, 
        ;banh o phong, robot o phong, canh tay robot trong
        :precondition (and(ball ?obj) (room ?room) (gripper ?gripper)
        (at ?obj ?room) (at-robby ?room) (free ?gripper))
        
        ;ket qua: robot dang mang banh, banh khong trong phong,
        ;canh tay robot khong trong
        :effect (and (carry ?obj ?gripper) (not(at ?obj ?room)) (not(free ?gripper))) 
    )
    
    ;hanh dong de xuong
    (:action drop
        ;tham so
        :parameters  (?obj ?room ?gripper)
        ;dk tien quyet
        :precondition (and (ball ?obj) (room ?room) (gripper ?gripper) 
        (carry ?obj ?gripper) (at-robby ?room))
        ;ket qua
        :effect (and (at ?obj ?room) (free ?gripper) (not (carry ?obj ?gripper)))
    )
)

