all: verificador gestor cliente

gestor : gestor.c
	gcc gestor.c -o gestor -lpthread
verificador : verificador.c
	gcc  verificador.c -o verificador
cliente : cliente.c
	gcc cliente.c -o cliente -l ncurses  -lpthread
clean: 
	rm -f gestor cliente verificador
