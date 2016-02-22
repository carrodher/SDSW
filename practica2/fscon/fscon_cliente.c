/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "fscon.h"

 int main (int argc, char *argv[])
 {
 	CLIENT *clnt;
 	int *pfd;
 	int *result;
 	LEER_result  *result_leer;	
 	int leer_nbytes;

 	if (argc < 3) 
 	{
 		printf ("Uso: %s server_host nombre_fichero\n", argv[0]);
 		exit (1);
 	}

 	clnt = clnt_create (argv[1], FSCON, CON, "udp");
 	if (clnt == NULL) 
 	{
 		clnt_pcreateerror (argv[1]);
 		exit (1);
 	}
 	else
 	{
	   /* Abre el fichero */
 		pfd = abrir_1(argv[2], clnt);
 		if (pfd == (int *) NULL) 
 		{
 			clnt_perror (clnt, "call failed");
 		}
 		else
 		{
 			printf("El descriptor es: %d\n",*pfd);
 		}

	  	/* Lee del fichero */
 		leer_nbytes=BUF_SIZE;

 		result_leer = leer_1(*pfd, leer_nbytes, clnt);
 		if (result_leer == (LEER_result *) NULL) 
 		{
 			clnt_perror (clnt, "call failed");
 		}
 		else
 		{
			/* imprime los datos leidos */
 			printf("Imprimiendo datos: \n "); 
 			printf("Resultado: %d \n", result_leer->cod_error);
 			if (-1 != result_leer->cod_error)
 			{
 				unsigned int i;
 				printf("\nSe han leido %d octetos: \n", result_leer->datos.BUF_len);
 				for(i=0; i<result_leer->datos.BUF_len; i++)
 				{
 					printf("%c",result_leer->datos.BUF_val[i]);
 				}
 			}
 		}

	   	/* Cierra el fichero previamente abierto */
 		result = cerrar_1(*pfd, clnt);

 		if (result == (int *) NULL) 
 		{
 			clnt_perror (clnt, "call failed");
 		}
 		clnt_destroy (clnt);
 	}
 	exit (0);
 }