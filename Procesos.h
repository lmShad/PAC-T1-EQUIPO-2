// Integrante 1: Jose Miguel Castellanos Martinez
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
