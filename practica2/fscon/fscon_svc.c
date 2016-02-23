/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "fscon.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static LEER_result *
_leer_1 (leer_1_argument *argp, struct svc_req *rqstp)
{
	return (leer_1_svc(argp->fd, argp->nbytes, rqstp));
}

static int *
_escribir_1 (escribir_1_argument *argp, struct svc_req *rqstp)
{
	return (escribir_1_svc(argp->fd, argp->nbytes, argp->buf, rqstp));
}

static int *
_abrir_1 (char * *argp, struct svc_req *rqstp)
{
	return (abrir_1_svc(*argp, rqstp));
}

static int *
_cerrar_1 (int  *argp, struct svc_req *rqstp)
{
	return (cerrar_1_svc(*argp, rqstp));
}

static void
fscon_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		leer_1_argument leer_1_arg;
		escribir_1_argument escribir_1_arg;
		char *abrir_1_arg;
		int cerrar_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case leer:
		_xdr_argument = (xdrproc_t) xdr_leer_1_argument;
		_xdr_result = (xdrproc_t) xdr_LEER_result;
		local = (char *(*)(char *, struct svc_req *)) _leer_1;
		break;

	case escribir:
		_xdr_argument = (xdrproc_t) xdr_escribir_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _escribir_1;
		break;

	case abrir:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _abrir_1;
		break;

	case cerrar:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _cerrar_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (FSCON, CON);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, FSCON, CON, fscon_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (FSCON, CON, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, FSCON, CON, fscon_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (FSCON, CON, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
