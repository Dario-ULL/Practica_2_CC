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

#include <deque>
#include <string>
#include <stdexcept>

class Cinta {
  public:
    Cinta(const std::string& simboloBlanco, const std::string& cadenaEntrada = "");

    std::string leer() const;
    void escribir(const std::string& simbolo);
    void mover(const std::string& movimiento);
    void reiniciar(const std::string& cadenaEntrada = "");
    std::string obtenerRepresentacion() const;
  private:
    std::deque<std::string> contenido_;
    int posicionCabeza_; 
    std::string simboloBlanco_;

    void asegurarEspacio();
};