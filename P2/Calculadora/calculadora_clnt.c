/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "calculadora.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

float *
sumar_1(float arg1, float arg2,  CLIENT *clnt)
{
	sumar_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, SUMAR, (xdrproc_t) xdr_sumar_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
restar_1(float arg1, float arg2,  CLIENT *clnt)
{
	restar_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, RESTAR, (xdrproc_t) xdr_restar_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
multiplicar_1(float arg1, float arg2,  CLIENT *clnt)
{
	multiplicar_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, MULTIPLICAR, (xdrproc_t) xdr_multiplicar_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
dividir_1(float arg1, float arg2,  CLIENT *clnt)
{
	dividir_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, DIVIDIR, (xdrproc_t) xdr_dividir_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
producto_escalar_1(t_vector arg1, t_vector arg2,  CLIENT *clnt)
{
	producto_escalar_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, PRODUCTO_ESCALAR, (xdrproc_t) xdr_producto_escalar_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

t_vector *
escalar_por_vector_1(float arg1, t_vector arg2,  CLIENT *clnt)
{
	escalar_por_vector_1_argument arg;
	static t_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, ESCALAR_POR_VECTOR, (xdrproc_t) xdr_escalar_por_vector_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_t_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

t_vector *
suma_vectores_1(t_vector arg1, t_vector arg2,  CLIENT *clnt)
{
	suma_vectores_1_argument arg;
	static t_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, SUMA_VECTORES, (xdrproc_t) xdr_suma_vectores_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_t_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

t_vector *
resta_vectores_1(t_vector arg1, t_vector arg2,  CLIENT *clnt)
{
	resta_vectores_1_argument arg;
	static t_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, RESTA_VECTORES, (xdrproc_t) xdr_resta_vectores_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_t_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

t_vector *
producto_vectorial_1(t_vector arg1, t_vector arg2,  CLIENT *clnt)
{
	producto_vectorial_1_argument arg;
	static t_vector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, PRODUCTO_VECTORIAL, (xdrproc_t) xdr_producto_vectorial_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_t_vector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
producto_mixto_1(t_vector arg1, t_vector arg2, t_vector arg3,  CLIENT *clnt)
{
	producto_mixto_1_argument arg;
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	arg.arg3 = arg3;
	if (clnt_call (clnt, PRODUCTO_MIXTO, (xdrproc_t) xdr_producto_mixto_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
media_1(t_vector arg1,  CLIENT *clnt)
{
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MEDIA,
		(xdrproc_t) xdr_t_vector, (caddr_t) &arg1,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

float *
potencia_1(potencia arg1,  CLIENT *clnt)
{
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, POTENCIA,
		(xdrproc_t) xdr_potencia, (caddr_t) &arg1,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

potencia *
multiplicar_potencias_1(potencia arg1, potencia arg2,  CLIENT *clnt)
{
	multiplicar_potencias_1_argument arg;
	static potencia clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, MULTIPLICAR_POTENCIAS, (xdrproc_t) xdr_multiplicar_potencias_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_potencia, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

potencia *
dividir_potencias_1(potencia arg1, potencia arg2,  CLIENT *clnt)
{
	dividir_potencias_1_argument arg;
	static potencia clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, DIVIDIR_POTENCIAS, (xdrproc_t) xdr_dividir_potencias_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_potencia, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
