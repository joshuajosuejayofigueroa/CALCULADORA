#include "calculo.h"
#include <stdexcept>
#include <cctype>
#include <cmath> // ojo: esto lo uso SOLO para floor() y fabs(), NO para pow/exp/log/sin/cos

using namespace std;

// Numero de Euler (e), lo necesito para el logaritmo. Lo pongo como
// constante en vez de calcularlo cada vez porque no cambia nunca.
const double NUMERO_EULER = 2.718281828459045235360287471352;

// =========================================================================
// PARTE 1: FUNCIONES RECURSIVAS BASE
// =========================================================================
// Idea general que me tengo clara para explicar en el video: TODA funcion
// recursiva necesita (1) un caso base, que es cuando ya no me sigo
// llamando a mi misma y devuelvo un valor directo, y (2) un caso
// recursivo, donde me vuelvo a llamar pero con un problema mas chico,
// acercandome cada vez mas al caso base.
// =========================================================================

// potencia(base, exponente) -> base elevado a exponente, con exponente ENTERO.
//
// Caso base: si el exponente es 0, cualquier numero elevado a 0 es 1.
// Caso recursivo: base^n = base * base^(n-1). Voy bajando el exponente
// de a uno hasta que llegue a 0 y ahi paro.
//
// Tambien contemplo el caso de exponente negativo: base^(-n) = 1 / base^n
double potencia(double base, long long exponente) {
    if (exponente == 0) {
        return 1.0; // caso base
    }
    if (exponente < 0) {
        // si el exponente es negativo, calculo la potencia positiva
        // y despues invierto (1 / resultado)
        return 1.0 / potencia(base, -exponente);
    }
    // caso recursivo: multiplico "base" por el resultado de una potencia
    // mas chica (exponente - 1). Cada llamada se acerca mas al caso base.
    return base * potencia(base, exponente - 1);
}

// factorial(numero) -> numero!  (ej: factorial(5) = 5*4*3*2*1 = 120)
//
// Antes de calcular nada, se valida que el numero no sea negativo, porque
// el factorial de un negativo no existe matematicamente. Si es negativo,
// lanzo una excepcion para que el menu principal la atrape y le avise
// al usuario que se equivoco.
//
// Caso base: 0! y 1! valen 1.
// Caso recursivo: n! = n * (n-1)!
double factorial(long long numero) {
    if (numero < 0) {
        throw runtime_error("No existe el factorial de un numero negativo");
    }
    if (numero == 0 || numero == 1) {
        return 1.0; // caso base
    }
    return static_cast<double>(numero) * factorial(numero - 1); // caso recursivo
}

// calcularExp(x) -> e^x usando la Serie de Taylor:
//
//      e^x = 1 + x + x^2/2! + x^3/3! + x^4/4! + ...
//          = suma para n=0 hasta infinito de:  x^n / n!
//
// Como en la vida real no puedo sumar "hasta el infinito", sumo solamente
// "terminos" cantidad de terminos (por defecto 25, que ya da bastante
// precision). Hago la suma de forma recursiva: en cada llamada calculo
// UN termino de la serie, y se lo sumo al resultado de seguir sumando
// los terminos que faltan (eso es la llamada recursiva).
//
// Notita: como necesito un contador "n" que vaya avanzando
// (0, 1, 2, 3...) ademas de "x", hice  una funcion recursiva auxiliar
// dentro de un struct (sumarTerminosExp). Esto es una tecnica comun
// cuando la funcion publica no deberia recibir ese contador como
// parametro (queda mas limpio para quien la usa desde el menu).
double calcularExp(double x, int terminos) {
    struct sumarTerminosExp {
        static double sumar(double x, int n, int maxTerminos) {
            if (n >= maxTerminos) {
                return 0.0; // caso base: ya sume todos los terminos que queria
            }
            double terminoActual = potencia(x, n) / factorial(n);
            return terminoActual + sumar(x, n + 1, maxTerminos); // caso recursivo
        }
    };
    return sumarTerminosExp::sumar(x, 0, terminos);
}

