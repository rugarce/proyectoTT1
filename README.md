# Proyecto TT1 

Este repositorio contiene el código y documentación del proyecto de la asignatura.

## 📂 Estructura del repositorio

- `src/` → Contiene la implementación de la clase `Matrix`.
- `docs/` → Contiene la documentación generada con Doxygen.
- `LICENSE` → Archivo con la licencia del proyecto.
- `.editorconfig` → Configuración de formato de código.
- `README.md` → Este archivo, con la descripción del repositorio.


## Instrucción de compilación de la aplicación: 
g++ tests/EKF_GEOS3.cpp src/*cpp -lm -std=c++23 -o bin/main.exe
cd bin
main.exe
pause
## Instrucción de compilación para los test unitarios:
g++ tests/tests.cpp src/*.cpp -lm -std=c++23 -o bin/tests.exe
cd bin
tests.exe
pause 
