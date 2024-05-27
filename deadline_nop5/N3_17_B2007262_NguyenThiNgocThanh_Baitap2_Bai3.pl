%gioitinh(X).
nam(an).
nam(anh).
nam(ha).

nam(duc). %chu
nam(phong). %bactrai
nam(thinh). %cau
nam(thoai).
nam(cuong).

nu(co).
nu(binh).
nu(lan). %co
nu(hong). %di
nu(nguyen). %mo
nu(them). %thim
nu(ut). %bacgai

nu(cat).
nu(chau).

%tuoi(X,Y).
tuoi(an, 9).
tuoi(anh, 22).
tuoi(co, 17).

tuoi(ha, 50).
tuoi(binh, 47).
tuoi(duc, 45).
tuoi(phong, 53).
tuoi(thinh, 55).
tuoi(lan, 52).
tuoi(hong, 48).

%cha(X,Y).
cha(ha, an).
cha(ha, anh).
cha(ha, co).
cha(cuong, ha).
cha(cuong, duc).
cha(cuong, phong).
cha(cuong, lan).
cha(thoai, thinh).
cha(thoai, binh).
cha(thoai, hong).

%me(X,Y).
me(binh, an).
me(binh, anh).
me(binh, co).
me(chau, ha).
me(chau, duc).
me(chau, phong).
me(chau, lan).
me(cat, thinh).
me(cat, binh).
me(cat, hong).

%chong(X, Y).
chong(ha, binh).
chong(thinh, nguyen).
chong(duc, them).
chong(phong, ut).
chong(cuong, chau).
chong(thoai, cat).

vo(Y, X) :- chong(X, Y).

bigger(X, Y) :- (X>Y -> true; false).

%a
anhruot(X, Y) :- nam(X), cha(F1, X), cha(F1, Y), me(F2, X), me(F2, Y),tuoi(X, T1), tuoi(Y, T2), bigger(T1, T2).
chiruot(X, Y) :- nu(X), cha(F1, X), cha(F1, Y), me(F2, X), me(F2, Y),tuoi(X, A1), tuoi(Y, A2), bigger(A1, A2).
emtrairuot(X, Y):-nam(X), cha(F1, X), cha(F1, Y),me(F2, X), me(F2, Y),tuoi(X, B1), tuoi(Y, B2), bigger(B2, B1).
emgairuot(X, Y):- nu(X), cha(F1, X), cha(F1, Y),me(F2, X), me(F2, Y), tuoi(X, C1), tuoi(Y, C2), bigger(C2, C1).
%b
chu(X, Z) :- emtrairuot(X, F1), cha(F1, Z).
bactrai(X, Z):- anhruot(X, F1), cha(F1, Z).
cau(X, Z) :- anhruot(X, F2),me(F2, Z); emtrairuot(X, F2), me(F2, Z).

%c
co(X, Z) :- emgairuot(X, F1), cha(F1, Z); chiruot(X, F1), cha(F1, Z).
di(X, Z) :- emgairuot(X, F2), me(F2, Z); chiruot(X, F2), me(F2, Z).
mo(X, Z) :- chong(Y, X), cau(Y, Z).
thim(X, Z) :- chong(Y, X), chu(Y, Z).
bacgai(X, Z):- chong(Y, X), bactrai(Y, Z).

%d
ongnoi(X, Z):- cha(X, F1), cha(F1, Z).
ongngoai(X, Z):-cha(X, F2), me(F2, Z).

%e
banoi(X, Z):-me(X, F1), cha(F1, Z).
bangoai(X, Z):- me(X, F2), me(F2, Z).

%f
chavo(X, C):- cha(X, F2), vo(F2, C).
mevo(Y, C):- chavo(X, C), vo(Y, X).
chachong(X, V):-cha(X, F1), chong(F1, V).
mechong(Y, V):-chachong(X, V), vo(Y, X).