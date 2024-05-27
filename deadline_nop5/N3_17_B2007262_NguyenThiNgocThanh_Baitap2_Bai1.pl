thucan('Ga').
thucan('Tao').
thucan(X) :- song(Y), an(Y,X).
song('Bill').
an('Bill', dauphong).
an('John', X) :- thucan(X).
an('Sue', X) :- an('Bill', X).