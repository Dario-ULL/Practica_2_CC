/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Complejidad Computacional
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    21/10/2026
 * @brief   Programar un simulador de un autómata con pila
*/

#include "../includes/Cinta.h"

Cinta::Cinta(const std::string& simboloBlanco, const std::string& cadenaEntrada)
    : simboloBlanco_(simboloBlanco), posicionCabeza_(0) {
  for (const char& c : cadenaEntrada) {
    contenido_.push_back(std::string(1, c));
  }
  if (contenido_.empty()) {
    contenido_.push_back(simboloBlanco_);
  }
}


std::string 
Cinta::leer() const {
  if (posicionCabeza_ >= 0 && posicionCabeza_ < static_cast<int>(contenido_.size())) {
    return contenido_[posicionCabeza_];
  }
  return simboloBlanco_;
}

void 
Cinta::escribir(const std::string& simbolo) {
  if (posicionCabeza_ < 0 || posicionCabeza_ >= static_cast<int>(contenido_.size())) {
    throw std::out_of_range("Posición de la cabeza fuera de rango.");
  }
  asegurarEspacio();
  contenido_[posicionCabeza_] = simbolo;
}


void 
Cinta::mover(const std::string& movimiento) {
  if (movimiento == "R") {
    posicionCabeza_++;
  } else if (movimiento == "L") {
    posicionCabeza_--;
  }
  asegurarEspacio();
}


void 
Cinta::reiniciar(const std::string& cadenaEntrada) {
  contenido_.clear();
  for (const char& c : cadenaEntrada) {
    contenido_.push_back(std::string(1, c));
  }
  if (contenido_.empty()) {
    contenido_.push_back(simboloBlanco_);
  }
  posicionCabeza_ = 0;
}


std::string 
Cinta::obtenerRepresentacion() const {
std::string resultado = "";
  for (int i = 0; i < static_cast<int>(contenido_.size()); ++i) {
    if (i == posicionCabeza_) {
      resultado += "[" + contenido_[i] + "]";
    } else {
      resultado += contenido_[i];
    }
  }
  return resultado;
}

void 
Cinta::asegurarEspacio() {
  if (posicionCabeza_ < 0) {
    contenido_.push_front(simboloBlanco_);
    posicionCabeza_ = 0;
  } else if (posicionCabeza_ >= static_cast<int>(contenido_.size())) {
    contenido_.push_back(simboloBlanco_);
  }
}