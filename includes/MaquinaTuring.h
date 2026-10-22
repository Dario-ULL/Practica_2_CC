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
#include "Cinta.h"

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iomanip>

class MaquinaTuring {
 public:
  MaquinaTuring() = default;
  MaquinaTuring(const std::set<std::string> &conjuntoEstados,
                const std::set<std::string> &conjuntoAlfabeto,
                const std::set<std::string> &conjuntoCinta,
                const std::string &estadoInicial,
                const std::string &simboloBlanco,
                const std::set<std::string> &conjuntoEstadosFinales,
                const int &numeroCintas,
                const std::multimap<std::string, Transicion> &transiciones);
  ~MaquinaTuring() = default;

  bool ejecutar(std::string cadenaEntrada);
  void showMaquinaTuring() const;
  template <typename T> std::string formatearContenedor(const T& contenedor) const;
  void mostrarCintas() const;

  std::set<std::string> getConjuntoEstados() const { return conjuntoEstados_; }
  std::set<std::string> getConjuntoAlfabeto() const { return conjuntoAlfabeto_; }
  std::set<std::string> getConjuntoCinta() const { return conjuntoCinta_; }
  std::string getEstadoInicial() const { return estadoInicial_; }
  std::string getSimboloBlanco() const { return simboloBlanco_; }
  std::set<std::string> getConjuntoEstadosFinales() const { return conjuntoEstadosFinales_; }
  int getNumeroCintas() const { return numeroCintas_; }
  std::multimap<std::string, Transicion> getTransiciones() const { return transiciones_; }
 private:
  void inicializarCintas(const std::string& cadenaEntrada);
  bool ejecutarRecursivo(std::string estadoActual); 
  bool perteneceConjuntoAlfabetoCadena(const std::string &simbolo) const;
  std::set<std::string> conjuntoEstados_;
  std::set<std::string> conjuntoAlfabeto_;
  std::set<std::string> conjuntoCinta_;
  std::string estadoInicial_;
  std::string simboloBlanco_;
  std::set<std::string> conjuntoEstadosFinales_;
  int numeroCintas_;
  std::multimap<std::string, Transicion> transiciones_;
  std::vector<Cinta> cintas_;
};