giaithua(0, 1).
giaithua(X, Y) :-
	X > 0,
	X1 is X -1,
	giaithua(X1, Y1),
	Y is X * Y1.

C(0, N, 1). %NC0=1.
C(1, N, N). %NC1=N.
C(N, N, 1). %NCN=1.

C(X, N, result):-
	giaithua(N, result1),
	giaithua(X, result2),
	X1 is N - X,
	giaithua(X1, result3),
	result is result1 / ( result2 * result3).
	
	