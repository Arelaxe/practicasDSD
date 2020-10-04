#include "calculadora.h"
#include <stdio.h>
#include <math.h>

float *
sumar_1_svc(float arg1, float arg2,  struct svc_req *rqstp)
{
	static float  result;

	result = arg1+arg2;

	return &result;
}

float *
restar_1_svc(float arg1, float arg2,  struct svc_req *rqstp)
{
	static float  result;

	result = arg1-arg2;

	return &result;
}

float *
multiplicar_1_svc(float arg1, float arg2,  struct svc_req *rqstp)
{
	static float  result;

	result = arg1*arg2;

	return &result;
}

float *
dividir_1_svc(float arg1, float arg2,  struct svc_req *rqstp)
{
	static float  result;

	result = arg1/arg2;

	return &result;
}

float *
producto_escalar_1_svc(t_vector arg1, t_vector arg2,  struct svc_req *rqstp)
{
	static float  result;
	float r = 0;
	int contador = 0;

	while(contador<arg1.t_vector_len){
		r += arg1.t_vector_val[contador]*arg2.t_vector_val[contador];
		contador++;
	}

	result = r;

	return &result;
}

t_vector *
escalar_por_vector_1_svc(float arg1, t_vector arg2,  struct svc_req *rqstp)
{
	static t_vector  result;

	result.t_vector_val = (float *) malloc(arg2.t_vector_len);
	result.t_vector_len = arg2.t_vector_len;

	for (int i=0; i<arg2.t_vector_len; i++){
		result.t_vector_val[i] = arg2.t_vector_val[i]*arg1;
	}

	return &result;
}

t_vector *
suma_vectores_1_svc(t_vector arg1, t_vector arg2,  struct svc_req *rqstp)
{
	static t_vector  result;
	int contador = 0;
	result.t_vector_val = (float *) malloc(50*sizeof(float));
	result.t_vector_len = 0;

	while (contador < arg1.t_vector_len){
		result.t_vector_val[contador] = arg1.t_vector_val[contador] + arg2.t_vector_val[contador];
		result.t_vector_len++;
		contador++;
	}

	return &result;
}

t_vector *
resta_vectores_1_svc(t_vector arg1, t_vector arg2,  struct svc_req *rqstp)
{
	static t_vector  result;
	int contador = 0;
	result.t_vector_val = (float *) malloc(50*sizeof(float));
	result.t_vector_len = 0;

	while (contador < arg1.t_vector_len){
		result.t_vector_val[contador] = arg1.t_vector_val[contador] - arg2.t_vector_val[contador];
		result.t_vector_len++;
		contador++;
	}

	return &result;
}

t_vector *
producto_vectorial_1_svc(t_vector arg1, t_vector arg2,  struct svc_req *rqstp)
{
	static t_vector  result;
	int tam = 3;
	
	result.t_vector_val = (float *) malloc(tam*sizeof(float));
	result.t_vector_len = tam;

	result.t_vector_val[0] = arg1.t_vector_val[1]*arg2.t_vector_val[2] - arg1.t_vector_val[2]*arg2.t_vector_val[1];
	result.t_vector_val[1] = arg1.t_vector_val[2]*arg2.t_vector_val[0] - arg1.t_vector_val[0]*arg2.t_vector_val[2];
	result.t_vector_val[2] = arg1.t_vector_val[0]*arg2.t_vector_val[1] - arg1.t_vector_val[1]*arg2.t_vector_val[0];

	return &result;
}

float *
producto_mixto_1_svc(t_vector arg1, t_vector arg2, t_vector arg3,  struct svc_req *rqstp)
{
	static float  result;
	t_vector vector_intermedio;
	int tam = 3;
	float r;

	vector_intermedio.t_vector_val = (float *) malloc(tam*sizeof(float));
	vector_intermedio.t_vector_len = tam;

	vector_intermedio.t_vector_val[0] = arg2.t_vector_val[1]*arg3.t_vector_val[2] - arg2.t_vector_val[2]*arg3.t_vector_val[1];
	vector_intermedio.t_vector_val[1] = arg2.t_vector_val[2]*arg3.t_vector_val[0] - arg2.t_vector_val[0]*arg3.t_vector_val[2];
	vector_intermedio.t_vector_val[2] = arg2.t_vector_val[0]*arg3.t_vector_val[1] - arg2.t_vector_val[1]*arg3.t_vector_val[0];

	for (int i=0; i<tam; i++){
		r += arg1.t_vector_val[i]*vector_intermedio.t_vector_val[i];
	}

	result = r;
		
	return &result;
}

float *
media_1_svc(t_vector arg1,  struct svc_req *rqstp)
{
	static float  result;
	float r = 0;

	for (int i=0; i<arg1.t_vector_len; i++){
		r += arg1.t_vector_val[i];
	}

	r /= arg1.t_vector_len;

	result = r;

	return &result;
}

float *
potencia_1_svc(potencia arg1,  struct svc_req *rqstp)
{
	static float  result = 0;
	
	result = pow(arg1.base,arg1.exponente);

	return &result;
}

potencia *
multiplicar_potencias_1_svc(potencia arg1, potencia arg2,  struct svc_req *rqstp)
{
	static potencia  result;

	result.base = arg1.base;
	result.exponente = arg1.exponente+arg2.exponente;

	return &result;
}

potencia *
dividir_potencias_1_svc(potencia arg1, potencia arg2,  struct svc_req *rqstp)
{
	static potencia  result;

	result.base = arg1.base;
	result.exponente = arg1.exponente-arg2.exponente;

	return &result;
}