// calcularLn(x) -> logaritmo natural de x.
//
// Aqui tuve que pensar un poco mas. La serie de Taylor "de manual" para
// ln(1+u) = u - u^2/2 + u^3/3 - u^4/4 + ...  converge muy lento cuando
// "u" esta cerca de 1 (lo comprobe yo misma probando con x=2, me daba
// un resultado con error notorio). Por eso use una version mejor,
// basada en la funcion atanh, que converge mucho mas rapido:
//
//      y = (x-1)/(x+1)
//      ln(x) = 2 * ( y + y^3/3 + y^5/5 + y^7/7 + ... )
//
// Ademas, si x es un numero muy grande o muy chico, "y" se acerca a 1
// o a -1 y la serie converge lento otra vez. Para evitar eso, antes de
// sumar la serie "reduzco" el rango de x usando el numero de Euler,
// de forma recursiva:
//   - si x > 2:    ln(x) = 1 + ln(x/e)
//   - si x < 0.5:  ln(x) = -1 + ln(x*e)
// Esto lo hice probando distintos valores hasta encontrar el rango
// donde la serie converge rapido y bien (entre 0.5 y 2).
double calcularLn(double x, int terminos) {
    if (x <= 0) {
        throw runtime_error("El logaritmo natural no esta definido para x <= 0");
    }

    // Paso 1: reduccion de rango (esto tambien es recursivo)
    if (x > 2.0) {
        return 1.0 + calcularLn(x / NUMERO_EULER, terminos);
    }
    if (x < 0.5) {
        return -1.0 + calcularLn(x * NUMERO_EULER, terminos);
    }

    // Paso 2: ya tengo x entre 0.5 y 2, aqui si sumo la serie
    double y = (x - 1.0) / (x + 1.0);
    double ySquared = y * y; // lo calculo una sola vez para no repetir

    struct sumarTerminosLn {
        // potenciaImpar guarda y^(2n+1), y lo voy actualizando en cada
        // llamada multiplicando por ySquared (asi no repito potencias)
        static double sumar(double ySquared, double potenciaImpar, int n, int maxTerminos) {
            if (n >= maxTerminos) {
                return 0.0; // caso base
            }
            double terminoActual = potenciaImpar / static_cast<double>(2 * n + 1);
            return terminoActual + sumar(ySquared, potenciaImpar * ySquared, n + 1, maxTerminos);
        }
    };
    return 2.0 * sumarTerminosLn::sumar(ySquared, y, 0, terminos);
}

// calcularSeno(x) -> seno de x, con x en radianes.
//
//      sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
//             = suma para n=0 hasta infinito de: (-1)^n * x^(2n+1) / (2n+1)!
//
// Ojo con el signo: se alterna + - + - ... por eso calculo "signo"
// segun si n es par o impar.
double calcularSeno(double x, int terminos) {
    struct sumarTerminosSeno {
        static double sumar(double x, int n, int maxTerminos) {
            if (n >= maxTerminos) {
                return 0.0;
            }
            double signo = (n % 2 == 0) ? 1.0 : -1.0;
            double terminoActual = signo * potencia(x, 2 * n + 1) / factorial(2 * n + 1);
            return terminoActual + sumar(x, n + 1, maxTerminos);
        }
    };
    return sumarTerminosSeno::sumar(x, 0, terminos);
}

// calcularCoseno(x) -> coseno de x, con x en radianes. Es igual que el
// seno pero con potencias PARES (2n en vez de 2n+1).
//
//      cos(x) = 1 - x^2/2! + x^4/4! - x^6/6! + ...
double calcularCoseno(double x, int terminos) {
    struct sumarTerminosCoseno {
        static double sumar(double x, int n, int maxTerminos) {
            if (n >= maxTerminos) {
                return 0.0;
            }
            double signo = (n % 2 == 0) ? 1.0 : -1.0;
            double terminoActual = signo * potencia(x, 2 * n) / factorial(2 * n);
            return terminoActual + sumar(x, n + 1, maxTerminos);
        }
    };
    return sumarTerminosCoseno::sumar(x, 0, terminos);
}

