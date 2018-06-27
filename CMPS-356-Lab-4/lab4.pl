/* Name: Cody Graves
*  Program: Lab 4
*  Date: 3/6/18
*/


membership(short,X,1) :- X < 160. 
membership(short,X,0) :- X >= 170.
membership(short,X,A) :- X < 170, A is -X/10 + 17, !.
membership(short,X,A) :- X >= 160, A is -X/10 + 17.

membership(average,X,1) :- X = 175.
membership(average,X,0) :- X < 165, !.
membership(average,X,0) :- X > 185.
membership(average,X,A) :- X > 175, A is -X/10 + 18.5, !. 
membership(average,X,A) :- X >= 165, A is X/10 - 16.5, !.
membership(average,X,A) :- X < 175, A is X/10 - 16.5, !.
membership(average,X,A) :- X =< 185, A is -X/10 + 18.5.

membership(tall,X,1) :- X > 190.
membership(tall,X,0) :- X < 180.
membership(tall,X,A) :- X >= 180, A is X/10 - 18, !.
membership(tall,X,A) :- X =< 190, A is X/10 - 18.

alittle(S,X,M) :- membership(S,X,A), M is A**1.3.
slightly(S,X,M) :- membership(S,X,A), M is A**1.7.
very(S,X,M) :- membership(S,X,A), M is A**2.
extremely(S,X,M) :- membership(S,X,A), M is A**3.

