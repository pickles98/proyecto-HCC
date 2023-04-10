#include<vector>
#include<sstream>
#include<fstream>
#include<string>

// Esta funcion lee los datos de un archivo y los
// guarda en una matriz.
std::vector<std::vector<double>> lectura(
		std::ifstream& archivo, char sep) {
	//std::ifstream archivo;
	std::vector<std::vector<double>> datos;
	std::string linea;

	while (std::getline(archivo, linea)) {
		std::istringstream ss(linea);
		std::vector<double> fila;
		double valor;
		while (ss >> valor) {
			fila.push_back(valor);
			if (ss.peek() == sep) {
				ss.ignore();
			}
		}
		datos.push_back(fila);
	}

	return datos;
}

// Esta funcion guarda datosi de una matriz en un archivo.
//int (std::vector<std::vector<double>> matriz) {
//	std::ofstream archivo_salida("archivo_salida"+num+".dat");
//	for (const auto& fila : matriz) {
//		for (const auto& valor : fila) {
//			archivo_salida << valor << " ";
//		}
//		archivo_salida << std::endl;
//	}
//	return 1;
//}
