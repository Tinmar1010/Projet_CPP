CLASSESM=Classes/Modele/
CLASSESV=Classes/Voiture/
CLASSESO=Classes/Option/
CLASSESP=Classes/Personne/
CLASSESE=Classes/Exception/
CLASSESVE=Classes/Vecteur/
CLASSESIT= Classes/Iterateur/
CLASSESVET=Classes/VecteurTrie/
CLASSESG = Classes/Garage/
CLASSESCO = Classes/Contrat/

OBJSM=Classes/Modele/Modele.o
OBJSV=Classes/Voiture/Voiture.o
OBJSO=Classes/Option/Option.o

OBJSP=Classes/Personne/Personne.o
OBJSI=Classes/Personne/Intervenant.o
OBJSE=Classes/Personne/Employe.o
OBJSC=Classes/Personne/Client.o
OBJSCO = Classes/Contrat/Contrat.o

PERS = $(OBJSP) $(OBJSI) $(OBJSE) $(OBJSC)

OBJSEX=Classes/Exception/Exception.o
OBJSEOE=Classes/Exception/OptionException.o
OBJSEPE=Classes/Exception/PasswordException.o
EXEC= $(OBJSEX) $(OBJSEOE) $(OBJSEPE)

OBJSVE= Classes/Vecteur/Vecteur.o
OBJSIT= Classes/Iterateur/Iterateur.o
OBJSVET= Classes/VecteurTrie/VecteurTrie.o
VEC= $(OBJSVE) $(OBJSIT) 
OBJSG = Classes/Garage/Garage.o


OBJS_QT = main.o  applicgaragewindow.o moc_applicgaragewindow.o

PROGRAMS = ApplicGarage


CO=g++ -g -I $(CLASSESM) -I $(CLASSESV) -I $(CLASSESO) -I $(CLASSESP) -I $(CLASSESE) -I$(CLASSESVE) -I$(CLASSESIT) -I$(CLASSESG) -I $(CLASSESCO)

all:	$(PROGRAMS)

ApplicGarage:	 $(OBJS_QT) $(OBJSM) $(OBJSV) $(OBJSO) $(PERS) $(EXEC) $(VEC) $(OBJSG) $(OBJSCO)
		echo "Creation de ApplicGarage..."
		$(CO) $(OBJSM) $(OBJSV) $(OBJSO) $(PERS) $(EXEC) $(VEC) $(OBJSG) $(OBJS_QT) $(OBJSCO) -Wl,-O1 -o ApplicGarage  -g /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

main.o:		main.cpp
	echo "Creation de main.o"
	$(CO) -c -g -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o main.cpp


applicgaragewindow.o:	applicgaragewindow.cpp applicgaragewindow.h ui_applicgaragewindow.h
		echo "Creation de applicgaragewindow.o"
		$(CO) -c -g -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o applicgaragewindow.o applicgaragewindow.cpp

moc_applicgaragewindow.o:	moc_applicgaragewindow.cpp applicgaragewindow.h
		echo "Creation de moc_applicgaragewindow.o"
		$(CO) -c -g -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_applicgaragewindow.o moc_applicgaragewindow.cpp

	
$(OBJSM):	$(CLASSESM)Modele.cpp
	echo "Creation de Modele.o"
	$(CO) $(CLASSESM)Modele.cpp -c -g -o $(OBJSM)

$(OBJSV):	$(CLASSESV)Voiture.cpp
	echo "Creation de Voiture.o"
	$(CO) $(CLASSESV)Voiture.cpp -c -g -o $(OBJSV)

$(OBJSO):	$(CLASSESO)Option.cpp
	echo "Creation de Option.o"
	$(CO) $(CLASSESO)Option.cpp -c -g -o $(OBJSO)

$(OBJSP):	$(CLASSESP)Personne.cpp
	echo "Creation de Personne.o"
	$(CO) $(CLASSESP)Personne.cpp -c -g -o $(OBJSP)

$(OBJSI):	$(CLASSESP)Intervenant.cpp
	echo "Creation de Intervenant.o"
	$(CO) $(CLASSESP)Intervenant.cpp -c -g -o $(OBJSI)

$(OBJSE):	$(CLASSESP)Employe.cpp
	echo "Creation de Employe.o"
	$(CO) $(CLASSESP)Employe.cpp -c -g -o $(OBJSE)

$(OBJSC):	$(CLASSESP)Client.cpp
	echo "Creation de Client.o"
	$(CO) $(CLASSESP)Client.cpp -c -g -o $(OBJSC)

$(OBJSEX):		$(CLASSESE)Exception.cpp
	echo "Creation de Exception.o"
	$(CO) $(CLASSESE)Exception.cpp -c -g -o $(OBJSEX)

$(OBJSOE):		$(CLASSESE)OptionException.cpp
	echo "Creation de OptionException.o"
	$(CO) $(CLASSESE)OptionException.cpp -c -g -o $(OBJSOE)

$(OBJSPE):		$(CLASSESE)PasswordException.cpp
	echo "Creation de PasswordException.o"
	$(CO) $(CLASSESE)PasswordException.cpp -c -g -o $(OBJSPE)	
	
$(OBJSVE):	$(CLASSESVE)Vecteur.cpp
	echo "Creation de vecteur.o"
	$(CO) $(CLASSESVE)Vecteur.cpp -c -g -o $(OBJSVE)

$(OBJSIT):	$(CLASSESIT)Iterateur.cpp
	echo "Creation d'iterateur.o"
	$(CO) $(CLASSESIT)Iterateur.cpp -c -g -o $(OBJSIT)

$(OBJSVET):	$(CLASSESVET)VecteurTrie.cpp
	echo "Creation de vecteurTrie.o"
	$(CO) $(CLASSESVET)VecteurTrie.cpp -c -g -o $(OBJSVET)

$(OBJSG): $(CLASSESG)Garage.cpp
	echo "Creation de Garage.o"
	$(CO) $(CLASSESG)Garage.cpp -c -g -o $(OBJSG)

$(OBJSCO): $(CLASSESCO)Contrat.cpp
	echo "Creation de Contrat.cpp"
	$(CO) $(CLASSESCO)Contrat.cpp -c -g -o $(OBJSCO)
	

clean:
	rm $(CLASSESM)*.o $(CLASSESV)*.o $(CLASSESO)*.o $(CLASSESP)*.o $(CLASSESE)*.o $(CLASSESVE)*.o $(CLASSESIT)*.o $(CLASSESG)*.o $(OBJS_QT) $(OBJSCO)

clobber:	clean
	@rm -f tags $(PROGRAMS) *~ *.log