#Ubuntu Linux Container
FROM ubuntu:14.04

#Installation der wichtigsten Ubuntu Komponenten
RUN apt-get update -y

#Installation von g++ zum kompilieren -y ist mal wieder zum Bestätigen von anfragen
RUN apt-get install -y g++

#Installieren von Git, das -y sagt aus das er die Frage ob er es installieren soll automatisch mit ja bestätigt
RUN apt-get install -y git

#Installieren der ganzen SDL sachen
RUN apt-get install -y libsdl2-image-dev && apt-get install -y libsdl2-dev

#Zur Ausführung von der Waermeleitungsgleichung, muss ich danach zuerst das repo ziehen dafür brauche ich evtl. den Token (lange Zahl da vor dem Doppelpunkt. Hinten kommt die Installationslokation
#RUN git clone -b docker https://4367027f94c72935b64cbd45e846e765899fbc2e:marcelmaxjoedicke@github.com/MarcelJoedicke/Hallo.git /myapp/
RUN git clone https://github.com/MarcelJoedicke/Waermeleitungsgleichung.git

#Wechseln in den Hallo Ordner, geht nur über Workdir nicht über cd!!!
WORKDIR /Waermeleitungsgleichung/

#anzeigen das man im richtigen Arbeitsordner ist
RUN ls

#als nächstes müsste ich kompilieren, dafür erstelle ich die hallo.o Datei aus der hallo.cpp Datei und Kompiliere Sie zu einen ausführbaren Programm
#RUN g++ hello.cpp -o Hallo
#RUN g++ -std=gnu++11 hello.cpp
RUN make all

#Dann versuche ich die Datei auszuführen
RUN ./Waermeblanko
