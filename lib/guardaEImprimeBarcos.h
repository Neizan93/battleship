/*
	Esta librería permite al programa principal la solicitud/calculo de las coordenadas de cada barco y su almacenamiento en las matrices correspondientes,
	de mismo modo que se imprimen los resultados si es necesario.

	Importante: La librería necesita de ciertas constantes para funcionar por lo que deberá de estar inicializada después de estas.
*/


// Función que rellena todos los componentes de las cuatro matrices con 'vacio':
void rellTablero( char tabJug[tamTab][tamTab][2], char tabMaq[tamTab][tamTab][2] )
{
	// Precondición: Se han de recibir cuatro matrices con basura de tamaño: 'tamTab'*'tamTabSe'
	// Poscondición: Se modifican sus componentes y se guarda en todos ellos 'vacio'

	int i, j, k;

	for( i=0; i < tamTab; i++ )
	{
		for( j=0; j < tamTab; j++ )
		{
			for( k=0; k < 2; k++ )
			{
				tabJug[i][j][k]	= vacio;
				tabMaq[i][j][k]	= vacio;
			};

		};
	};

};


// Función que imprime el tablero con la información que corresponda:
void impTablero( char tablero[tamTab][tamTab][2] )
{
	// Precondición: Se recibe una matriz de tamaño: 'tamTab'*'tamTab' con datos.
	// Poscondición: Se imprime por pantalla su contenido.

	system("cls"); //Descomentar para ejecutar desde el terminal de ubuntu.

	char letCol[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i, j;


	// Se imprime los indicadores de columna:
	printf( "\n    " );
	for( i=0; i < tamTab; i++ )
	{
		printf( " %c", letCol[i] );
	};
	printf( "\n    " );

	for( i=0; i < tamTab; i++ )
	{
		printf( "__" );
	};
	printf( "\n" );


	// Se imprimen los indicadores de fila y la información de cada componente:
	for( i=0; i < tamTab; i++ )
	{
		// Se añade un espacio de más cuando el indicador de fila es menor de 10:
		if( i<10 )
		{
			printf( " %i |", i );
		}
		else if( i<100 )
		{
			printf( "%i |", i );
		};

		for( j=0; j < tamTab; j++ )
		{
			printf( " %c", tablero[i][j][0] );
		};

		printf( "\n" );
	};

	printf( "\n" );
};


// Función empleada por impBarco(), para separar las coordenadas de un string.
int validaYSeparaFilyCol( char tablero[tamTab][tamTab][2], char coor[4], int *fil, int *col, int tipoJugador )
{
	/*
		Precondición:
						Se ha de recibir una matriz de tamTab*tamTab*2
						Se ha de recibir una cadena terminada en '\0'
						Se obtiene por referencia las posiciones donde se guardaran dos enteros.
						Por ultimo tendremos que recibir un entero booleano con valores de 0 ó 1

		Poscondición:
						En caso de realizarse todo correctamente, se guardan las coordenadas desglosadas en las celdas indicadas por referencia y se devuelve un 1/true
						En caso contrario, se devuelve un 0/false y se muestra un error por pantalla solo para el usuario, para la maquina no.
*/


	int longCoor = strlen(coor);
	int correcto = 1;

	// A partir de la coordenada pueden darse cinco situaciones, que la coordenada sea: numLet, letNum, numNumLet, letNumNum o en cualquier otro caso: error.

	// Si la longitud de la cadena es de 2, y el componente 0 es numero y el 1 es letra...
	if( longCoor == 2   &&   coor[0] >= 48 && coor[0] <= 48+tamTab-1   &&   coor[1] >= 97 && coor[1] <= 97+tamTab-1 )
	{
		// Tanto la fila como la columna se guardan como enteros, a la fila se le restan -48 y nos da un entero, a la columna se le resta -49 para que nos de el "número en ASCII" y luego -48 para que nos de el entero.
		*fil = coor[0]-48;
		*col = coor[1]-49-48;

		// Si en la coordenada elegida hay un barco o parte de el, se imprime un error y correcto se cambia a false.
		if( tablero[*fil][*col][0] != vacio  &&  tablero[*fil][*col][0] != fin )
		{
			if( tipoJugador == 0 ) printf( "Esa coordenada ya esta en uso, elija otra: " );
			correcto = 0;
		};

	}	// Si la longitud es de 2, y el componente 0 es letra y el 1 numero...
	else if( longCoor == 2   &&   coor[1] >= 48 && coor[1] <= 48+tamTab-1   &&   coor[0] >= 97 && coor[0] <= 97+tamTab-1 )
	{
		*fil = coor[1]-48;
		*col = coor[0]-49-48;

		if( tablero[*fil][*col][0] != vacio  &&  tablero[*fil][*col][0] != fin )
		{
			if( tipoJugador == 0 ) printf( "Esa coordenada ya esta en uso, elija otra: " );
			correcto = 0;
		};

	}	// Si la longitud es de 3, y el componente 0y1 son números y el 2 es letra...
	else if( longCoor == 3   &&   coor[0] >= 48 && coor[0] <= 48+tamTab-1   &&   coor[1] >= 48 && coor[1] <= 48+tamTab-1   &&   coor[2] >= 97 && coor[2] <= 97+tamTab-1 )
	{
		*fil = ((coor[0]-48)*10) + (coor[1]-48);
		*col = coor[2]-49-48;

		if( tablero[*fil][*col][0] != vacio  &&  tablero[*fil][*col][0] != fin )
		{
			if( tipoJugador == 0 ) printf( "Esa coordenada ya esta en uso, elija otra: " );
			correcto = 0;
		};

	}	// Si la longitud es de 3, y el componente 0 es letra y el 1y2 números...
	else if( longCoor == 3   &&   coor[2] >= 48 && coor[2] <= 48+tamTab-1   &&   coor[1] >= 48 && coor[1] <= 48+tamTab-1   &&   coor[0] >= 97 && coor[0] <= 97+tamTab-1 )
	{
		*fil = ((coor[1]-48)*10) + (coor[2]-48);
		*col = coor[0]-49-48;

		if( tablero[*fil][*col][0] != vacio  &&  tablero[*fil][*col][0] != fin )
		{
			if( tipoJugador == 0 ) printf( "Esa coordenada ya esta en uso, elija otra: " );
			correcto = 0;
		};
	}
	else // En cualquier otra situación 'correcto' será false:
	{
		if( tipoJugador == 0 )	// Si el error lo ha generado el jugador...
		{
			impTablero(tablero);
			printf( "Indique correctamente las coordenadas:\n *Use solo las coordenadas marcadas en el tablero\n *Un numero para marcar la fila y una letra minuscula para marcar la columna. Ejemplo: 2c o c2.\n\nIntentelo de nuevo: " );
		};
		correcto = 0;
	};

	return correcto;

};


// Función empleada por impBarco(), para imprimir las posibles posiciones del barco.
void impMovPosBarco( char tablero[tamTab][tamTab][2], int fil, int col, int longBar )
{
	/*
		Precondición:
						Se ha de recibir una matriz de tamaño: 'tamTab'*'tamTab'
						Después dos enteros cuyo valor máximo sera 'tamTab'-1
						Y por ultimo un tercer entero que indica la longitud del barco, esta sera tan grande como la longitud del barco mas grande que introduzcamos en la Constante.

		Poscondición:	Se guarda en los componentes correspondientes todas las posiciones que puede tomar el final del barco, además de imprimir la matriz por pantalla.
	*/


	int huecosLibres = 1; // Se contabiliza desde el principio la coordenada de inicio.
	int i, j;

	// Indica la dirección a comprobar: 0,1,2,3 = Arriba, derecha, abajo, izquierda.
	for( i=0; i < 4; i++ )
	{
		// Se mira el número 'longBar' de componentes hacia la dirección especificada.
		for( j=1; j < longBar; j++ )
		{
			// En el caso de la comprobación hacia arriba (el resto son parecidas):
				// Si... i es 0 entonces comprobar si se puede colocar el barco hacia arriba
				//  y...  el número de filas es mayor o igual al espacio que ocupa el barco-1 (menos uno por la cabeza del barco que ya esta colocada)
				//  y...  cada casilla necesaria tiene 'vacio', entonces, huecos libres ++

			if( i==0   &&   fil >= longBar-1   &&   tablero[fil-j][col][0] == vacio )
			{
				huecosLibres++;
			}
			else if( i==1   &&   longBar <= tamTab-col   &&   tablero[fil][col+j][0] == vacio )
			{
				huecosLibres++;
			}
			else if( i==2   &&   longBar <= tamTab-fil   &&   tablero[fil+j][col][0] == vacio )
			{
				huecosLibres++;
			}
			else if( i==3   &&   col >= longBar-1   &&   tablero[fil][col-j][0] == vacio )
			{
				huecosLibres++;
			};
		}; //fin for j


		// En el caso de que los huecos libres sean igual al numero de huecos que hace falta, entonces se guarda en ese componente un 'fin'
		if( i == 0  &&  huecosLibres == longBar )
		{
			tablero[fil-(longBar-1)][col][0] = fin;
		}
		else if( i == 1  &&  huecosLibres == longBar )
		{
			tablero[fil][col+longBar-1][0] = fin;
		}
		else if( i == 2  &&  huecosLibres == longBar )
		{
			tablero[fil+longBar-1][col][0] = fin;
		}
		else if( i == 3  &&  huecosLibres == longBar )
		{
			tablero[fil][col-(longBar-1)][0] = fin;
		};

		huecosLibres = 1; // Se resetea a 1 el contador de huecos libres.

	}; // fin for i

};


// Función empleada por impFinBarco(), que valida si la posición final es o no 'fin'
int hayFinMarcado( char tablero[tamTab][tamTab][2], int filFin, int colFin )
{
	/*
	 	Precondición:
	 					Se ha de recibir una matriz de tamaño: 'tamTab'*'tamTab'
	 					Y dos enteros no mayores que 'tamTab'

		Poscondición:	Se devolverá un 1/true o un 0/false según corresponda.
	 */


	int esFin = 1;

	// Si en la casilla elegida de la matriz hay cualquier cosa que no sea un 'fin' no se pasara la validación.
	if( tablero[filFin][colFin][0] != fin )
	{
		esFin = 0;
	};

	return esFin;
};


// Función empleada por impFinBarco() que devuelve la coordenada menor (mas cerca del cero)
int devCoorMenor( int coorUno, int coorDos )
{
	/*
		Precondición:	Se reciben dos enteros no mayores que 'tamTab'
		Poscondición:	Se devuelve el numero más pequeño.
	*/


	int menor;

	if( coorUno < coorDos )
		menor = coorUno;
	else
		menor = coorDos;

	return menor;
};


// Función empleada por impBarco(), que imprime el resto del barco según elija el jugador/maquina.
void impFinBarco( char tablero[tamTab][tamTab][2], int fil, int col, int longBar, char simbBarco, int tipoJugador )
{
	/*
		Precondición:
						Se ha de recibir una matriz de tamaño: 'tamTab'*'tamTab'
						Dos enteros no mayores de 'tamTab'
						Un entero que marca la longitud del barco
						Un carácter que indica con que símbolo se ha de imprimir ese barco
						Y un ultimo entero que indica quien llamo a la función, si el bucle del jugador o el de la maquina.
						También se necesita que la función main haya generado números aleatorios para poderlos usar ahora.

		Poscondición:	Se guarda en todos los componentes que ocupa ese barco el simbBarco recibido.
	*/


	char coor[4];
	int coorMenor;
	int filFin, colFin;
	int i;
	int dirFinBarMaq;
	int maqGuaCoor = 0;


	// Si es el jugador quien esta colocando los barcos:
	if( tipoJugador == 0 )
	{
		// Se solicita la coordenada de fin, la cual ha de pasar la validación, en concreto ha de ser una coordenada correcta y ha de estar obligatoriamente en una casilla que contenga un carácter de 'fin'
		printf( "Elija entre una de las coordenadas de fin marcadas con \'%c\'\n", fin );
		do
		{
			scanf( "%s", coor );
		} while( validaYSeparaFilyCol( tablero, coor, &filFin, &colFin, tipoJugador ) != 1  ||  hayFinMarcado( tablero, filFin, colFin ) != 1 );

	}
	else // En caso contrario, la maquina genera sus coordenadas:
	{
		do
		{
			// Se genera un numero aleatorio de 0 a 3:
			dirFinBarMaq = rand()%4;

			if( dirFinBarMaq == 0  &&  hayFinMarcado( tablero, fil-(longBar-1), col ) == 1 )	// Arriba
			{
				filFin = fil-(longBar-1);
				colFin = col;
				maqGuaCoor = 1;
			}
			else if( dirFinBarMaq == 1  &&  hayFinMarcado( tablero, fil, col+(longBar-1) ) == 1 ) // Derecha
			{
				filFin = fil;
				colFin = col+(longBar-1);
				maqGuaCoor = 1;
			}
			else if( dirFinBarMaq == 2  &&  hayFinMarcado( tablero, fil+(longBar-1), col ) == 1 ) // Abajo
			{
				filFin = fil+(longBar-1);
				colFin = col;
				maqGuaCoor = 1;
			}
			else if( dirFinBarMaq == 3   &&  hayFinMarcado( tablero, fil, col-(longBar-1) ) == 1 ) // Izquierda
			{
				filFin = fil;
				colFin = col-(longBar-1);
				maqGuaCoor = 1;
			};
		} while( maqGuaCoor != 1 );	// Mientras no se pueda colocar el barco en una de las posibles posiciones repetir el proceso incluido el calculo de un nuevo numero aleatorio.


	};


	// Se guarda el final del barco:
	tablero[filFin][colFin][0] = simbBarco;


	// Hasta ahora se tiene guardado el comienzo y el final del barco, ahora se guarda el resto (solo con barcos mayores de dos casillas)
	for( i=1; i < longBar-1; i++ )
	{
		if( fil == filFin )	// Si la fila de inicio del barco y la de fin son iguales, el barco estará orientado horizontalmente:
		{
			coorMenor = devCoorMenor( col, colFin );	// Se calcula la coordenada menor
			tablero[fil][coorMenor+i][0] = simbBarco;		// Se guarda el carácter 'simbBarco' que corresponda en los huecos que hay en medio del inicio y el final del barco
		}
		else if( col == colFin )
		{
			coorMenor = devCoorMenor( fil, filFin );
			tablero[coorMenor+i][col][0] = simbBarco;
		};
	};

};


// Función empleada por impBarco(), que borra las posibles soluciones.
void borrMovPosBarco( char tablero[tamTab][tamTab][2] )
{
	// Precondición: Se ha de recibir una matriz de tamaño: 'tamTab'*'tamTab'
	// Poscondición: Se sustituyen todos los caracteres 'fin' por 'vacio'

	int i, j;

	for( i=0; i < tamTab; i++ )
	{
		for( j=0; j < tamTab; j++ )
		{
			if( tablero[i][j][0] == fin )
			{
				tablero[i][j][0] = vacio;
			};

		};
	};
};


// Función que imprime el barco elegido:
void impBarco( char tabJug[tamTab][tamTab][2], char tabMaq[tamTab][tamTab][2], int longBar, int simAUsar, int tipoJugador )
{
	/*
		Precondición:
						Se han de recibir dos matrices de tamaño: 'tamTab'*'tamTab'
						Un entero que marca la longitud del barco a guardar/imprimir y que no sera mayor que el tamaño del barco más grande.
						Un entero que sera igual al numero de barco que se este colocando, que ira de 0 hasta 'barcos'
						Y un entero booleano con 0 ó 1 que marca si la función la llamo el jugador o la maquina.
						También se necesita que la función main haya generado números aleatorios para poderlos usar ahora.

		Poscondición:	Se almacena en los componentes correspondientes el barco escogido, además de imprimir por pantalla, solo con el usuario, su tablero.
	*/


	char coor[4];
	char simbolosBarcos[10] = "123456789";
	int fil, col;


	// Si es el usuario quien esta colocando sus barcos, solicitar las coordenadas:
	if( tipoJugador == 0 )
	{
		// Se imprime el tablero:
		impTablero(tabJug);

		// Se solicita la coordenada de inicio
		printf( "Indique la coordenada de inicio del barco, ejemplo: 2c\n" );
		do
		{
			scanf( "%s", coor );
		} while( validaYSeparaFilyCol( tabJug, coor, &fil, &col, tipoJugador ) != 1 );

		tabJug[fil][col][0] = simbolosBarcos[simAUsar];										// Se introduce en el tablero el inicio del barco:
		impMovPosBarco( tabJug, fil, col, longBar );										// Se imprimen las posibles posiciones que el barco puede ocupar según su tamaño y de si entra en el tablero o no:
		impTablero(tabJug);																	// Se imprime el tablero:
		impFinBarco( tabJug, fil, col, longBar, simbolosBarcos[simAUsar], tipoJugador );	// Se imprime el final y resto del barco:
		borrMovPosBarco( tabJug );															// Se borran las posiciones no usadas:

	}
	else // En caso contrario, la maquina genera sus coordenadas:
	{
		do
		{
			// Se generan las coordenadas de forma aleatoria, si estas estuviesen elegidas se reelegirán otras hasta conseguir unas validas.
			// NOTA: Por alguna razón estraña, cuando el tablero es más grande de 10, y la función de números aleatorios genera un numero grande, este se guarda correctamente, aun cuando solo se le esta dejando un componente para guardarlo... no debería de funcionar pero lo hace correctamente...
			coor[0] = (rand()%tamTab)+48;		// Un numero del 0 al tamTab al cual se le suman 48 para obtener el numero ASCII correspondiente.
			coor[1] = (rand()%tamTab)+48+49;	// Una numero del 0 a tamTab, que posteriormente se le suman 48 para tener el numero en ASCII y +49 para el correspondiente en letra.
			coor[2] = '\0';						// Fin de la cadena

		} while( validaYSeparaFilyCol( tabMaq, coor, &fil, &col, tipoJugador ) != 1 );

		tabMaq[fil][col][0] = simbolosBarcos[simAUsar];
		impMovPosBarco( tabMaq, fil, col, longBar );
		impFinBarco( tabMaq, fil, col, longBar, simbolosBarcos[simAUsar], tipoJugador );
		borrMovPosBarco( tabMaq );

	};

};
