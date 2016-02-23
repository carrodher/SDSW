  /*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "fscon.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

LEER_result * leer_1_svc(int fd, int nbytes,  struct svc_req *rqstp)
{
  static LEER_result result;

	/*
	 * insert server code here
	 */
	 
  int oct_leidos = 0;
  static char buf_lectura [BUF_SIZE];

  result.datos.BUF_len = 0;
  result.datos.BUF_val = buf_lectura;

  if(nbytes <= BUF_SIZE)
  {
    if((oct_leidos = read(fd,result.datos.BUF_val, nbytes)) >= 0)
    {
     result.cod_error = 0;
     result.datos.BUF_len = oct_leidos;
    }
    else
    {
     result.cod_error = -1;
     printf("Error en la lectura del fichero\n");
    }
  }
  else
  {
    result.cod_error = -1;
    printf("Error: Se intenta leer mas de lo permitido\n");       
  }

  return &result;
}

int * escribir_1_svc(int fd, int nbytes, BUF buf, struct svc_req *rqstp)
{
	static int result;

	int oct_escritos = 0;
  result = 0;

  if((oct_escritos = write(fd,buf.BUF_val, nbytes)) >= 0)
  {
    result = oct_escritos;
    printf("Escritos %d octetos \n",oct_escritos);
  }
  else
  {
    result = -1;
    printf("Error en la escritura del fichero\n");
  }

  return &result;
}

int * abrir_1_svc(char *nom, struct svc_req *rqstp)
{
	static int result;

	/*
	 * insert server code here
	 */

  if ((result = open(nom, O_RDWR, 0)) == -1)
  {
    printf("Error en apertura de fichero para lectura %s\n", nom);
  }
  else
  {
    printf("Fichero %s abierto \n", nom);
  }

  return &result;
}

int * cerrar_1_svc(int fd, struct svc_req *rqstp)
{
	static int result;

	/*
	 * insert server code here
	 */

   if((result = close(fd)) == -1)
   {
     printf("Error al cerrar el fichero \n ");
   }
   else
   {
     printf("Fichero cerrado \n");
   }

  return &result;
}