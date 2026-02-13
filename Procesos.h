// Integrante 1: [Escribe aquí tu nombre]
#ifndef PROCESOS_H
#define PROCESOS_H

#include <string>

struct Proceso {
    unsigned long pid;
    std::string nombre;
    size_t memoriaKB;
};

Proceso* obtenerProcesosActivos(int& cantidadTotal);
void liberarMemoriaProcesos(Proceso* lista);

#endif
