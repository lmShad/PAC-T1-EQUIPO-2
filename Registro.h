// Integrante 3: Brandon Yahir Flores Garcia
#ifndef REGISTRO_H
#define REGISTRO_H

#include "Procesos.h"
#include "Analisis.h"
#include <string>
#include <vector>

void guardarReporte(const std::string& nombreArchivo,
                    const Proceso* procesos,
                    int cantidadTotal,
                    const std::vector<ProcesoSospechoso>& sospechosos);

#endif
