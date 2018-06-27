car(gray).
color(a,orange).
color(b,tan).
shape(a,round).
shape(b,round).
ate(albert,b).
ate(jane,salad).
hamburger(X) :- color(X,tan), shape(X,round).
orange(X) :- color(X,orange), shape(X,round).
full(X) :- ate(X, Y), hamburger(Y).
