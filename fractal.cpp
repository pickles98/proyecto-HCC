#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <random>

double distancias(double, double, double, double, double, double);
int conteo(double, std::vector<double>);

int main() {
	std::ifstream archivo("datos.tsv");
	std::vector<double> RA;
	std::vector<double> DE;
	std::vector<double> rs;

	std::string linea_vacia;
	std::getline(archivo, linea_vacia);
	
	if (archivo.is_open()) {
		std::string linea;
		while (std::getline(archivo, linea)) {
			std::istringstream ss(linea);
			std::vector<double> fila;
			double valor;
			while (ss >> valor) {
				fila.push_back(valor);
				if (ss.peek() == ',') {
					ss.ignore();
				}
			}
			RA.push_back(fila[0]);
			DE.push_back(fila[1]);
			rs.push_back(fila[2]);
		}
		archivo.close();
	} else {
		std::cerr << "No se pudo abrir el archivo." << std::endl;
		return 1;
	}

	std::vector<double> dist0;	//vector que contiene las distancias a nuestra galaxia
	std::vector<double> x;		//coordenadas (x,y,z) de cada galaxia en Mpc
	std::vector<double> y;
	std::vector<double> z;

	const double c = 299792.458;	//vel. de la luz en km/s
	const double H0 = 72;		//cte de Hubble [(km/s)/Mpc]
	
	// distancia[Mpc] = rs * c / H0
	for (int i = 0; i < rs.size(); i++) {
		double valor = rs[i] * c / H0;
		dist0.push_back(valor);

	}

	for (int i = 0; i < rs.size(); i++) {
		double x1 = dist0[i] * cos(DE[i]) * cos(RA[i]);
		double y1 = dist0[i] * cos(DE[i]) * sin(RA[i]);
		double z1 = dist0[i] * sin(DE[i]);
		x.push_back(x1);
		y.push_back(y1);
		z.push_back(z1);
	}

	
	// Calculamos la mayor distancia a la que esta una galaxia
	double max = 0;
	for (const auto& i : dist0) {
		if (i > max) {
			max = i;
		}
	}

	std::cout << "Distancia máxima: " << max << std::endl;
	

	// En este paso defino mi conjunto de galaxias centro
	std::vector<int> galaxias_centro;
	double limite = 150;	//mas alla de esta distancia no tomamos galaxias pues puede
				//haber problemas de borde
	int semilla = 27;
	int cant_galaxias = rs.size();
	int M = 100;		//cantidad de galaxias centro que voy a utilizar 
	int m = 0;
	while (m < M) {
		semilla += 3;		//vario el valor de la semilla para cambiar el nro generado
	//Creo un objeto mt19937 como generador de números utilizando Mersenne twister
		std::mt19937 generador(semilla);
	//Creo una distribucion uniforme para generar numero enteros entre 
	//todos los indices de las galaxias
		std::uniform_int_distribution<int> distribucion(0, cant_galaxias); 
		int num_alt = distribucion(generador);		//Genero un número aleatorio
		if (dist0[num_alt] < limite) {
			galaxias_centro.push_back(num_alt);
			m += 1;
		}
	}
	
	std::vector<std::vector<double>> dtogc;		// vector de vectores que guardara 
							//las distancias a las galaxias centro

	for (const auto& galaxia : galaxias_centro) {
		std::vector<double> fila;
		for (int i = 0; i < cant_galaxias; i++) {
			double valor;
			valor = distancias(x[galaxia], y[galaxia], z[galaxia], x[i], y[i], z[i]);
			fila.push_back(valor);
		}
		dtogc.push_back(fila);
	}

	double r;			//radio variable de las esferas
	const double rmax = 350.;	//limite para los r
	std::vector<std::vector<double>> promedio;
	std::vector<double> C2;
	r = 2;				//valor de inicio

	// En este paso calculo el promedio de la cantidad de galaxias que
	// entraban en cada esfera de radio r. De paso calculo el valor C2(r).
	while (r < rmax) {
		double sum = 0;
		double prom = 0;	//promedio(r) = cant_galaxias * C2(r)
		double c2 = 0;		//valor de C2(r)
		std::vector<double> fila1; //guardo las filas de promedio
		fila1.push_back(r);
		for (const auto& fila : dtogc) {
			int cg;
			cg = conteo(r, fila);
			sum += cg;
		}
		prom = sum / 100.;
		c2 = prom / cant_galaxias;
		fila1.push_back(prom);
		promedio.push_back(fila1);
		C2.push_back(c2);
		r += 2;
	}
	
	// En este paso calculo D2(r)
	std::vector<std::vector<double>> D2;
	int cant_datosr = C2.size();
	r = 2;
	for (int i = 0; i < cant_datosr - 1; i++) {
		std::vector<double> fila;
		double d2 = 0;
		fila.push_back(r);
		d2 = (log10(C2[i+1])-log10(C2[i]))/(log10(i+1)-log10(i));
		fila.push_back(d2);
		D2.push_back(fila);
		r += 2;
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

double distancias(double x0, double y0, double z0, double x, double y, double z) {
	double dist;

	dist = sqrt(pow(x-x0,2) + pow(y-y0,2) + pow(z-z0,2));

	return dist;
}

int conteo(double radio, std::vector<double> distancias) {
	int cantidad;
	const double h = 0.6767;
	cantidad = 0;

	for (const auto& valor : distancias) {
		if (valor < radio/h and valor != 0) {
			cantidad += 1;
		}
	}
	
	return cantidad;
}                                                                                                                                                                                                                                                
