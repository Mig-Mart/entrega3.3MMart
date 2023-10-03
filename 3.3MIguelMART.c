#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	int ID; 
	char nombre [30]; 
	char correo [30]; 
	char contra [30];
	char IDs [5];
	char ID_PERSs [5];
	char ID_PARTIDAs [5];
	char scoress [5];
	int ID_PERS;
	int score;
	int ID_PARTIDA;
	int x; // num de usuarios a a￱adir
	char consulta [80];
	conn = mysql_init(NULL);
	if (conn==NULL) 
	{		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "bd",0, NULL, 0);
	if (conn==NULL) 
	{
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//pedimos al usuario el valor de x:
	printf ("Usuarios por poner:\n");
	scanf ("%d", &x);
	//Introduciremos x usuarios, 
	for (int i=0; i<x; i++) 
	{
		printf ("Da ID(int), nombre(char), correo(char), contra(char), ID de personaje(int), puntos(int) e ID de Partida(int) separado por espacio :\n");
		err = scanf ("%d %s %s %s %d %d %d", &ID, nombre, correo, contra, &ID_PERS, &score, &ID_PARTIDA);
		if (err!=7) 
		{
			printf ("Error al introducir datos \n");
			exit (1);
		}
			// Ahora construimos el string con el comando SQL
 
		strcpy (consulta, "INSERT INTO USUARIOS VALUES (");
		//ponemos ID etc 
		sprintf(IDs, "%d", ID); //int to string
		strcat (consulta, IDs); 
		strcat (consulta, ",'");
		strcat (consulta, nombre); 
		strcat (consulta, "','");
		strcat (consulta, correo);
		strcat (consulta, "','");
		strcat (consulta, contra);
		strcat (consulta, "',");
		sprintf(ID_PERSs, "%d", ID_PERS); //int to string
		strcat(consulta, ID_PERSs); // debe existir este foreign key!
		strcat (consulta, ",");
		sprintf(scoress, "%d", score); //int to string
		strcat(consulta, scoress);
		strcat (consulta, ",");
		sprintf(ID_PARTIDAs, "%d", ID_PARTIDA); //int to string debe existir este foreign key!
		strcat(consulta, ID_PARTIDAs);
		strcat (consulta, ");");
		printf("consulta = %s\n", consulta);
		// Ahora ya podemos realizar la insercion 
		err = mysql_query(conn, consulta);
		if (err!=0) {
			printf ("Error al introducir datos la base %u %s\n", 
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
	}
	// cerrar la conexion con el servidor MYSQL 
	mysql_close (conn);
	exit(0);
}