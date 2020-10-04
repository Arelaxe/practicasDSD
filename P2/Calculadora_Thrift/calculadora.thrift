service Calculadora {
    void ping(),
    double suma (1:double num1 , 2:double  num2),
    double resta (1: double num1 , 2:double  num2),
    double multiplicar (1: double num1 , 2:double  num2),
    double dividir (1: double num1 , 2:double  num2),
    double producto_escalar (1: list<double> v1, 2: list<double> v2),
    list<double> escalar_por_vector (1: double num, 2: list<double> v),
    list<double> suma_vectores (1: list<double> v1, 2: list<double> v2),
    list<double> resta_vectores (1: list<double> v1, 2: list<double> v2),
    list<double> producto_vectorial (1: list<double> v1, 2: list<double> v2),
    double producto_mixto (1: list<double> v1, 2: list<double> v2, 3: list<double> v3),
    double media (1: list<double> v),
    double potencia (1:double base, 2:double exponente),
}