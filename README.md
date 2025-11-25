# Gestor_de_genda-de-Contactos

# Lenguaje en el que se desarrollo el sistema es en C++.

# Descripcion: 
El sistema desarrollado es un Gestor de agenda de contactos, que permite registrar, buscar, mostrar y eliminar contactos. La información se almacenará en memoria (no es necesario guardar los datos en archivos o bases de datos). Cada vez que el programa se ejecute, se deberán ingresar nuevamente los datos.

# Pasos para la instalacion y clonacion del repositorio:

1. CLONAR EL REPOSITORIO
Abre tu terminal, navega al directorio deseado y ejecuta:
Sustituye [URL_DEL_REPOSITORIO] por la URL HTTPS o SSH del proyecto en GitHub.
git clone [URL_DEL_REPOSITORIO]

2. ACCEDER AL DIRECTORIO
Sustituye [NOMBRE_DEL_REPOSITORIO] por el nombre de la carpeta recién creada.
cd [NOMBRE_DEL_REPOSITORIO]

3. COMPILACIÓN USANDO CMAKE (Flujo recomendado para C++)
Esto crea una carpeta "build" para mantener limpios los archivos fuente.

Crear y acceder al directorio de construcción
mkdir build
cd build

Generar los archivos del sistema de construcción (ej. Makefile)
Los dos puntos ".." indican a CMake que busque el archivo CMakeLists.txt en el directorio padre.
cmake ..

Compilar el proyecto usando 'make'
make

(Opcional) Volver al directorio raíz para la ejecución
cd ..

4. EJECUTAR EL PROGRAMA (Si la compilación fue exitosa)
Sustituye [NOMBRE_DEL_EJECUTABLE] por el nombre del archivo de salida que se generó (generalmente el nombre del proyecto o el especificado en CMakeLists.txt)../[NOMBRE_DEL_EJECUTABLE]

# Licencia MIT.
