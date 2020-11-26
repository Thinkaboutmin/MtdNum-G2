#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tinyexpr.h"



double mainFunction(const double x, const char* equation) {
  const te_variable vars[] = {{"x", &x}};

  int err;

  const auto eq = te_compile(equation, vars, 1, &err);
  
  if(err != 0) {
    printf("Erro ao interpretar");
  }

  return te_eval(eq);
}

// Realiza o cálculo do xi
double iterFun(double p_x, double x,const char * equation) {
  double f_x = mainFunction(x, equation); // F(X)
  double f_p_x = mainFunction(p_x, equation); // F(x-1)
  double p_x_minus_x = p_x - x; // x-1 - x

  return x - ((f_x * p_x_minus_x) / (f_p_x - f_x));
}

double errorFun(double past_x, double x) {
   return fabs(((x - past_x) / x)) * 100;
}

void getText(char *message, char *variable, int size){
    printf("\n %s: ", message);
    fgets(variable, sizeof(char) * size, stdin);
    sscanf(variable, "%[^\n]", variable);
}

int main()
{
    float x, x0;
    int ite;
    char * equation = (char *)calloc(150, sizeof(char));

    getText("Digite a equação (exemplo: -5 + 17.7*x - 11*(x^2) + 2*(x^3))", equation, 150);

    printf("\nDigite o valor de x-1: ");
    scanf("%f",&x);
    
    printf("\nDigite o valor de x0: ");
    scanf("%f",&x0);
    
    printf("\nDigite o numero de iteracoes: ");
    scanf("%d",&ite);
    
    printf("iteracao\txi-1\tf(xi-1)\txi\tf(xi)\tEa\n");
    for(int i = 0; ite != 0; --ite, ++i) {
        double ea = 0;
        if (i > 0) {
          double tmp_x = x0;
          x0 = iterFun(x, x0, equation); // o próximo x0 é o cálculo
          x = tmp_x; // o próximo x-1 é o x0 anterior

          ea = errorFun(tmp_x, x0);
        }

        // Imprime as iterações
        printf("%d", i);

        // Imprime o xi-1
        printf("\t%f", x);

        // Imprime o f(xi-1)
        printf("\t%f", mainFunction(x, equation));

        // Imprime o xi
        printf("\t%f", x0);

        // Imprime o f(xi)
        printf("\t%f", mainFunction(x0, equation));

        // Imprime o f(xi)
        printf("\t%f\n", ea);
    }
    return 0;
}