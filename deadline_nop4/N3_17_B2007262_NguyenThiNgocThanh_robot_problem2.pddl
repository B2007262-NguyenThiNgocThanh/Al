(define (problem strips-gripper4)

    (:domain gripper-strips) ;goi ham
    
    ;dinh nghia cac doi tuong
    (:objects rooma roomb ball1 ball2 ball3 ball4 left right)
    
    ;khoi tao doi tuong
    (:init 
        (room rooma) (room roomb) ;phong
        (ball ball1) (ball ball2) (ball ball3) (ball ball4) ;banh
        (gripper left) (gripper right) ; canh tay trai - phai
        (at-robby rooma) ;robot tai phong a
        (free left) (free right) ;2 tay robot trong
        (at ball1 rooma) (at ball2 rooma) (at ball3 rooma) (at ball4 rooma) ;2 trai banh trong phong a
    )
    ;ket qua mong muon : 3 trai banh o phong b
    (:goal 
        (and(at ball1 roomb) (at ball2 roomb) (at ball3 roomb))
    )

)