all:headerstrucs headerdefines gestor cliente

headerstrucs :structs.h
	gcc structs.h
	
headerdefines : defines.h
	gcc defines.h

gestor : gestor.c
	gcc gestor.c -o gestor

verificador : verificador.c
	gcc  verificador.c -o verificador
cliente : cliente.c
	gcc cliente.c -o cliente -l ncurses
