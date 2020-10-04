typedef float t_vector<>;

struct potencia{
    float base;
    float exponente;
};

typedef struct potencia potencia;

program CALCULADORA {
    version CALCULADORAVERS{
        float SUMAR (float,float) = 1;
        float RESTAR (float,float) = 2;
        float MULTIPLICAR (float,float) = 3;
        float DIVIDIR (float,float) = 4;
        float PRODUCTO_ESCALAR (t_vector,t_vector) = 5;
        t_vector ESCALAR_POR_VECTOR (float,t_vector) = 6;
        t_vector SUMA_VECTORES (t_vector,t_vector) = 7;
        t_vector RESTA_VECTORES (t_vector,t_vector) = 8;
        t_vector PRODUCTO_VECTORIAL (t_vector,t_vector) = 9;
        float PRODUCTO_MIXTO (t_vector,t_vector,t_vector) = 10;
        float MEDIA (t_vector) = 11;
        float POTENCIA (potencia) = 13;
        potencia MULTIPLICAR_POTENCIAS (potencia,potencia) = 14;
        potencia DIVIDIR_POTENCIAS (potencia,potencia) = 15;
    } = 1;
} = 0x20000001;