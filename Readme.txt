# A* Escape

Videojuego de laberinto desarrollado en **C++** utilizando **SFML 3.1.0** y el algoritmo de búsqueda de caminos **A***.

El objetivo del juego es llegar al cuadro verde antes de que los enemigos te alcancen. El jugador cuenta con **3 vidas** y existen **dos enemigos móviles** que utilizan A* para encontrar el camino hacia el jugador.

---

## 🎮 Características

* Laberinto con obstáculos.
* Implementación del algoritmo **A***.
* Dos enemigos que persiguen al jugador.
* Sistema de **3 vidas**.
* Detección de colisiones.
* Pantalla de **WIN** al llegar a la meta.
* Pantalla de **GAME OVER** al perder las 3 vidas.
* Mensajes de finalización mediante archivos `.txt`.
* Música de fondo.
* Movimiento controlado del jugador.
* Proyecto estructurado con **CMake**.

---

# 🕹️ Cómo jugar

## Objetivo

Comienza controlando el jugador azul.

Debes atravesar el laberinto y llegar al:

🟢 **cuadro verde**

Mientras avanzas, dos enemigos rojos intentarán atraparte:

🔴 **Enemigo 1**
🔴 **Enemigo 2**

Cada enemigo calcula su camino hacia el jugador mediante el algoritmo **A***.

---

## Controles

| Tecla | Acción          |
| ----- | --------------- |
| `W`   | Mover arriba    |
| `S`   | Mover abajo     |
| `A`   | Mover izquierda |
| `D`   | Mover derecha   |

El jugador solamente puede desplazarse por las celdas libres del laberinto.

---

# ❤️ Sistema de vidas

El jugador comienza con:

**3 vidas**

Cuando un enemigo ocupa la misma casilla que el jugador:

```text
Jugador + Enemigo
       ↓
Pierdes 1 vida
```

Después de recibir un golpe:

* Se descuenta una vida.
* El jugador regresa al inicio.
* Los enemigos regresan a sus posiciones iniciales.
* Se activa un pequeño tiempo de protección.

Ejemplo:

```text
Vidas: 3
   ↓
Vidas: 2
   ↓
Vidas: 1
   ↓
Vidas: 0
```

Al llegar a `0` vidas aparece la pantalla:

```text
GAME OVER
```

---

# 🏆 Victoria

Para ganar solamente tienes que llegar al cuadro verde.

```text
🔵 Jugador
   ↓
🟢 Meta
```

Cuando el jugador entra en la casilla de la meta:

* Los enemigos dejan de moverse.
* La música se detiene.
* Aparece el mensaje de victoria.
* La ventana cambia a:

```text
A* Escape - YOU WIN
```

El contenido de la pantalla de victoria se carga desde:

```text
assets/win.txt
```

---

# 💀 Game Over

Cuando se pierden las 3 vidas:

* Los enemigos dejan de moverse.
* La música se detiene.
* Aparece el mensaje de derrota.
* La ventana cambia a:

```text
A* Escape - GAME OVER
```

El diseño ASCII se carga desde:

```text
assets/gameover.txt
```

Puedes modificar ese archivo para cambiar el diseño de la pantalla.

---

# 🧠 Algoritmo A*

Cada enemigo utiliza el algoritmo **A*** para buscar el camino hacia el jugador.

El algoritmo utiliza:

```text
f(n) = g(n) + h(n)
```

donde:

* `g(n)` = costo desde el inicio hasta la posición actual.
* `h(n)` = estimación de la distancia hasta el objetivo.
* `f(n)` = costo total estimado.

En este proyecto se utiliza una distancia Manhattan como heurística.

El algoritmo analiza únicamente las celdas transitables del laberinto.

---

# 🛠️ Tecnologías utilizadas

* **C++17**
* **SFML 3.1.0**
* **CMake**
* **Ninja**
* **GCC / G++ 16.2.0**
* **GDB**
* Algoritmo **A***
* Visual Studio Code

---

# 💻 Instalación

## 1. Instalar Visual Studio Code

Descarga e instala:

https://code.visualstudio.com/

Extensiones recomendadas:

* **C/C++** de Microsoft
* **CMake Tools** de Microsoft

---

## 2. Instalar MSYS2

Descarga:

https://www.msys2.org/

Utiliza la terminal:

```text
MSYS2 UCRT64
```

---

## 3. Actualizar MSYS2

En la terminal UCRT64:

```bash
pacman -Syu
```

Si vuelve a pedir una actualización, vuelve a ejecutar el comando.

---

## 4. Instalar GCC

En MSYS2 UCRT64:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

Comprobar:

```bash
g++ --version
```

El proyecto fue probado con GCC 16.2.0.

También puede comprobarse:

```bash
which g++
```

Resultado esperado:

```text
/ucrt64/bin/g++
```

---

## 5. Instalar GDB

```bash
pacman -S mingw-w64-ucrt-x86_64-gdb
```

Comprobar:

```bash
gdb --version
```

