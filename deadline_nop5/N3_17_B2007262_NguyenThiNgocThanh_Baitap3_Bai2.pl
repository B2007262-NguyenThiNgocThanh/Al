move(1, A, B, C) :- 
	write('from '),
	write(A),
	write(' to '),
	write(C),
	nl. %true
	
move(N, A, B, C):-
	N>1,
	Move is N -1,
	move(Move, A, C, B),
	move(1, A, B, C),
	move(Move, B, A, C).
	