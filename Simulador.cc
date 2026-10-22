/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Complejidad Computacional
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    8/10/2026
 * @brief   Programar un simulador de un autómata con pila
*/

#include "includes/LectorDeArchivo.h"
#include "includes/MaquinaTuring.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  std::string archivo_config = "";
  for (int i = 0; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-config") {
      if (i + 1 < argc) {
        archivo_config = argv[i + 1];
        i++;
      } else {
        std::cerr << "ERROR: No se especificó el archivo después de -config" << std::endl;
        return 2;
      }
    }
  }
  if (archivo_config.empty()) {
    std::cerr << "ERROR: Uso: " << argv[0] << " -config <nombre_archivo>" << std::endl;
    return 2;
  }
  std::cout << "Archivo recibido: " << archivo_config << std::endl;
  MaquinaTuring maquina;
  try {
    LectorDeArchivo lector(archivo_config);
    maquina = lector.getMaquinaTuring();
    std::cout << "Autómata cargado correctamente desde el archivo." << std::endl;
    maquina.showMaquinaTuring();
  } catch (const std::exception& e) {
    std::cerr << "ERROR: Error al procesar el archivo: " << e.what() << std::endl;
    return 3;
  }

  while (true) {
    try {
      std::string cadenaEntrada;
      std::cout << "Ingrese la cadena de entrada: ";
      std::cin >> cadenaEntrada;
      if (cadenaEntrada == "exit" || cadenaEntrada == "quit" || cadenaEntrada == "salir" || cadenaEntrada == "q") {
        std::cout << "Saliendo del programa." << std::endl;
        break;
      }
      if (maquina.ejecutar(cadenaEntrada)) {
        std::cout << "La cadena es aceptada por el autómata." << std::endl;
      } else {
        std::cout << "La cadena no es aceptada por el autómata." << std::endl;
      }
      maquina.mostrarCintas();
    } catch (const std::exception& e) {
      std::cerr << "ERROR: Error al procesar la cadena de entrada: " << e.what() << std::endl;
      return 4;
    }
  }   
  
  return 0;
}