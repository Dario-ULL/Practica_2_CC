/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Complejidad Computacional
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    21/10/2026
 * @brief   Programar un simulador de un autómata con pila
*/

#pragma once

#include "Transicion.h"
#include "MaquinaTuring.h"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>
#include <set>

class LectorDeArchivo {
  public:
    LectorDeArchivo(std::string nombreArchivo);
    ~LectorDeArchivo() = default;

    bool obtenerSiguienteLineaValida(std::ifstream& archivo, std::string& linea);
    MaquinaTuring getMaquinaTuring() const { return automata_; }
  private:
    bool validar() const; 
    MaquinaTuring automata_;
};