// potenciaConDecimales(base, exponente) -> para cuando el exponente NO es
// un numero entero, por ejemplo 8^(1/3) o 2^0.5
//
// Aqui no puedo usar la misma logica de "potencia()" (multiplicar la base
// varias veces no tiene sentido si el exponente es fraccionario). Por eso
// uso una identidad matematica que aprendi repasando para este proyecto:
//
//      base^exponente = e^(exponente * ln(base))
//
// Y como YA tengo hechas mis funciones calcularExp() y calcularLn() de
// forma recursiva, simplemente las reutilizo aqui. Esto solo funciona
// si la base es positiva (por la restriccion del logaritmo).
double potenciaConDecimales(double base, double exponente) {
    if (base <= 0) {
        throw runtime_error("Para potencias con exponente decimal necesito una base positiva");
    }
    return calcularExp(exponente * calcularLn(base));
}

// =========================================================================
// PARTE 2: EVALUADOR DE EXPRESIONES
// =========================================================================
// Esta es la parte que mas trabajo me costo entender, asi que la anoto
// bien detallada para no olvidarme de la logica.
//
// El problema: si el usuario escribe "3 + 4 * 2", no puedo simplemente
// ir de izquierda a derecha sumando y multiplicando en el orden que
// aparecen, porque en matematica la multiplicacion tiene que hacerse
// ANTES que la suma (precedencia de operadores).
//
// La solucion que aprendi se llama "Recursive Descent Parsing" (analisis
// descendente recursivo). La idea es armar una funcion por cada "nivel
// de precedencia", de MENOR a MAYOR prioridad, donde cada funcion llama
// a la de mayor prioridad antes de aplicar su propio operador:
//
//   evaluarExpresion  -> maneja + y -            (menor prioridad)
//   evaluarTermino     -> maneja * , / y %
//   evaluarPotencia    -> maneja ^                (asociativo a la derecha)
//   evaluarUnario      -> maneja el signo -5
//   evaluarPostfijo    -> maneja el factorial 5!
//   evaluarValor       -> numeros, Ans/M1/M2, y parentesis (mayor prioridad)
//
// Todas estas funciones comparten una variable "posicion" que le paso
// POR REFERENCIA (con &) a cada una. Esa variable indica en que caracter
// de la expresion voy leyendo. Como la paso por referencia, cuando una
// funcion "consume" caracteres (avanza la posicion), todas las demas
// funciones (incluida la que la llamo) se enteran del avance.
// =========================================================================

// Salto los espacios en blanco para no confundirlos con parte de un numero
static void saltarEspacios(const string &texto, size_t &posicion) {
    while (posicion < texto.size() && isspace(static_cast<unsigned char>(texto[posicion]))) {
        posicion++;
    }
}

// Las declaro antes porque se llaman entre ellas (recursion "cruzada")
static double evaluarExpresionInterna(const string &texto, size_t &posicion, MemoriaCalculadora &memoria);
static double evaluarTermino(const string &texto, size_t &posicion, MemoriaCalculadora &memoria);
static double evaluarPotencia(const string &texto, size_t &posicion, MemoriaCalculadora &memoria);
static double evaluarUnario(const string &texto, size_t &posicion, MemoriaCalculadora &memoria);
static double evaluarPostfijo(const string &texto, size_t &posicion, MemoriaCalculadora &memoria);
static double evaluarValor(const string &texto, size_t &posicion, MemoriaCalculadora &memoria);

