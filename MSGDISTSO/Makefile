all:headercliente headergestor verificador gestor cliente

headercliente :cliente_default.h
	gcc cliente_default.h
	
headergestor : gestor_default.h
	gcc gestor_default.h

gestor : gestor.c
	gcc gestor.c -o gestor

verificador : verificador.c
	gcc  verificador.c -o verificador

cliente : cliente.c
	gcc cliente.c -o cliente -l ncurses