y:

```bash
which gdb
```

---

## 6. Instalar CMake

```bash
pacman -S mingw-w64-ucrt-x86_64-cmake
```

Comprobar:

```bash
cmake --version
```

---

# 📚 Instalar SFML 3.1.0

Descarga e instala SFML 3.1.0.

En este proyecto se utiliza la siguiente estructura:

```text
SFML-3.1.0
├── bin
├── include
└── lib
```

El proyecto está configurado para buscar SFML en:

```text
C:\Users\danie\Documents\libreries\SFML-3.1.0
```

Si SFML se encuentra en otra ubicación, cambia `SFML_DIR` en `CMakeLists.txt`.

---

# 📁 Estructura del proyecto

```text
AStarGame
│
├── assets
│   ├── medieval.wav
│   ├── win.txt
│   ├── gameover.txt
│   └── consola.ttf
│
├── include
│   ├── AStar.h
│   ├── Game.h
│   └── Grid.h
│
├── src
│   ├── AStar.cpp
│   ├── Game.cpp
│   ├── Grid.cpp
│   └── main.cpp
│
├── build
│
└── CMakeLists.txt
```

---

# 🎵 Archivos multimedia

## Música

La música se encuentra en:

```text
assets/medieval.wav
```

El juego la carga mediante:

```cpp
music.openFromFile("assets/medieval.wav");
```

La música se repite automáticamente mientras juegas.

El volumen actual está configurado en:

```cpp
music.setVolume(30.0f);
```

---

## Pantallas ASCII

La pantalla de victoria está almacenada en:

```text
assets/win.txt
```

La pantalla de derrota está almacenada en:

```text
assets/gameover.txt
```

Esto permite modificar el diseño sin modificar el código fuente.

---

## Fuente

Para mostrar el ASCII dentro de la ventana se utiliza:

```text
assets/consola.ttf
```

Se recomienda una fuente monoespaciada para conservar correctamente la forma del ASCII.

---

# 🔨 Compilar el proyecto

Abre una terminal de PowerShell en:

```text
C:\Users\danie\Desktop\AStarGame
```

## Primera configuración

Eliminar la carpeta `build` si existe:

```powershell
Remove-Item -Recurse -Force .\build -ErrorAction SilentlyContinue
```

Configurar CMake:

```powershell
C:\msys64\ucrt64\bin\cmake.exe -S . -B build -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe
```

Compilar:

```powershell
C:\msys64\ucrt64\bin\cmake.exe --build build
```

---

# ▶️ Ejecutar

Una vez compilado:

```powershell
.\build\AStarGame.exe
```

El ejecutable se encuentra en:

```text
build\AStarGame.exe
```

---

# 🧩 Problemas comunes

## El `.exe` no abre

Si Windows cierra inmediatamente el programa, puede faltar alguna DLL de SFML.

Las DLL de la versión Debug utilizadas por el proyecto son:

```text
sfml-audio-d-3.dll
sfml-graphics-d-3.dll
sfml-system-d-3.dll
sfml-window-d-3.dll
```

Estas se encuentran normalmente en:

```text
SFML-3.1.0\bin
```

Deben encontrarse junto al ejecutable:

```text
build
├── AStarGame.exe
├── sfml-audio-d-3.dll
├── sfml-graphics-d-3.dll
├── sfml-system-d-3.dll
└── sfml-window-d-3.dll
```

También se utilizan las DLL de runtime de UCRT64:

```text
libstdc++-6.dll
libgcc_s_seh-1.dll
```

---

## La música no se escucha

Comprueba que exista:

```text
build\assets\medieval.wav
```

y que `Game.cpp` utilice:

```cpp
music.openFromFile("assets/medieval.wav");
```

También verifica que el volumen no esté en `0`:

```cpp
music.setVolume(30.0f);
```

---

## El ASCII no aparece

Comprueba que existan:

```text
build\assets\win.txt
build\assets\gameover.txt
build\assets\consola.ttf
```

La fuente debe ser compatible y preferentemente monoespaciada.

---

# 📌 Resumen rápido

Instalar:

```text
Visual Studio Code
MSYS2 UCRT64
GCC
GDB
CMake
SFML 3.1.0
```

Abrir:

```text
C:\Users\danie\Desktop\AStarGame
```

Configurar:

```powershell
C:\msys64\ucrt64\bin\cmake.exe -S . -B build -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe
```

Compilar:

```powershell
C:\msys64\ucrt64\bin\cmake.exe --build build
```

Ejecutar:

```powershell
.\build\AStarGame.exe
```

Controles:

```text
W = arriba
S = abajo
A = izquierda
D = derecha
```

Objetivo:

```text
Llega al cuadro verde antes de perder tus 3 vidas.
```

---

# 👨‍💻 Autor

**Luis Daniel Brambila Ramos**

Proyecto académico de programación en C++ y algoritmos de búsqueda.

**Tecnologías principales:**

```text
C++
SFML
CMake
A*
```
