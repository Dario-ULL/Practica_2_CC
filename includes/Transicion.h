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

#include <vector>
#include <string>
#include <iostream>

struct Transicion {
  std::vector<std::string> simbolosLeidos_;
  std::string estadoDestino_;
  std::vector<std::string> simbolosEscritos_;
  std::vector<std::string> movimientos_;

  Transicion() = default;

  Transicion(const std::vector<std::string>& leidos,
             const std::string& estadoDestino,
             const std::vector<std::string>& escritos,
             const std::vector<std::string>& movimientos)
      : simbolosLeidos_(leidos),
        estadoDestino_(estadoDestino),
        simbolosEscritos_(escritos),
        movimientos_(movimientos) {}

  void showTransicion() const {
    std::cout << "Transición: (";
    for (size_t i = 0; i < simbolosLeidos_.size(); ++i) {
      std::cout << simbolosLeidos_[i] << (i + 1 < simbolosLeidos_.size() ? ", " : "");
    }
    std::cout << ") --> " << estadoDestino_ << ", escribe: (";
    for (size_t i = 0; i < simbolosEscritos_.size(); ++i) {
      std::cout << simbolosEscritos_[i] << (i + 1 < simbolosEscritos_.size() ? ", " : "");
    }
    std::cout << "), movs: (";
    for (size_t i = 0; i < movimientos_.size(); ++i) {
      std::cout << movimientos_[i] << (i + 1 < movimientos_.size() ? ", " : "");
    }
    std::cout << ")" << std::endl;
  }
};