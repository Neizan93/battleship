/*
	Hundir_la_flota

	Desarrolla un juego de �hundir la flota� para jugar contra el ordenador. El ordenador colocar�
	inicialmente sus barcos en su tablero sin mostrarlos por pantalla para que el usuario no conozca su
	ubicaci�n. Le pedir� al usuario que introduzca informaci�n sobre la ubicaci�n de sus barcos (los del
	usuario). Ambos jugar�n con el mismo n�mero de barcos y de las mismas dimensiones. Y se proceder�
	a jugar por turnos, repitiendo disparo si se acierta y perdiendo el turno si el proyectil cae en una casilla
	en la que haya �agua�. Tras cada jugada, se mostrar� informaci�n al usuario sobre la situaci�n de su
	tablero, y sobre la situaci�n que conoce del tablero del ordenador (es decir, s�lo los disparos que ha
	hecho, sobre qu� posici�n y sus aciertos y errores). La estrategia a utilizar por el ordenador para ganar,
	se deja en manos de cada desarrollador y se puede hacer tan sofisticada como se desee. No est�
	permitido que el ordenador utilice informaci�n sobre la situaci�n de los barcos del adversario, se supone
	que el juego es limpio.
*/



// Constantes modificables:
	#define tamTab	10						// Mismo ancho que alto. M�nimo obligatorio=4, M�nimo aconsejable=7, M�ximo obligatorio=26 (lo marca las letras del abecedario)

	#define	tocado	'X'						// Diferentes marcas a representar en los tableros.
	#define hundido	'#'
	#define agua 	'~'
	#define fin 	'*'
	#define vacio 	' '

	#define BARPEQ  2						// Numero de barcos de cada tama�o. Maximo 9 en total.
	#define BARMED  2
	#define BARGRA  1

	#define LONGBARPEQ 2					// La longitud de cada tama�o de barco.
	#define LONGBARMED 3
	#define LONGBARGRA 4


// Librerias:
	#include <stdio.h>

	#include <stdlib.h>						// Librer�as requeridas para el calculo de n�meros aleatorios.
	#include <time.h>

	#include <string.h>

											// Librer�a propia que contiene todas las funciones necesarias para que el jugador y la maquina coloquen...
	#include "lib/guardaEImprimeBarcos.h"	// ...sus barcos en el tablero.
	#include "lib/guardaEImprimeBombas.h"	// ...sus bombas.



// Funci�n principal:
main()
{
	//Se genera un conjunto de n�meros aleatorios:
	srand((unsigned int)time(NULL));


	// Se crean dos tableros de tres dimensiones, en el primer nivel se guardan los barcos de cada jugador, y en el segundo las bombas que tocaron barco o agua del contrario:
	char tabJug[tamTab][tamTab][2];
	char tabMaq[tamTab][tamTab][2];


	// Se inicializan las variables, algunas de ellas reciben el valor de las Constantes de la cabecera:
	int  barPeq = BARPEQ, longBarPeq = LONGBARPEQ;
	int  barMed = BARMED, longBarMed = LONGBARMED;
	int  barGra = BARGRA, longBarGra = LONGBARGRA;
	int  barcos = barPeq + barMed + barGra;
	int trozosBarco = (barPeq*longBarPeq)+(barMed*longBarMed)+(barGra*longBarGra);
	char tipoBar;
	int i;

	int leTocaA = rand()%2; // Variable con valor generado aleatoriamente cuyos valores seran: 0=jugador, 1=maquina. E indicaran de quien es el turno.



	// Se rellenan todos los componentes de las cuatro matrices con 'vacio':
	rellTablero( tabJug, tabMaq );


	// La Maquina coloca todos sus barcos:
	for( i=0; i < barcos; i++ )
	{
		// Se van eligiendo los barcos de mayor a menor medida:
		if( barGra != 0 )
		{
			tipoBar = 'g';
			impBarco( tabJug, tabMaq, longBarGra, i, 1 ); // El ultimo par�metro, el 1, indica que la introducci�n de barcos es por parte de la maquina y por consiguiente que tablero deber� de usar.
			barGra--;
		}
		else if( barMed != 0 )
		{
			tipoBar = 'm';
			impBarco( tabJug, tabMaq, longBarMed, i, 1 );
			barMed--;
		}
		else if( barPeq != 0 )
		{
			tipoBar = 'p';
			impBarco( tabJug, tabMaq, longBarPeq, i, 1 );
			barPeq--;
		};
	};


	//Se resetean los barcos con los valores de las Constantes para que el jugador pueda colocar sus barcos ahora:
	barPeq = BARPEQ; barMed = BARMED; barGra = BARGRA;


	// El jugador introduce todos sus barcos:
	for( i=0; i < barcos; i++ )
	{
		// Se imprime el tablero:
		impTablero(tabJug);

		// Se solicita el barco a colocar:
		printf( "Dispone de %i barcos: %i peque�os, %i medianos y %i grandes.\n", barPeq+barMed+barGra, barPeq, barMed, barGra );
		printf( "Indique el barco que quiere colocar: p / m / g\n" );
		do
		{
			scanf( "%c", &tipoBar );
		} while( tipoBar != 'p' && tipoBar != 'm' && tipoBar != 'g' );


		// Si hay disponibles barcos de ese tama�o, se env�an a la funci�n que los imprime:
		if( tipoBar == 'p' && barPeq != 0 )
		{
			impBarco( tabJug, tabMaq, longBarPeq, i, 0); // El ultimo par�metro, el 0, indica que la introducci�n de barcos es por parte del jugador y por consiguiente que tablero deber� de usar.
			barPeq--;
		}
		else if( tipoBar == 'm' && barMed != 0 )
		{
			impBarco( tabJug, tabMaq, longBarMed, i, 0);
			barMed--;
		}
		else if( tipoBar == 'g' && barGra != 0 )
		{
			impBarco( tabJug, tabMaq, longBarGra, i, 0);
			barGra--;
		}
		else
		{
			printf( "No dispone de mas barcos de ese tamanio, elija otro.\n" );
			i--; //Dado que hemos elegido un tama�o de barco que no estaba disponible, para que no dejemos de introducir ninguno se resta 1 al bucle.
		};
	};

	system("cls"); //Descomentar para ejecutar desde el terminal de ubuntu.

	// Ahora hay que programar la guerra!
	// En el momento de que alguno de los jugadores tenga todos los barcos hunidos por completo se termina el juego:
	do
	{
		impBomba( tabJug, tabMaq, trozosBarco, &leTocaA );
	} while( cuenTrozHund(tabJug) != trozosBarco   &&   cuenTrozHund(tabMaq) != trozosBarco );

	printf( "\n\n" );
	impTabJudYTamBomJug( tabJug, tabMaq );
	//impTabJudYTamBomJugTest( tabJug, tabMaq ); // Esta funci�n es de depuraci�n, descomentar para testear el programa.

	// Quien tenga mas trozos hundidos pierde:
	if( cuenTrozHund(tabJug) < cuenTrozHund(tabMaq) )	printf( "\n   Ganaste!\n\n" );
	else												printf( "\n   Gano la maquina\n\n" );

}; // Fin del main