// evaluarValor: el nivel MAS profundo de la recursion. Aqui es donde
// realmente "leo" un numero, una variable de memoria, o abro un parentesis
// (y si abro un parentesis, vuelvo a llamar a evaluarExpresionInterna,
// que es el nivel MAS alto -- por eso los parentesis pueden contener
// cualquier expresion completa adentro, incluso otros parentesis).
static double evaluarValor(const string &texto, size_t &posicion, MemoriaCalculadora &memoria) {
    saltarEspacios(texto, posicion);
    if (posicion >= texto.size()) {
        throw runtime_error("La expresion termino antes de tiempo (esperaba un numero)");
    }

    // Reviso si lo que sigue es una variable de memoria
    if (texto.compare(posicion, 3, "Ans") == 0) {
        posicion += 3;
        return memoria.Ans;
    }
    if (texto.compare(posicion, 2, "M1") == 0) {
        posicion += 2;
        return memoria.M1;
    }
    if (texto.compare(posicion, 2, "M2") == 0) {
        posicion += 2;
        return memoria.M2;
    }

    // Si encuentro un parentesis que abre, resuelvo TODO lo de adentro
    // llamando de nuevo a evaluarExpresionInterna (aqui esta la magia
    // de la recursion: los parentesis pueden anidarse tantas veces como
    // se quiera, porque cada uno abre su propia "sub-evaluacion")
    if (texto[posicion] == '(') {
        posicion++; // como que "entro" al parentesis
        double valorDeAdentro = evaluarExpresionInterna(texto, posicion, memoria);
        saltarEspacios(texto, posicion);
        if (posicion >= texto.size() || texto[posicion] != ')') {
            throw runtime_error("Me falto un parentesis de cierre ')'");
        }
        posicion++; // "salgo" del parentesis
        return valorDeAdentro;
    }

    // Si no es nada de lo anterior, tiene que ser un numero
    if (isdigit(static_cast<unsigned char>(texto[posicion])) || texto[posicion] == '.') {
        size_t inicioDelNumero = posicion;
        while (posicion < texto.size() &&
               (isdigit(static_cast<unsigned char>(texto[posicion])) || texto[posicion] == '.')) {
            posicion++;
        }
        return stod(texto.substr(inicioDelNumero, posicion - inicioDelNumero));
    }

    throw runtime_error(string("No entendi este caracter: '") + texto[posicion] + "'");
}

// evaluarPostfijo: aplica el factorial DESPUES de leer el valor. Ej: 5!
// Lo puse en su propio nivel porque el factorial "se pega" al numero
// antes que cualquier otra operacion (mayor prioridad que todo lo demas).
static double evaluarPostfijo(const string &texto, size_t &posicion, MemoriaCalculadora &memoria) {
    double valor = evaluarValor(texto, posicion, memoria);
    saltarEspacios(texto, posicion);
    while (posicion < texto.size() && texto[posicion] == '!') {
        posicion++;
        if (valor < 0 || floor(valor) != valor) {
            throw runtime_error("El factorial solo se puede calcular de enteros no negativos");
        }
        valor = factorial(static_cast<long long>(valor));
        saltarEspacios(texto, posicion);
    }
    return valor;
}

// evaluarUnario: se encarga del signo negativo delante de un numero,
// como en "-5" o "-(2+3)". Es recursiva porque podria venir mas de un
// signo seguido, aunque en la practica casi no se usa asi (--5).
static double evaluarUnario(const string &texto, size_t &posicion, MemoriaCalculadora &memoria) {
    saltarEspacios(texto, posicion);
    if (posicion < texto.size() && texto[posicion] == '-') {
        posicion++;
        return -evaluarUnario(texto, posicion, memoria); // recursion
    }
    if (posicion < texto.size() && texto[posicion] == '+') {
        posicion++;
        return evaluarUnario(texto, posicion, memoria);
    }
    return evaluarPostfijo(texto, posicion, memoria);
}

