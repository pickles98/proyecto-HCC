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

	//for (const auto& valor : dist) {
		//std:: cout << valor << std::endl;
	//}

	double diag(x, x0, y, y0, z, z0) {
		double x, y, z;
		double x0, y0, z0;
		double d;
		d = sqrt(pow(x-x0, 2) + pow(y-y0, 2) + pow(z-z0, 2));
		return d;
	}
	int dimension = rs.size()
	int semilla = 42;
	std::mt19937 generador(semilla);
	std::uniform_int_distribution<int> distribucion(1, dimension);
	int nro_aleatorio = distribucion(generador);



	return 0;
}
