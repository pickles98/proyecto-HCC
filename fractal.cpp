#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <random>

int main() {
	std::ifstream archivo("asu1.tsv");
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

	std::vector<double> dist;
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;

	const double c = 299792.458;
	const double H0 = 72;

	for (int i = 0; i < rs.size(); i++) {
		double valor = rs[i] * c / H0;
		dist.push_back(valor);

	}

	for (int i = 0; i < rs.size(); i++) {
		double x1 = dist[i] * cos(DE[i]) * cos(RA[i]);
		double y1 = dist[i] * cos(DE[i]) * sin(RA[i]);
		double z1 = dist[i] * sin(DE[i]);
		x.push_back(x1);
		y.push_back(y1);
		z.push_back(z1);
	}

	//for (const auto& valor : x) {
	//	std:: cout << valor << std::endl;
	//}
	
	// Calculamos la mayor distancia a la que esta una galaxia
	double max = 0;
	for (const auto& i : dist) {
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
	while (M < 10) {
		// Genero un número aleatorio utilizando la libreria random
		// Defino mi semilla
		semilla += 27;
		//Creo un objeto mt19937 como generador de números utilizando Mersenne twister
		std::mt19937 generador(semilla);
		//Creo una distribucion uniforme para generar numero enteros entre todos los indices de las galaxias
		std::uniform_int_distribution<int> distribucion(0, cant_galaxias); 
		//Genero un número aleatorio
		int num_alt = distribucion(generador);
		if (dist[num_alt] < limite) {
			galaxias_centro.push_back(num_alt);
			M += 1;
		}
	}
	
	//std::mt19937 generador(semilla);
	//std::uniform_int_distribution<int> distribucion(0, cant_galaxias);
	//int num_alt = distribucion(generador);

	//std::cout << "numero aleatorio: " << num_alt << std::endl;
	
	for (const auto& galaxia : galaxias_centro) {
		std::cout << galaxia << " " << dist[galaxia] << std::endl;
	}

	

	return 0;
}
