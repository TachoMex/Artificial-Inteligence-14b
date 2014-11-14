componente(x1).
componente(x2).
componente(a1).
componente(a2).
componente(o1).
componente(sumador).

entrada(1,sumador).
entrada(2,sumador).
entrada(3,sumador).
entrada(1,x1).
entrada(2,x1).
entrada(1,x2).
entrada(2,x2).
entrada(1,a1).
entrada(2,a1).
entrada(1,a2).
entrada(2,a2).
entrada(1,o1).
entrada(2,o2).

salida(1,sumador).
salida(2,sumador).
salida(1,x1).
salida(1,x2).
salida(1,a1).
salida(1,a2).
salida(1,o1).

conectados(entrada(1,sumador),entrada(2,a1)).
conectados(entrada(1,sumador),entrada(1,x1)).
conectados(entrada(2,sumador),entrada(2,x1)).
conectados(entrada(2,sumador),entrada(1,a1)).
conectados(entrada(3,sumador),entrada(2,x2)).
conectados(entrada(3,sumador),entrada(2,a2)).
conectados(salida(1,x1),entrada(1,x2)).
conectados(salida(1,x1),entrada(1,a2)).
conectados(salida(1,a1),entrada(2,o1)).
conectados(salida(1,a2),entrada(1,o1)).
conectados(salida(1,x2),salida(1,sumador)).
conectados(salida(1,o1),salida(2,sumador)).

compuertaAnd(a1).
compuertaAnd(a2).
compuertaOr(o1).
compuertaXor(x1).
compuertaXor(x2).

valor(Y,V2):-conectados(X,Y),valor(X,V2).

valor(salida(1,X),1):- 
	compuertaAnd(X), 
	valor(entrada(1,X),1), 
	valor(entrada(2,X),1).

valor(salida(1,X),0):- 
	compuertaAnd(X), 
	valor(entrada(1,X),0). 

valor(salida(1,X),0):- 
	compuertaAnd(X), 
	valor(entrada(2,X),0). 

valor(salida(1,X),0):- 
	compuertaOr(X), 
	valor(entrada(1,X),0), 
	valor(entrada(2,X),0).

valor(salida(1,X),1):- 
	compuertaOr(X), 
	valor(entrada(1,X),1). 

valor(salida(1,X),1):- 
	compuertaOr(X), 
	valor(entrada(2,X),1). 

valor(salida(1,X),1):- 
	compuertaXor(X), 
	valor(entrada(1,X),I1), 
	valor(entrada(2,X),I2),
	I1\=I2.

valor(salida(1,X),0):-
	compuertaXor(X), 
	valor(entrada(1,X),I1), 
	valor(entrada(2,X),I2),
	I1=I2.

valor(entrada(1,sumador),1).
valor(entrada(2,sumador),1).
valor(entrada(3,sumador),1).