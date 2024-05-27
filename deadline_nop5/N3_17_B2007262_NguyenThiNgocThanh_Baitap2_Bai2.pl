nguoi('Marcus').
pompeian('Marcus').
lama(X) :- pompeian(X).
lanhchua('Ceasar').
khongtrungthanh('Marcus', 'Ceasar').
amsat(X, Y):- lama(X),khongtrungthanh(X, Y), lanhchua(Y).
