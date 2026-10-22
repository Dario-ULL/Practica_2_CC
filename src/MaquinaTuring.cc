/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Complejidad Computacional
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    21/10/2026
 * @brief   Programar un simulador de un autómata con pila
*/

#include "../includes/MaquinaTuring.h"

MaquinaTuring::MaquinaTuring(const std::set<std::string> &conjuntoEstados,
                             const std::set<std::string> &conjuntoAlfabeto,
                             const std::set<std::string> &conjuntoCinta,
                             const std::string &estadoInicial,
                             const std::string &simboloBlanco,
                             const std::set<std::string> &conjuntoEstadosFinales,
                             const int &numeroCintas,
                             const std::multimap<std::string, Transicion> &transiciones): 
    conjuntoEstados_(conjuntoEstados),
    conjuntoAlfabeto_(conjuntoAlfabeto),
    conjuntoCinta_(conjuntoCinta),
    estadoInicial_(std::move(estadoInicial)),
    simboloBlanco_(std::move(simboloBlanco)),
    conjuntoEstadosFinales_(conjuntoEstadosFinales),
    numeroCintas_(numeroCintas),
    transiciones_(std::move(transiciones)) {}


void
MaquinaTuring::showMaquinaTuring() const {
  const int anchoTotal = 100;
  std::cout << "+" << std::string(anchoTotal - 2, '=') << "+\n";
  std::cout << "|" << std::setw(anchoTotal) << std::left << "                            DEFINICIÓN FORMAL DE LA MÁQUINA DE TURING (M)" << "|\n";
  std::cout << "|" << std::setw(anchoTotal + 1) << std::left << "                                      M = (Q, Σ, Γ, s, b, F, δ)" << "|\n";
  std::cout << "+" << std::string(anchoTotal - 2, '=') << "+\n";
  // 1. Ficha formal de la máquina
  std::cout << std::setw(27) << std::left << "Estados (Q):" << formatearContenedor(conjuntoEstados_) << "\n";
  std::cout << std::setw(28) << std::left << "Alfabeto Entrada (Σ):" << formatearContenedor(conjuntoAlfabeto_) << "\n";
  std::cout << std::setw(28) << std::left << "Alfabeto Cinta (Γ):" << formatearContenedor(conjuntoCinta_) << "\n";
  std::cout << std::setw(27) << std::left << "Estado Inicial (s):" << estadoInicial_ << "\n";
  std::cout << std::setw(28) << std::left << "Símbolo Blanco (b):" << ("'" + simboloBlanco_ + "'") << "\n";
  std::cout << std::setw(27) << std::left << "Estados Finales (F):" << formatearContenedor(conjuntoEstadosFinales_) << "\n";
  std::cout << std::setw(28) << std::left << "Número de Cintas:" << numeroCintas_ << "\n";
  // 2. Cabecera de la tabla de transiciones
  std::cout << "+" << std::string(anchoTotal - 2, '-') << "+\n";
  std::cout << "|" << std::setw(anchoTotal - 1) << std::left << "                                      TABLA DE TRANSICIONES (δ)" << "|\n";
  std::cout << "+" << std::string(anchoTotal - 2, '-') << "+\n";
  // Encabezados de columnas
  std::cout << "| " << std::setw(16) << std::left << "Estado Act."
            << "| " << std::setw(21) << std::left << "Leído"
            << "| " << std::setw(16) << std::left << "Estado Sig."
            << "| " << std::setw(20) << std::left << "Escrito"
            << "| " << std::setw(16) << std::left << "Movimientos"
            << " |\n";
  std::cout << "+" << std::string(17, '-')
            << "+" << std::string(21, '-')
            << "+" << std::string(17, '-')
            << "+" << std::string(21, '-')
            << "+" << std::string(18, '-') << "+\n";
  // 3. Filas con cada transición
  for (const auto& par : transiciones_) {
    const std::string& estadoOrigen = par.first;
    const Transicion& t = par.second;
    std::string leidosStr   = formatearContenedor(t.simbolosLeidos_);
    std::string escritosStr = formatearContenedor(t.simbolosEscritos_);
    std::string movsStr     = formatearContenedor(t.movimientos_);
    std::cout << "| " << std::setw(16) << std::left << estadoOrigen
              << "| " << std::setw(20) << std::left << leidosStr
              << "| " << std::setw(16) << std::left << t.estadoDestino_
              << "| " << std::setw(20) << std::left << escritosStr
              << "| " << std::setw(17) << std::left << movsStr
              << "|\n";
  }
  std::cout << "+" << std::string(17, '-')
            << "+" << std::string(21, '-')
            << "+" << std::string(17, '-')
            << "+" << std::string(21, '-')
            << "+" << std::string(18, '-') << "+\n";
}


template <typename T>
std::string 
MaquinaTuring::formatearContenedor(const T& contenedor) const {
  std::ostringstream oss;
  oss << "{ ";
  bool primero = true;
  for (const auto& elem : contenedor) {
    if (!primero) oss << ", ";
    oss << elem;
    primero = false;
  }
  oss << " }";
  return oss.str();
}


void 
MaquinaTuring::mostrarCintas() const {
  std::cout << "--- Estado final de las cintas ---" << std::endl;
  for (size_t i = 0; i < cintas_.size(); ++i) {
    std::cout << "Cinta " << (i + 1) << ": " 
              << cintas_[i].obtenerRepresentacion() << std::endl;
  }
  std::cout << "----------------------------------\n" << std::endl;
}


void 
MaquinaTuring::inicializarCintas(const std::string& cadenaEntrada) {
  cintas_.clear();
  cintas_.reserve(numeroCintas_);
  cintas_.emplace_back(simboloBlanco_, cadenaEntrada);
  for (int i = 1; i < numeroCintas_; ++i) {
    cintas_.emplace_back(simboloBlanco_, "");
  }
}


bool
MaquinaTuring::ejecutar(std::string cadenaEntrada) {
  inicializarCintas(cadenaEntrada);
  return ejecutarRecursivo(estadoInicial_);
}


bool
MaquinaTuring::ejecutarRecursivo(std::string estadoActual) {
  std::vector<std::string> simbolosLeidos(numeroCintas_);
  for (int i = 0; i < numeroCintas_; ++i) {
    simbolosLeidos[i] = cintas_[i].leer();
  }
  auto rango = transiciones_.equal_range(estadoActual);
  const Transicion* transicionAplicable = nullptr;
  for (auto it = rango.first; it != rango.second; ++it) {
    if (it->second.simbolosLeidos_ == simbolosLeidos) {
      transicionAplicable = &(it->second);
      break;
    }
  }

  if (transicionAplicable == nullptr) {
    return conjuntoEstadosFinales_.find(estadoActual) != conjuntoEstadosFinales_.end();
  }

  for (int i = 0; i < numeroCintas_; ++i) {
    cintas_[i].escribir(transicionAplicable->simbolosEscritos_[i]);
    cintas_[i].mover(transicionAplicable->movimientos_[i]);
  }

  return ejecutarRecursivo(transicionAplicable->estadoDestino_);
}


bool
MaquinaTuring::perteneceConjuntoAlfabetoCadena(const std::string &simbolo) const {
  return conjuntoAlfabeto_.find(simbolo) != conjuntoAlfabeto_.end();
}