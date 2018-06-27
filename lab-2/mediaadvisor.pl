/* Name: Cody Graves
*  Program: Lab 2
*  Date: 2/13/18

    start with ?- go.     */

go :- hypothesize(Media),
      write('The best medium is: '),
      write(Media),
      nl,
      undo.

/* hypotheses to be tested */
hypothesize(workshop)   :- workshop, !.
hypothesize(lecture)     :- lecture, !.
hypothesize(videocassette)   :- videocassette, !.
hypothesize(roleplayexersise)     :- roleplayexercise, !.
hypothesize(unknown).             /* no diagnosis */

/* medium identification rules */
workshop :- ss_phys_obj, sr_hands_on, verify(feedback).
videocassette :- ss_visual, sr_documented, verify(feedback).
roleplayexercise :- ss_verbal, sr_oral, verify(feedback).
lecture :- ss_symbolic, sr_analytical, verify(feedback).
lecture :- ss_visual, sr_oral, verify(feedback).
lecture :- ss_verbal, sr_analytical, verify(feedback).

/* classification rules */
ss_verbal :- verify(env_paper), !.
ss_verbal :- verify(env_manuals), !.
ss_verbal :- verify(env_documents), !.
ss_verbal :- verify(env_textbooks).

ss_visual :- verify(env_pictures), !.
ss_visual :- verify(env_pictures), !.
ss_visual :- verify(env_pictures), !.
ss_visual :- verify(env_pictures).

ss_phys_obj :- verify(env_machines), !.
ss_phys_obj :- verify(env_buildings), !.
ss_phys_obj :- verify(env_tools).

ss_symbolic :- verify(env_numbers), !.
ss_symbolic :- verify(env_formulas), !.
ss_symbolic :- verify(env_computer programs).

sr_oral :- verify(job_lecturing), !.
sr_oral :- verify(job_advising), !.
sr_oral :- verify(job_counselling).

sr_hands_on :- verify(job_building), !.
sr_hands_on :- verify(job_repairing), !.
sr_hands_on :- verify(job_troubleshooting).

sr_documented :- verify(job_writing), !.
sr_documented :- verify(job_typing), !.
sr_documented :- verify(job_drawing).

sr_analytical :- verify(job_evaluating), !.
sr_analytical :- verify(job_reasoning), !.
sr_analytical :- verify(job_investigating).





/* how to ask questions */
ask(Question) :-
    write('Does following attribute apply: '),
    write(Question),
    write('? '),
    read(Response),
    nl,
    ( (Response == yes ; Response == y)
      ->
       assert(yes(Question)) ;
       assert(no(Question)), fail).

:- dynamic yes/1,no/1.

/* How to verify something */
verify(S) :-
   (yes(S) 
    ->
    true ;
    (no(S)
     ->
     fail ;
     ask(S))).

/* undo all yes/no assertions */
undo :- retract(yes(_)),fail. 
undo :- retract(no(_)),fail.
undo.