// evaluarPotencia: maneja el operador ^
//
// Algo que aprendi y me parecio curioso: la potencia es "asociativa a la
// derecha". Eso significa que 2^3^2 se interpreta como 2^(3^2) = 2^9,
// NO como (2^3)^2 = 8^2. Por eso, cuando encuentro un '^', para calcular
// el exponente vuelvo a llamar a evaluarPotencia (no a evaluarUnario),
// dejando que la recursion se encargue de "agrupar de derecha a izquierda".
static double evaluarPotencia(const string &texto, size_t &posicion, MemoriaCalculadora &memoria) {
    double base = evaluarUnario(texto, posicion, memoria);
    saltarEspacios(texto, posicion);
    if (posicion < texto.size() && texto[posicion] == '^') {
        posicion++;
        double exponente = evaluarPotencia(texto, posicion, memoria); // asociatividad derecha
        if (floor(exponente) == exponente) {
            return potencia(base, static_cast<long long>(exponente));
        } else {
            return potenciaConDecimales(base, exponente);
        }
    }
    return base;
}

// evaluarTermino: maneja *, / y %. Estos tienen mas prioridad que + y -,
// por eso este nivel esta "mas adentro" en la cadena de llamadas.
static double evaluarTermino(const string &texto, size_t &posicion, MemoriaCalculadora &memoria) {
    double resultado = evaluarPotencia(texto, posicion, memoria);
    saltarEspacios(texto, posicion);

    while (posicion < texto.size() &&
           (texto[posicion] == '*' || texto[posicion] == '/' || texto[posicion] == '%')) {
        char operador = texto[posicion];
        posicion++;
        double numeroDerecho = evaluarPotencia(texto, posicion, memoria);

        if (operador == '*') {
            resultado = resultado * numeroDerecho;
        } else if (operador == '/') {
            if (numeroDerecho == 0) {
                throw runtime_error("No se puede dividir entre cero");
            }
            resultado = resultado / numeroDerecho;
        } else { // operador == '%'
            if (numeroDerecho == 0) {
                throw runtime_error("No se puede sacar modulo entre cero");
            }
            // Hago el modulo "a mano" para que tambien funcione con
            // numeros decimales (el % de C++ normal solo sirve con enteros)
            long long veces = static_cast<long long>(resultado / numeroDerecho);
            resultado = resultado - veces * numeroDerecho;
        }
        saltarEspacios(texto, posicion);
    }
    return resultado;
}

// evaluarExpresionInterna: el nivel de MENOR prioridad, maneja + y -.
// Es el punto de entrada de toda la recursion (y tambien el nivel al
// que "regreso" cada vez que abro un parentesis).
static double evaluarExpresionInterna(const string &texto, size_t &posicion, MemoriaCalculadora &memoria) {
    double resultado = evaluarTermino(texto, posicion, memoria);
    saltarEspacios(texto, posicion);

    while (posicion < texto.size() && (texto[posicion] == '+' || texto[posicion] == '-')) {
        char operador = texto[posicion];
        posicion++;
        double numeroDerecho = evaluarTermino(texto, posicion, memoria);
        resultado = (operador == '+') ? resultado + numeroDerecho : resultado - numeroDerecho;
        saltarEspacios(texto, posicion);
    }
    return resultado;
}

// Esta es la funcion "publica" que uso desde el menu. Se encarga de
// arrancar la posicion en 0 y de revisar que, al terminar, no haya
// quedado ningun caracter raro sobrante (por ejemplo un parentesis de
// mas al final, que indicaria que el usuario escribio algo mal).
double evaluarExpresion(const string &expresionTexto, MemoriaCalculadora &memoria) {
    size_t posicion = 0;
    double resultado = evaluarExpresionInterna(expresionTexto, posicion, memoria);
    saltarEspacios(expresionTexto, posicion);
    if (posicion != expresionTexto.size()) {
        throw runtime_error("Sobraron caracteres al final, revisa los parentesis de tu expresion");
    }
    return resultado;
}
