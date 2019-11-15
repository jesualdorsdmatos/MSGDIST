all: verificador gestor cliente

gestor : gestor.c
	gcc gestor.c -o gestor
verificador : verificador.c
	gcc  verificador.c -o verificador
cliente : cliente.c
	gcc cliente.c -o cliente -l ncurses
clean: 
	rm -f gestor cliente verificador
