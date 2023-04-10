#include <cmath>
#include <vector>
#include <random>

// Esta funcion calcula la distancia al cuadrado entre dos 
// puntos A y B con coordenadas (x0, y0, z0) y (x, y, z) 
// respectivamente. 
double distancia2(double x0, double y0, double z0, 
		double x, double y, double z) {
	double dist2;

	dist2 = pow(x-x0,2) 
		+ pow(y-y0,2) 
		+ pow(z-z0,2);

	return dist2;
}

// Esta funcion devuelve la cantidad de elementos en el
// vector distancias que son menores al valor de radio.
int conteo2(double radio, 
		std::vector<double> distancias) {
	const double h = 0.6767;
	double r2;

	r2 = pow(radio/h,2);

	int cantidad = 0;
	for (const auto& valor : distancias) {
		if (valor < r2 and
				valor != 0) {
			cantidad += 1;
		}
	}

	return cantidad;
}

// Esta funcion realiza un histograma con los elementos
// del vector distancias. Cada bin es un intervalo entre
// 2 Mpc.
std::vector<std::vector<int>> histograma2(
		std::vector<std::vector<double>> distancias,
		int cant_radios) {
	const double h = 0.6767;
	int bines = int(cant_radios/2);
	std::vector<std::vector<int>> histograma;

	for (const auto& fila : distancias)
	{
		std::vector<int> histo;
		for (const auto& valor : fila) 
		{
			for (int i = 0; i < bines; i++)
			{
				int j = 2 * i;
				double rmin;
				rmin = pow(j/h,2);
				double rmax;
				rmax = pow((j+2)/h,2);
				int a = round(rmin);
				int b = round(rmax);
				if (valor >= a and valor < b)
				{
					histo[i] += 1;
				}
			}
		}
		histograma.push_back(histo);
	}

	return histograma;
}

// Esta funcion devuelve un vector que es la suma de todos
// los vectores filas de una matriz.
std::vector<int> suma(
		std::vector<std::vector<int>> histograma) {
	std::vector<int> n;

	for (const auto& fila : histograma) {
		int i = 0;
		for (const auto& valor : fila) {
			n[i] += valor;
			i++;
		}
	}

	return n;
}

// Esta funcion multiplica un vector de tipo double por
// una constante.
std::vector<double> producto_double(
		std::vector<double> vec,
		double a){
	std::vector<double> resultado;
	for (const auto& valor : vec) {
		double aux = a * valor;
		resultado.push_back(aux);
	}

	return resultado;
}

// Esta funcion multiplica un vector de tipo int por
// una constante.
std::vector<double> producto_int(
		std::vector<int> vec,
		double a){
	std::vector<double> resultado;
	for (const auto& valor : vec) {
		double aux = a * valor;
		resultado.push_back(aux);
	}

	return resultado;
}

// Esta funcion guarda los datos de un vector en una
// matriz que en la primera fila tiene los valores de
// los radios y en la segunda columna tiene los datos
// del vector.
std::vector<std::vector<double>> arreglo(
		std::vector<double> vec) {
	std::vector<std::vector<double>> matriz;
	double radio = 2;
	for (const auto& valor : vec) {
		std::vector<double> fila;
		fila.push_back(radio);
		fila.push_back(valor);
		matriz.push_back(fila);
		radio += 2;
	}

	return matriz;
}

// Esta funcion genera un valor entero de forma
// pseudo-aleatoria en el intervalo (a,b).
int aleatorio(int semilla, int a, int b) {
	std::mt19937 generador(semilla);
	std::uniform_int_distribution<int> distribucion(a,b);
	int num_aleatorio = distribucion(generador);
	
	return num_aleatorio;
}
