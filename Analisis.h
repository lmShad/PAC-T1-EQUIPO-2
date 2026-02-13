// Integrante 2: Jonathan Emir Jacobo Martinez
#ifndef ANALISIS_H
#define ANALISIS_H

#include "Procesos.h"
#include <string>
#include <vector>

enum class NivelRiesgo { BAJO, MEDIO, ALTO };

struct ProcesoSospechoso {
    Proceso proceso;
    std::string razon;
    NivelRiesgo nivel;
};

std::vector<ProcesoSospechoso> analizarProcesos(
    const Proceso* procesos,
    int cantidadTotal,
    int modo,
    const std::vector<std::string>& sospechososUsuario,
    size_t umbralMemoriaMB = 200
);

#endif
