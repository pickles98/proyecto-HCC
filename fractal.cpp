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

	//for (const auto& valor : RA) {
		//std::cout << valor << std::endl;
	//}

	std::vector<double> dist0;
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;

	const double c = 299792.458;
	const double H0 = 72;

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

	//for (const auto& valor : x) {
	//	std:: cout << valor << std::endl;
	//}
	
	// Calculamos la mayor distancia a la que esta una galaxia
	double max = 0;
	for (const auto& i : dist0) {
		if (i > max) {
			max = i;
		}
	}

	std::cout << "Distancia máxima: " << max << std::endl;
	

	std::vector<int> galaxias_centro;
	// Ahora definimos la condición que debe tener una galaxia para poder ser centro
	int M = 0;
	double limite = 360;
	int semilla = 27;
	int cant_galaxias = rs.size();
	while (M < 100) {
		// Genero un número aleatorio utilizando la libreria random
		// Defino mi semilla
		semilla += 27;
		//Creo un objeto mt19937 como generador de números utilizando Mersenne twister
		std::mt19937 generador(semilla);
		//Creo una distribucion uniforme para generar numero enteros entre todos los indices de las galaxias
		std::uniform_int_distribution<int> distribucion(0, cant_galaxias); 
		//Genero un número aleatorio
		int num_alt = distribucion(generador);
		if (dist0[num_alt] < limite) {
			galaxias_centro.push_back(num_alt);
			M += 1;
		}
	}
	
	//std::mt19937 generador(semilla);
	//std::uniform_int_distribution<int> distribucion(0, cant_galaxias);
	//int num_alt = distribucion(generador);

	//std::cout << "numero aleatorio: " << num_alt << std::endl;
	
	for (const auto& galaxia : galaxias_centro) {
		std::cout << galaxia << " " << dist0[galaxia] << std::endl;
	}
	
	std::vector<std::vector<double>> dtogc;		// vector de vectores que guardara las distancias a las galaxias centro

	//for (int i = 0; i < cant_galaxias; i++) {
	//	std::vector<double> fila;
	//	for (const auto& galaxia : galaxias_centro) {
	//		double valor;
	//		valor = distancias(x[galaxia], y[galaxia], z[galaxia], x[i], y[i], z[i]);
	//		fila.push_back(valor);
	//	}
	//	dtogc.push_back(fila);
	//}

	for (const auto& galaxia : galaxias_centro) {
		std::vector<double> fila;
		for (int i = 0; i < cant_galaxias; i++) {
			double valor;
			valor = distancias(x[galaxia], y[galaxia], z[galaxia], x[i], y[i], z[i]);
			fila.push_back(valor);
		}
		dtogc.push_back(fila);
	}

	//std::ofstream archivo_salida("distancias.dat");
	
	//for (const auto& fila : dtogc) {
	//	for (const auto & valor : fila) {
	//		archivo_salida << valor << "|";
	//	}
	//	archivo_salida << std::endl;
	//}
	//archivo_salida.close();
	//std::cout << "Archivo de salida listo." << std::endl;
	
	//std::vector<std::vector<int>> suma;
	double r;
	double rmax;
	std::vector<std::vector<double>> cont;
	rmax = 200.;
	r = 2;
	while (r < rmax) {
		std::vector<double> radios;
		radios.push_back(r);
		double sum = 0;
		for (const auto& fila : dtogc) {
			int cg;
			cg = conteo(r, fila);
			sum += cg;
		}
		sum = sum / 100.;
		radios.push_back(sum);
		//suma.push_back(radios);
		cont.push_back(radios);
		r += 2;
	}
	
	std::ofstream archivo_salida("conteos.dat");
	//archivo_salida << std::right;
	//std::vector<std::string> titulos;
	//titulos = {"galaxia1", "galaxia2", "galaxia3", "galaxia4", "galaxia5", "galaxia6", "galaxia7", "galaxia8", "galaxia9", "galaxia10"};
	
	//archivo_salida << " " << "|" << " galaxia_1 " << "|" << " galaxia_2 " << "|" << " galaxia_3 " << "|" << " galaxia_4 " << "|" << " galaxia_5 " << "|" << " galaxia_6 " << "|" << " galaxia_7 " << "|" << " galaxia_8 " << "|" << " galaxia_9 " << "|" << " galaxia 10" << std::endl;
	//archivo_salida << "radio" << " ";
	//for (int i=0; i<10; i++) {
	//	archivo_salida << titulos[i] << " ";
	//}
	//archivo_salida << std::endl;
	//archivo_salida << titulos[9] << std::endl;

	//for (const auto& fila : suma) {
	//	for (const auto& valor : fila) {
	//		archivo_salida << valor << " ";
	//	}
	//	archivo_salida << std::endl;
	//}
	//archivo_salida.close();
	//
	
	archivo_salida << std::right;
	archivo_salida << "radio" << " " << "cant.prom.gal." << std::endl;
	for (const auto& fila : cont) {
		for (const auto& valor : fila) {
			archivo_salida << valor << " ";
		}
		archivo_salida << std::endl;
	}
	archivo_salida.close();
	std::cout << "Archivo de salida listo." << std::endl;
	
	return 0;
}

double distancias(double x0, double y0, double z0, double x, double y, double z) {
	double dist;

	dist = sqrt(pow(x-x0,2) + pow(y-y0,2) + pow(z-z0,2));

	return dist;
}

int conteo(double radio, std::vector<double> distancias) {
	int cantidad;
	
	cantidad = 0;

	for (const auto& valor : distancias) {
		if (valor < radio) {
			cantidad += 1;
		}
	}
	
	return cantidad;
}                                                                                                                                                                                                                                                
