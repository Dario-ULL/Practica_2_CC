# Práctica 2: Simulador de Máquina de Turing Determinista Multicinta

**Asignatura:** Complejidad Computacional  
**Curso:** 2026/2027  
**Institución:** Escuela Superior de Ingeniería y Tecnología (ESIT), Universidad de La Laguna  
**Alumno** Darío Domínguez González
---

## 1. Opciones de Implementación Seleccionadas

Conforme a las variantes solicitadas en el enunciado de la práctica, se ha seleccionado la siguiente opciones:

* **Movimientos permitidos:** Izquierda (`L`), Derecha (`R`) y Sin movimiento / Estático (`S`).

---

## 2. Estructura del Proyecto

El proyecto sigue una estructura modular orientada a objetos en C++:

```text
.
├── Simulador.cc
├── Makefile
├── README.md
├── build/
├── data/
│   ├── mt_ejemplo1.txt
│   ├── mt_ejemplo2.txt
├── include/
│   ├── Cinta.hpp
│   ├── LectorDeArchivo.hpp
│   ├── MaquinaTuring.hpp
│   └── Transicion.hpp
└── src/
    ├── Cinta.cpp
    ├── LectorDeArchivo.cpp
    └── MaquinaTuring.cpp
```

---

## 3. Máquinas de Turing Diseñadas

### Problema 1: Reconocedor del lenguaje $L = \{ a^n b^m \mid m \ge n, n > 0 \}$
* **Fichero de configuración:** `data/mt_ejemplo1.txt`
* **Imagen del grafo:** `data/grafo_mt1.png`
* **Descripción:** MT determinista de 2 cintas. Exige al menos una `a` inicial, copiando las `a` en la Cinta 2. Al leer las `b` en la Cinta 1, retrocede en la Cinta 2 emparejando símbolos para verificar que $m \ge n$.

### Problema 2: Transformador de cadenas sobre $\{a, b\}^*$ a unario
* **Fichero de configuración:** `data/mt_ejemplo2.txt`
* **Imagen del grafo:** `data/grafo_mt2.png`
* **Descripción:** MT determinista de 2 cintas. Cuenta las apariciones de `b` seguidas del separador blanco `.` y el recuento de apariciones de `a` codificadas en unario ($1^k$, o `0` si la cantidad es cero). Al finalizar la computación, el resultado queda en la primera cinta y la cabeza de L/E se ubica en el primer símbolo del resultado.

---

## 4. Compilación y Ejecución

### Compilación (usando g++ / C++17)
```bash
make
# o directamente:
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o simulador
```

### Ejecución
El programa acepta los parámetros por línea de comandos requeridos:

**Entrada interactiva por teclado:**
 ```bash
 ./simulador -config mt_ejemplo1.txt
 ```
