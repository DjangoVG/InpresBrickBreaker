.SILENT:

GRILLESDL=GrilleSDL
RESSOURCES=Ressources
ECRAN=Ecran

CC = g++ -DSUN -I$(ECRAN) -I$(GRILLESDL) -I$(RESSOURCES) -I /opt/guengel/include/SDL
OBJS = $(GRILLESDL)/GrilleSDL.o $(RESSOURCES)/Ressources.o $(ECRAN)/Ecran.o
PROGRAMS = CasseBriques

ALL: $(PROGRAMS)

CasseBriques:	CasseBriques.cpp $(OBJS)
	echo Creation de CasseBriques...
	$(CC) CasseBriques.cpp -o CasseBriques $(OBJS) -lrt -lpthread -lSDL

$(GRILLESDL)/GrilleSDL.o:	$(GRILLESDL)/GrilleSDL.c $(GRILLESDL)/GrilleSDL.h
		echo Creation de GrilleSDL.o ...
		$(CC) -c $(GRILLESDL)/GrilleSDL.c
		mv GrilleSDL.o $(GRILLESDL)

$(RESSOURCES)/Ressources.o:	$(RESSOURCES)/Ressources.c $(RESSOURCES)/Ressources.h
		echo Creation de Ressources.o ...
		$(CC) -c $(RESSOURCES)/Ressources.c
		mv Ressources.o $(RESSOURCES)

$(ECRAN)/Ecran.o:	$(ECRAN)/Ecran.c $(ECRAN)/Ecran.h
		$(CC) $(ECRAN)/Ecran.c -c
		mv Ecran.o $(ECRAN)/Ecran.o

clean:
	@rm -f $(OBJS) core

clobber:	clean
	@rm -f tags $(PROGRAMS)
