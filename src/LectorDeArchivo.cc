/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Complejidad Computacional
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    21/10/2026
 * @brief   Programar un simulador de un autómata con pila
*/

#include "../includes/LectorDeArchivo.h"

namespace fs = std::filesystem;

LectorDeArchivo::LectorDeArchivo(std::string nombreArchivo) {
  if (nombreArchivo.rfind("data/", 0) != 0) {
    nombreArchivo = "data/" + nombreArchivo;
  }
  std::ifstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo: " + nombreArchivo);
  }

  std::set<std::string> conjuntoEstados;
  std::set<std::string> conjuntoAlfabeto;
  std::set<std::string> conjuntoCinta;
  std::string estadoInicial;
  std::string simboloBlanco;
  std::set<std::string> conjuntoEstadosFinales;
  int numeroCintas = 1;
  std::multimap<std::string, Transicion> transiciones;

  std::string linea;
  std::string aux;
  // 1. Conjunto Q (Estados)
  if (!obtenerSiguienteLineaValida(archivo, linea)) {
    throw std::runtime_error("Error: Archivo incompleto (falta conjunto Q)");
  }
  std::istringstream issEstados(linea);
  while (issEstados >> aux) {
    conjuntoEstados.insert(aux);
  }
  // 2. Conjunto Sigma (Alfabeto de entrada)
  if (!obtenerSiguienteLineaValida(archivo, linea)) {
    throw std::runtime_error("Error: Archivo incompleto (falta conjunto Sigma)");
  }
  std::istringstream issAlfabeto(linea);
  while (issAlfabeto >> aux) {
    conjuntoAlfabeto.insert(aux);
  }

  // 3. Conjunto Gamma (Alfabeto de la cinta)
  if (!obtenerSiguienteLineaValida(archivo, linea)) {
    throw std::runtime_error("Error: Archivo incompleto (falta conjunto Gamma)");
  }
  std::istringstream issCinta(linea);
  while (issCinta >> aux) {
    conjuntoCinta.insert(aux);
  }
  // 4. Estado inicial
  if (!obtenerSiguienteLineaValida(archivo, linea)) {
    throw std::runtime_error("Error: Archivo incompleto (falta estado inicial)");
  }
  std::istringstream issEstadoInicial(linea);
  issEstadoInicial >> estadoInicial;
  // 5. Símbolo blanco
  if (!obtenerSiguienteLineaValida(archivo, linea)) {
    throw std::runtime_error("Error: Archivo incompleto (falta símbolo blanco)");
  }
  std::istringstream issBlanco(linea);
  issBlanco >> simboloBlanco;
  // 6. Conjunto F (Estados finales/aceptación)
  if (!obtenerSiguienteLineaValida(archivo, linea)) {
    throw std::runtime_error("Error: Archivo incompleto (falta conjunto F)");
  }
  std::istringstream issFinales(linea);
  while (issFinales >> aux) {
    conjuntoEstadosFinales.insert(aux);
  }
  // 7. Número de cintas
  if (!obtenerSiguienteLineaValida(archivo, linea)) {
    throw std::runtime_error("Error: Archivo incompleto (falta número de cintas)");
  }
  std::istringstream issNumCintas(linea);
  if (!(issNumCintas >> numeroCintas) || numeroCintas < 1) {
    throw std::runtime_error("Error: Número de cintas inválido: " + linea);
  }
  // 8. Transiciones multicinta
  while (obtenerSiguienteLineaValida(archivo, linea)) {
    std::istringstream issTransicion(linea);
    std::string estadoActual;
    std::string estadoDestino;
    std::vector<std::string> simbolosLeidos(numeroCintas);
    std::vector<std::string> simbolosEscritos(numeroCintas);
    std::vector<std::string> movimientos(numeroCintas);
    if (!(issTransicion >> estadoActual)) {
      throw std::runtime_error("Error en transición (falta estado actual): " + linea);
    }
    for (int i = 0; i < numeroCintas; ++i) {
      if (!(issTransicion >> simbolosLeidos[i])) {
        throw std::runtime_error("Error en transición (faltan símbolos leídos): " + linea);
      }
    }
    if (!(issTransicion >> estadoDestino)) {
      throw std::runtime_error("Error en transición (falta estado destino): " + linea);
    }
    for (int i = 0; i < numeroCintas; ++i) {
      if (!(issTransicion >> simbolosEscritos[i])) {
        throw std::runtime_error("Error en transición (faltan símbolos a escribir): " + linea);
      }
    }
    for (int i = 0; i < numeroCintas; ++i) {
      if (!(issTransicion >> movimientos[i])) {
        throw std::runtime_error("Error en transición (faltan movimientos): " + linea);
      }
    }
    transiciones.emplace(estadoActual, Transicion(simbolosLeidos, estadoDestino, simbolosEscritos, movimientos));
  }
  archivo.close();
  automata_ = MaquinaTuring(conjuntoEstados, conjuntoAlfabeto, conjuntoCinta,estadoInicial, simboloBlanco, conjuntoEstadosFinales,numeroCintas, transiciones);
  validar();
}


