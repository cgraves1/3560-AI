item(a).
item(b).
item(c).
item(d).
item(e).

item(z) :- item(y), item(d).
item(y) :- item(x), item(b), item(e).
item(x) :- item(a).
item(l) :- item(c).
item(n) :- item(l), item(m).
