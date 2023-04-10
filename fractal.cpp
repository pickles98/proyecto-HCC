#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include "funciones.h"
#include "func_lec_esc.h"

int main() {
	std::ifstream archivo("datos.tsv");
//	std::string nombre_archivo = "datos.tsv";
	char sep = ',';
	std::vector<std::vector<double>> datos;
	//std::vector<double> RA;
	//std::vector<double> DE;
	//std::vector<double> rs;

	//std::string linea_vacia;
	//std::getline(archivo, linea_vacia);
	
	if (archivo.is_open()) {
		//std::string linea;
		//while (std::getline(archivo, linea)) {
		//	std::istringstream ss(linea);
		//	std::vector<double> fila;
		//	double valor;
		//	while (ss >> valor) {
		//		fila.push_back(valor);
		//		if (ss.peek() == sep) {
		//			ss.ignore();
		//		}
		//	}
		//	RA.push_back(fila[0]);
		//	DE.push_back(fila[1]);
		//	rs.push_back(fila[2]);
		//}
		//
		datos = lectura(archivo, sep);
		archivo.close();
	} else {
		std::cerr << "No se pudo abrir el archivo." << std::endl;
		return 1;
	}

	int N = datos.size();		//cantidad de galaxias
	
	std::vector<double> RA;
	std::vector<double> DE;
	std::vector<double> rs;

	for (const auto& fila : datos) {
		std::vector<double> aux;
		for (const auto& valor : fila) {
			aux.push_back(valor);
		}
		RA.push_back(aux[0]);
		DE.push_back(aux[1]);
		rs.push_back(aux[2]);
	}

	std::vector<double> dist0;	//vector que contiene las distancias a nuestra galaxia
	std::vector<double> x;		//coordenadas (x,y,z) de cada galaxia en Mpc
	std::vector<double> y;
	std::vector<double> z;

	const double c = 299792.458;	//vel. de la luz en km/s
	const double h = 0.6767;	//parametro de Hubble
	
	// distancia[Mpc] = rs * c / H0
	for (int i = 0; i < N; i++) {
		double valor = rs[i] * c / (h*100.);
		dist0.push_back(valor);
	}

	for (int i = 0; i < N; i++) {
		double x1 = dist0[i] * cos(DE[i]) * cos(RA[i]);
		double y1 = dist0[i] * cos(DE[i]) * sin(RA[i]);
		double z1 = dist0[i] * sin(DE[i]);
		x.push_back(x1);
		y.push_back(y1);
		z.push_back(z1);
	}

	// En este paso defino mi conjunto de galaxias centro
	int M = 100;		//cantidad de galaxias centro que voy a utilizar 
	std::vector<int> galaxias_centro;
	double limite = 150;	//mas alla de esta distancia no tomamos galaxias pues puede
				//haber problemas de borde
	int semilla;
	std::cout << "Ingrese un valor para la semilla" << std::endl;
	std::cin >> semilla;
	int m = 0;
	while (m < M) {
		int num_alt;
	//Creo un objeto mt19937 como generador de números utilizando Mersenne twister
		//std::mt19937 generador(semilla);
	//Creo una distribucion uniforme para generar numero enteros entre 
	//todos los indices de las galaxias
		//std::uniform_int_distribution<int> distribucion(0, N); 
		//int num_alt = distribucion(generador);		//Genero un número aleatorio
		//semilla += 1;	//vario el valor de la semilla para cambiar el nro generado
		num_alt = aleatorio(semilla, 0, N);
		if (dist0[num_alt] < limite) {
			galaxias_centro.push_back(num_alt);
			m += 1;
		}
	}

	//En este paso guardo las distancias a mis galaxias centro en una matriz 
	std::vector<std::vector<double>> dtogc;		// vector de vectores que guardara 
							//las distancias a las galaxias centro
	for (const auto& galaxia : galaxias_centro) {
		std::vector<double> fila;
		for (int i = 0; i < N; i++) {
			double valor;
			valor = distancia2(x[galaxia], y[galaxia], z[galaxia], x[i], y[i], z[i]);
			fila.push_back(valor);
		}
		dtogc.push_back(fila);
	}

	double rmax = 352;	//limite para los r
	int radios = int(rmax/2);
	int rprom = 192; 	//cantidad de radios para el grafico r vs N(r)
	std::vector<std::vector<double>> promedio;
	std::vector<double> C2;
	// En este paso calculo el promedio de la cantidad de galaxias que
	// entraban en cada esfera de radio r. De paso calculo el valor C2(r).
	double r = 2;
	while (r < rmax) {
		double sum = 0;
		double prom;	//promedio(r) = cant_galaxias * C2(r)
		double c2;		//valor de C2(r)
		std::vector<double> filap; //guardo las filas de promedio
		filap.push_back(r);
		for (const auto& fila : dtogc) {
			int cg = conteo2(r, fila);
			sum += cg;
		}
		prom = sum / M;
		c2 = prom / N;
		filap.push_back(prom);
		if (r < rprom) {
			promedio.push_back(filap);
		}
		C2.push_back(c2);
		r += 2;
	}

	//std::vector<int> conteo;
 	//for (const auto& fila : dtogc) {
	//	conteo = histograma2(fila, N, radios);
		//for (int i = 0; i < radios; i++) {
		//	suma[i] += conteo[i];
		//}
	//}
	//for (const auto& valor : conteo) {
	//	std::cout << valor << " ";
	//}
	//std::cout << std::endl;


	//for (int i = 0; i < radios; i++) {
	//	std::vector<double> filap;
	//	double c2 = suma[i] / (N*M);
	//	filap.push_back(i+2);
	//	if (2*i < rprom) {
	//		double prom = suma[i]/M;
	//		filap.push_back(prom);
	//		promedio.push_back(filap);
	//	}
	//	C2.push_back(c2);
	//}

	// En este paso calculo D2(r)
	std::vector<std::vector<double>> D2;
	for (int i = 0; i < radios - 1; i++) {
		std::vector<double> fila;
		double d2 = 0;
		fila.push_back(2*i+2);
		d2 = (log10(C2[i+1])-log10(C2[i]))/(log10(i+1)-log10(i));
		fila.push_back(d2);
		D2.push_back(fila);
	}

	// Creo mis archivos donde voy a guardar los datos para hacer los graficos
	std::ofstream archivo_salida1("promedios.dat");
	std::ofstream archivo_salida2("D2.dat");

	archivo_salida1 << "radio" << " " << "prom" << " " << std::endl;
	for (const auto& fila : promedio) {
		for (const auto& valor : fila) {
			archivo_salida1 << valor << " ";
		}
		archivo_salida1 << std::endl;
	}
	archivo_salida1.close();
	
	archivo_salida2 << "radio" << " " << "D2(r)" << " " << std::endl;
	for (const auto& fila : D2) {
		for (const auto& valor : fila) {
			archivo_salida2 << valor << " ";
		}
		archivo_salida2 << std::endl;
	}
	archivo_salida2.close();

	std::cout << "Archivos de salida listos." << std::endl;
	
	return 0;
}
