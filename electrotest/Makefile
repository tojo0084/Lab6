# Denna makefile förutsätter att man har installerat "/usr/local/lib/libcomponent.so"
# vilket man kan göra med kommandon nedan (om man utgår från projekt-rooten dvs katalogen som innehåller katalogerna libpower , libcomponent, libresistance)
# cd libcomponent
# make all
# make install
# ls -l /usr/local/lib/
#  	(kontrollera att libcomponent.so finns med i katalogen som listades ovan)
# cd ..
# cd electrotest
# make all
# ./electrotest

all:
	gcc -o electrotest main/electrotest.c -L. -lcomponent -lm -Wl,-rpath,/usr/local/lib/libcomponent.so
