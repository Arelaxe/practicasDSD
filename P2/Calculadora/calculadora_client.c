#include <stdio.h>
#include <string.h>
#include "calculadora.h"

int
main (int argc, char *argv[])
{
	
	char *host;
	CLIENT *clnt;
	char opcion;
	float op1, op2;
	char operador;
	float * result;
	t_vector v1, v2,v3;
	float valor;
	t_vector * resultado_v;
	t_vector result_v;
	int n;
	float escalar;
	potencia * res_p;
	potencia pot1,pot2, res_pot;
	
	v1.t_vector_val = (float *)malloc(500*sizeof(float));
	v2.t_vector_val = (float *)malloc(500*sizeof(float));
	v3.t_vector_val = (float *)malloc(500*sizeof(float));
	v1.t_vector_len = 0;
	v2.t_vector_len = 0;
	v3.t_vector_len = 0;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];

	clnt = clnt_create (host, CALCULADORA, CALCULADORAVERS, "udp");

	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	printf("1: Operación básica\n2: Operación con vectores\n3: Media\n4: Operación con potencias \n");

	scanf("%s",&opcion);

	switch (opcion){
		case '1':
			printf("Introduce la operación de la siguiente manera: <operando 1> <operador> <operando 2>\n");
			scanf("%f %c %f",&op1,&operador,&op2);
			switch(operador){
				case '+':
					result = sumar_1(op1,op2,clnt);
					if (result == (float *) NULL) {
						clnt_perror (clnt, "call failed");
					}
				break;
				case '-':
					result = restar_1(op1,op2,clnt);
					if (result == (float *) NULL) {
						clnt_perror (clnt, "call failed");
					}
				break;
				case 'x':
					result = multiplicar_1(op1,op2,clnt);
					if (result == (float *) NULL) {
						clnt_perror (clnt, "call failed");
					}
				break;
				case '/':
					result = dividir_1(op1,op2,clnt);
					if (result == (float *) NULL) {
						clnt_perror (clnt, "call failed");
					}
				break;
				default:
					printf("Esta operación no está definida\n");
				break;
			}
			printf("El resultado es %f\n",*result);
		break;		
		
		case '2':
			printf("Producto escalar: 1\nSuma: 2\nResta: 3\nProducto vectorial: 4\nProducto mixto: 5\nEscalar por vector: 6\n");
			scanf("%s",&opcion);
			switch(opcion){
				case '1':
					printf("Introduce la dimensión de los vectores: ");
					scanf("%d",&n);

					printf("Introduce el primer vector:\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v1.t_vector_val[i] = valor;
						v1.t_vector_len++;
					}

					printf("Introduce el segundo vector:\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v2.t_vector_val[i] = valor;
						v2.t_vector_len++;
					}

					result = producto_escalar_1(v1,v2,clnt);
					if (result == (float *) NULL) {
						clnt_perror (clnt, "call failed");
					}
					float r = *result;
					printf("Resultado: %f\n", r);
				break;

				case '2':
					printf("Introduce la dimensión de los vectores: ");
					scanf("%d",&n);

					printf("Introduce el primer vector:\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v1.t_vector_val[i] = valor;
						v1.t_vector_len++;
					}

					printf("Introduce el segundo vector:\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v2.t_vector_val[i] = valor;
						v2.t_vector_len++;
					}

					resultado_v = suma_vectores_1(v1,v2,clnt);
					if (resultado_v == (t_vector *) NULL) {
						clnt_perror (clnt, "call failed");
					}

					result_v = *resultado_v;
					printf("Vector resultado: ");
					for (int i=0; i<result_v.t_vector_len; i++){
						printf("%f ",result_v.t_vector_val[i]);
					}
					printf("\n");
				break;

				case '3':
					printf("Introduce la dimensión de los vectores: ");
					scanf("%d",&n);

					v1.t_vector_len = n;

					printf("Introduce el primer vector:\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v1.t_vector_val[i] = valor;
					}

					printf("Introduce el segundo vector:\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v2.t_vector_val[i] = valor;
						v2.t_vector_len++;
					}

					resultado_v = resta_vectores_1(v1,v2,clnt);
					if (resultado_v == (t_vector *) NULL) {
						clnt_perror (clnt, "call failed");
					}

					result_v = *resultado_v;
					printf("Vector resultado: ");
					for (int i=0; i<result_v.t_vector_len; i++){
						printf("%f ",result_v.t_vector_val[i]);
					}
					printf("\n");
				break;

				case '4':
					n=3;
					printf("Introduce el primer vector (3 valores, con más el producto vectorial no tiene sentido)\n");

					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v1.t_vector_val[i] = valor;
						v1.t_vector_len++;
					}

					printf("Introduce el segundo vector (3 valores, con más el producto vectorial no tiene sentido)\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v2.t_vector_val[i] = valor;
						v2.t_vector_len++;
					}

					resultado_v = producto_vectorial_1(v1,v2,clnt);
					if (resultado_v == (t_vector *) NULL) {
						clnt_perror (clnt, "call failed");
					}
					result_v = *resultado_v;

					printf("Vector resultado: ");

					for (int i=0; i<result_v.t_vector_len; i++){
						printf("%f ",result_v.t_vector_val[i]);
					}
					printf("\n");
				break;

				case '5':
					n=3;
					printf("Introduce el primer vector (3 valores, con más el producto mixto no tiene sentido)\n");

					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v1.t_vector_val[i] = valor;
						v1.t_vector_len++;
					}

					printf("Introduce el segundo vector (3 valores, con más el producto mixto no tiene sentido)\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v2.t_vector_val[i] = valor;
						v2.t_vector_len++;
					}

					printf("Introduce el tercer vector (3 valores, con más el producto mixto no tiene sentido)\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v3.t_vector_val[i] = valor;
						v3.t_vector_len++;
					}

					result = producto_mixto_1(v1,v2,v3,clnt);
					if (result == (float *) NULL) {
						clnt_perror (clnt, "call failed");
					}

					printf("Resultado: %f\n",*result);
				break;

				case '6':
					printf("Introduce la dimensión del vector\n");
					scanf("%d",&n);

					printf("Introduce el vector\n");
					for (int i=0;i<n;i++){
						scanf("%f",&valor);
						v1.t_vector_val[i] = valor;
						v1.t_vector_len++;
					}

					printf("Introduce el escalar\n");
					scanf("%f",&escalar);

					resultado_v = escalar_por_vector_1(escalar,v1,clnt);
					if (resultado_v == (t_vector *) NULL) {
						clnt_perror (clnt, "call failed");
					}

					result_v = *resultado_v;

					printf("Vector resultado: ");

					for (int i=0; i<result_v.t_vector_len; i++){
						printf("%f ",result_v.t_vector_val[i]);
					}
					printf("\n");
				break;

				default:
					printf("Esta opción no está definida\n");
				break;
			}
		break;

		case '3':
			printf("¿Cuántos valores vas a introducir? ");
			scanf("%d",&n);

			printf("Introduce los valores\n");
			for (int i=0;i<n;i++){
				scanf("%f",&valor);
				v1.t_vector_val[i] = valor;
				v1.t_vector_len++;
			}

			result = media_1(v1,clnt);
			if (result == (float *) NULL) {
				clnt_perror (clnt, "call failed");
			}

			printf("El resultado es %f\n",*result);
		break;

		case '4':
			printf("1: Potencia básica\n2: Multiplicación\n3: División\n");
			scanf("%s",&opcion);
			
			switch (opcion)
			{
			case '1':
				printf("Introduce la base: ");
				scanf("%f",&pot1.base);
				printf("Introduce el exponente: ");
				scanf("%f",&pot1.exponente);

				result = potencia_1(pot1,clnt);
				if (result == (float *) NULL){
					clnt_perror (clnt, "call failed");
				}

				printf("El valor de la potencia es: %f\n",*result);
			break;

			case '2':
				printf("Introduce la base de las potencias (solo una, ya que debe ser la misma): ");
				scanf("%f",&pot1.base);
				pot2.base = pot1.base;
				printf("Introduce el exponente de la primera potencia: ");
				scanf("%f",&pot1.exponente);
				printf("Introduce el exponente de la segunda potencia: ");
				scanf("%f",&pot2.exponente);

				res_p = multiplicar_potencias_1(pot1,pot2,clnt);
				if(res_p == (potencia *) NULL){
					clnt_perror (clnt, "call failed");
				}

				res_pot = *res_p;

				result = potencia_1(res_pot,clnt);
				if(result == (float *) NULL){
					clnt_perror (clnt, "call failed");
				}

				printf("La potencia resultante es %f^%f y su valor es %f\n",res_pot.base,res_pot.exponente,*result);
			break;

			case '3':
				printf("Introduce la base de las potencias (solo una, ya que debe ser la misma): ");
				scanf("%f",&pot1.base);
				pot2.base = pot1.base;
				printf("Introduce el exponente de la primera potencia: ");
				scanf("%f",&pot1.exponente);
				printf("Introduce el exponente de la segunda potencia: ");
				scanf("%f",&pot2.exponente);

				res_p = dividir_potencias_1(pot1,pot2,clnt);
				if(res_p == (potencia *) NULL){
					clnt_perror (clnt, "call failed");
				}

				res_pot = *res_p;

				result = potencia_1(res_pot,clnt);
				if(result == (float *) NULL){
					clnt_perror (clnt, "call failed");
				}

				printf("La potencia resultante es %f^%f y su valor es %f\n",res_pot.base,res_pot.exponente,*result);
			break;
			
			default:
				printf("Esta opción no está definida\n");
			break;
			}
		break;

		default:
			printf("Esta opción no es válida\n");
		break;
	}

	free(v1.t_vector_val);
	free(v2.t_vector_val);
	free(v3.t_vector_val);

	clnt_destroy (clnt);
	
exit (0);
}
