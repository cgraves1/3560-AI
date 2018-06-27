item(a,1.0).
item(b,0.70).
item(c,0.75).
item(d,0.80).
item(e,0.50).
item(m,-1.0).

item(z,CF) :- item(y,FY), item(d,FD), min(FY,FD,X), CF is X*0.70 .
item(y,CF) :- item(x,FX), item(b,FB), item(e,FE), min(FX,FB,FE,X), CF is X*0.95.
item(x,CF) :- item(a,F), CF is F*1.0.
item(l,CF) :- item(c,F), CF is F*0.85.
item(n,CF) :- item(l,FL), item(m,FM), min(FL,FM,X), CF is X*1.00.


min(X,Y,Z) :- (X=<Y), Z is X, !.
min(X,Y,Z) :- (Y=<X), Z is Y.
min(X,Y,Z,Q) :- (X=<Y), (X=<Z), Q is X, !.
min(X,Y,Z,Q) :- (Y=<X), (Y=<Z), Q is Y, !.
min(X,Y,Z,Q) :- (Z=<X), (Z=<Y), Q is Z.
