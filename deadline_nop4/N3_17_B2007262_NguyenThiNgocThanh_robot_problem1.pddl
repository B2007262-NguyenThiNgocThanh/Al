(define (problem1 strips-gripper2)
    ;;goi domain
    (:domain gripper-strips)
    ;;doi tuong
    (:objects rooma roomb ball1 ball2 left right)
    ;;khoi tao doi tuong
    (:init 
        (room rooma) (room roomb) (ball ball1) (ball ball2) 
        (gripper left) (gripper right) (at ball1 rooma) (at ball2 rooma)
        (at-robby rooma) (free left) (free right)
    )
    
    (:goal (and(at ball1 roomb)))
) 