bool 
LectorDeArchivo::obtenerSiguienteLineaValida(std::ifstream& archivo, std::string& linea) {
  while (std::getline(archivo, linea)) {
    if (!linea.empty() && linea.back() == '\r') {
      linea.pop_back();
    }
    if (linea.empty() || linea[0] == '#') {
      continue;
    }
    return true;
  }
  return false;
}


bool 
LectorDeArchivo::validar() const {
  const auto& conjuntoEstados = automata_.getConjuntoEstados();
  const auto& conjuntoAlfabeto = automata_.getConjuntoAlfabeto();
  const auto& conjuntoCinta = automata_.getConjuntoCinta();
  const auto& conjuntoFinales = automata_.getConjuntoEstadosFinales();
  const std::string& estadoInicial = automata_.getEstadoInicial();
  const std::string& simboloBlanco = automata_.getSimboloBlanco();
  int numeroCintas = automata_.getNumeroCintas();
  // 1. Validar que el estado inicial pertenece a Q
  if (conjuntoEstados.find(estadoInicial) == conjuntoEstados.end()) {
    throw std::runtime_error("Error de validación: El estado inicial '" + estadoInicial + 
                             "' no pertenece al conjunto de estados Q.");
  }
  // 2. Validar que el símbolo blanco pertenece al alfabeto de cinta Gamma 
  if (conjuntoCinta.find(simboloBlanco) == conjuntoCinta.end()) {
    throw std::runtime_error("Error de validación: El símbolo blanco '" + simboloBlanco + 
                             "' no pertenece al alfabeto de cinta Gamma.");
  }
  // 3. Validar que Sigma es subconjunto de Gamma
  for (const auto& simbolo : conjuntoAlfabeto) {
    if (conjuntoCinta.find(simbolo) == conjuntoCinta.end()) {
      throw std::runtime_error("Error de validación: El símbolo '" + simbolo + 
                               "' de Sigma no pertenece al alfabeto de cinta Gamma.");
    }
  }
  // 4. Validar que los estados finales pertenecen a Q
  for (const auto& estadoFinal : conjuntoFinales) {
    if (conjuntoEstados.find(estadoFinal) == conjuntoEstados.end()) {
      throw std::runtime_error("Error de validación: El estado final '" + estadoFinal + 
                               "' no pertenece al conjunto de estados Q.");
    }
  }
  // 5. Validar número de cintas
  if (numeroCintas < 1) {
    throw std::runtime_error("Error de validación: El número de cintas debe ser mayor o igual a 1.");
  }
  // 6. Validar transiciones
  std::set<std::pair<std::string, std::vector<std::string>>> transicionesDefinidas;
  for (const auto& par : automata_.getTransiciones()) {
    const std::string& estadoOrigen = par.first;
    const Transicion& t = par.second;
    // Estado origen en Q
    if (conjuntoEstados.find(estadoOrigen) == conjuntoEstados.end()) {
      throw std::runtime_error("Error en transición: El estado origen '" + estadoOrigen + 
                               "' no está en Q.");
    }
    // Estado destino en Q
    if (conjuntoEstados.find(t.estadoDestino_) == conjuntoEstados.end()) {
      throw std::runtime_error("Error en transición: El estado destino '" + t.estadoDestino_ + 
                               "' no está en Q.");
    }
    // Comprobar tamaños de vectores respecto al número de cintas
    if (static_cast<int>(t.simbolosLeidos_.size()) != numeroCintas ||
        static_cast<int>(t.simbolosEscritos_.size()) != numeroCintas ||
        static_cast<int>(t.movimientos_.size()) != numeroCintas) {
      throw std::runtime_error("Error en transición: La cantidad de símbolos o movimientos no coincide con el número de cintas (" + 
                               std::to_string(numeroCintas) + ").");
    }
    // Símbolos leídos deben pertenecer a Gamma
    for (const auto& s : t.simbolosLeidos_) {
      if (conjuntoCinta.find(s) == conjuntoCinta.end()) {
        throw std::runtime_error("Error en transición: Símbolo leído '" + s + "' no pertenece a Gamma.");
      }
    }
    // Símbolos a escribir deben pertenecer a Gamma
    for (const auto& s : t.simbolosEscritos_) {
      if (conjuntoCinta.find(s) == conjuntoCinta.end()) {
        throw std::runtime_error("Error en transición: Símbolo a escribir '" + s + "' no pertenece a Gamma.");
      }
    }
    // Movimientos permitidos (L, R, S)
    for (const std::string& m : t.movimientos_) {
      if (m != "L" && m != "R" && m != "S") {
        throw std::runtime_error("Error en transición: Movimiento inválido '" + m + 
                                 "'. Solo se permite 'L', 'R' o 'S'.");
      }
    }
    // Comprobación de determinismo: par (estadoOrigen, simbolosLeidos) único
    auto claveDeterminismo = std::make_pair(estadoOrigen, t.simbolosLeidos_);
    if (transicionesDefinidas.find(claveDeterminismo) != transicionesDefinidas.end()) {
      throw std::runtime_error("Error: La máquina no es determinista. Existe más de una transición para el estado '" + 
                               estadoOrigen + "' con la misma combinación de símbolos leídos.");
    }
    transicionesDefinidas.insert(claveDeterminismo);
  }
  return true;
}