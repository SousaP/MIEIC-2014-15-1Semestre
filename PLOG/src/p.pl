:-use_module(library(random)).
board(        
[[0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 ['A',' ',0,' ',0,' ',0,' ',0,' ',0,' ','B'],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0],
 [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '],
 [0,' ',0,' ',0,' ',0,' ',0,' ',0,' ',0]]
).


% para paredes: ' ' se nao tiver, '-' se tiver
% 0 para celulas neutras
% A para c�lulas com pe�o do jogador 1 sem parede por baixo
% B para c�lulas com pe�o do jogador 2 sem parede por baixo

%----------------------------------------------------------------------------
% check mov limit
checkLimit(Xinicial, Yinicial, Xfinal, Yfinal):-
        Xinicial > -1,
        Xinicial < 7,
        Xfinal > -1,
        Xfinal < 7,
        Yinicial > -1,
        Yinicial < 7,
        Yfinal > -1,
        Yfinal < 7.

checkLimit(X,Y):-
       X > -1,
        X < 13,
       Y> -1,
       Y< 13.



%----------------------------------------------------------------------------
%print lists
printline([]).
printline([H|T]):- write(H), printline(T).


%----------------------------------------------------------------------------

%print board
drawWalls([H|T],C):- write('  |'), printline(H), write('|'), nl, draw(T,C).
drawWalls([],_).
draw([H|T],C):-  write(C), NewC is C+1,write('.|'), printline(H), write('|'), nl,drawWalls(T,NewC).
draw([],_).
drawBoard(B):- nl,printline(['   ',0,' ',1,' ',2,' ',3,' ',4,' ',5, ' ',6]), nl,
        printline(['   ','-','-','-','-','-','-','-','-','-','-','-', '-','-']),
        nl, draw(B,0),
        printline(['   ','-','-','-','-','-','-','-','-','-','-','-', '-','-']), nl,nl.


%----------------------------------------------------------------------------
% Returns Element as the element of the list of lists at [Yindex][Xindex]     
elementAt([], _, -1):-!,fail.

elementAt([Elem|_], Elem, 0).

elementAt([_|T], Elem, X):-
        elementAt(T, Elem, NX),
        X is NX+1.
        
elementAt([], _, _, -1):-!, fail.

elementAt([H|_], Elem, X, 0):-
        elementAt(H, Elem, X).

%X = Col, Y = Line
elementAt([_|T], Elem, X, Y):-
          elementAt(T, Elem, X, NY),
          Y is NY+1.


%----------------------------------------------------------------------------
% Change player turn

changeActivePlayer(P, P1) :-
    P = 1,
    P1 is 2.
changeActivePlayer(P, P1) :-
    P = 2,
    P1 is 1.

%----------------------------------------------------------------------------
% Writes Turn
print_turn(1):-
        write('Blue turn: '),
        nl.
print_turn(2):-
        write('Red turn: '),
        nl.

%----------------------------------------------------------------------------
% Replaces the value of the element in the index Index to Elem 
replace([_|T], 0, Elem, [Elem|T]).

replace([H|T], Index, Elem, [H|R]):- 
        Index > -1, 
        NIndex is Index-1, 
        replace(T, NIndex, Elem, R), 
        !.

replace(List, _, _, List).


% Replaces the value of the element in (IndexX, IndexY) to Elem
replace([H|T], IndexX, 0, Elem, [X|T]):-
        replace(H, IndexX, Elem, X).
                                          
replace([H|T], IndexX, IndexY, Elem, [H|R]):-
        IndexY > -1, 
        NIndexY is IndexY-1, 
        replace(T, IndexX, NIndexY, Elem, R), 
        !.
        
replace(List, _, _,_, List).            

%-------------------------------------------------------------------
%make move
makeMov(B,Xi,Yi,Xf,Yf).


%---------------------------------------------------------------
%check move

checkCurve(B,Xinicial, Yinicial, Xfinal, Yfinal).
checkMov(B,Xinicial, Yinicial, Xfinal, Yfinal) :-checkLimit(Xinicial, Yinicial, Xfinal, Yfinal),!, checkCurve(B,Xinicial, Yinicial, Xfinal, Yfinal).
checkMov(_,_, _, _, _) :- fail.


%colocar um peao
checkMov(B,X,Y) :- checkLimit(X,Y),elementAt(B, Elem, X, Y), Elem \= ' ', !, checkArea(NrP,X,Y,B,_), NrP > 1,!.
checkMov(_,_,_) :-fail.



addNrP('A',NrP) :- NrP is 1.
addNrP('B',NrP) :- NrP is 1.
addNrP(_,NrP) :- NrP is 0.

checkArea(NrP,X,Y,ToVisit,Visited):- checkLimit(X,Y),elementAt(ToVisit,Elem,X,Y), Elem \= 'X',!,addNrP(Elem,NrI),
        replace(ToVisit,X,Y,'X',V0),
        Nx is X+1,
        checkArea(NrP1,Nx,Y,V0,V1),
         Ny is Y +1,
       checkArea(NrP3,X,Ny,V1,V2),
        Nx2 is X-1,
       checkArea(NrP2,Nx2,Y,V2,V3),
        Ny2 is Y-1,
        checkArea(NrP4,X,Ny2,V3,V4),
        Visited = V4,
        NrP is NrI + NrP1 + NrP2 + NrP3 + NrP4
        .  


checkArea(0, _, _, T, T).
%-----------------------------------------------------------------------
%input para a jogada
getMov(B,Xi,Yi,Xf,Yf) :- nl,
                        print('\nColuna da peca a mover : '),read(Xi),
                        print('\nLinha da peca a mover : '),read(Yi),
                        print('\nColuna da casa destino : '),read(Xf),
                        print('\nLinha da casa destino : '),read(Yf), checkMov(B,Xi,Yi,Xf,Yf), ! .
getMov(Xi,Yi,Xf,Yf) :- nl,write('Jogada nao permitida'),getMov(Xi,Yi,Xf,Yf).

getPiece(B,X,Y):- nl,
                        print('\nColuna da peca: '),read(X),
                        print('\nLinha da peca: '),read(Y),checkMov(B,X,Y), ! .
getPiece(B,X,Y) :- nl,write('Posicao nao permitida'),getPiece(B,X,Y).

mov(B,1) :- getPiece(B,_,_).
mov(B,2) :- getMov(B,_,_,_,_).
mov(B,_) :- selectMov(B,_).
    

selectMov(B,R) :- print('\n[1]Colocar peao\n[2]Mover peao\n'),read(R), mov(B,R).


%-----------------------------------------------------------------------
%into
getIntro(P) :- write('\nTurno do jogador: '), write(P), nl.

%------------------------------------------------------------------------
%creat Random Start
randomPlayer(P) :- random(1, 3,NrP), NrP == 1,!, P = 'A'. 
randomPlayer(P) :- P = 'B'.

%-----------------------------------------------------------------------
%Start
play :-  board(B), drawBoard(B).

% ---------------------------------MAIN MENU------------------------------------
fines:-
	mainMenu,
	read(X),
	mainMenuOption(X).

mainMenu:-
	nl,nl,
	write('----------------------------------------'),nl,
	write('Fines Game'),nl,nl,
	write('1- Play'), nl,
	write('2- Exit'), nl.

mainMenuOption(X):-
	(
		X = 1 -> play;
		X = 2 -> write('Goodbye!');
		(write('Wrong command!'),nl,fines)
	).

play(B,P) :- getIntro(P), drawBoard(B), selectMov(B,_), P =='A',!,play(B,'B').
play(B,P) :- P = 'A',play(B,P).
start:-  board(B), randomPlayer(P),play(B,P).


test:- board(B),checkArea(NrP,0,0,B,C), drawBoard(C) ,write(NrP).
test2:- board(B),elementAt(B,Elm,12,12),write(Elm). %ElementAt X,Y
test3:- board(B),replace(B,0,6,'C',C),drawBoard(C). % Replace Y,X