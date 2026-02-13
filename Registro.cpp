// Integrante 3: Brandon Yahir Flores Garcia.
#include "Registro.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

void guardarReporte(const std::string& nombreArchivo,
                    const Proceso* procesos,
                    int cantidadTotal,
                    const std::vector<ProcesoSospechoso>& sospechosos) {

    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para escritura: " + nombreArchivo);
    }

    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    archivo << "=== REPORTE DE SEGURIDAD DEL SISTEMA ===\n";
    archivo << "Fecha: " << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "\n";
    archivo << "Total escaneados: " << cantidadTotal << "\n";
    archivo << "Amenazas detectadas: " << sospechosos.size() << "\n\n";

    // 1. Lista de Riesgo MEDIO (Lo que pediste resaltar)
    archivo << "=== [!] ALERTAS DE RIESGO MEDIO ===\n";
    bool huboMedio = false;
    for (const auto& s : sospechosos) {
        if (s.nivel == NivelRiesgo::MEDIO) {
            huboMedio = true;
            archivo << "PROCESO: " << s.proceso.nombre << " | PID: " << s.proceso.pid << "\n";
            archivo << "  -> Memoria: " << s.proceso.memoriaKB << " KB\n";
            archivo << "  -> Detalle: " << s.razon << "\n\n";
        }
    }
    if (!huboMedio) archivo << "Sin alertas de riesgo medio.\n\n";

    // 2. Lista de Riesgo ALTO
    archivo << "=== [!!!] ALERTAS DE RIESGO ALTO ===\n";
    bool huboAlto = false;
    for (const auto& s : sospechosos) {
        if (s.nivel == NivelRiesgo::ALTO) {
            huboAlto = true;
            archivo << "PROCESO: " << s.proceso.nombre << " | PID: " << s.proceso.pid << "\n";
            archivo << "  -> Memoria: " << s.proceso.memoriaKB << " KB\n";
            archivo << "  -> Detalle: " << s.razon << "\n\n";
        }
    }
    if (!huboAlto) archivo << "Sin alertas de riesgo alto.\n\n";

    // 3. Inventario Completo
    archivo << "=== INVENTARIO COMPLETO DE PROCESOS ===\n";
    archivo << std::left << std::setw(10) << "PID"
            << std::setw(35) << "Nombre"
            << "Memoria (KB)\n";
    archivo << "--------------------------------------------------------\n";

    for (int i = 0; i < cantidadTotal; ++i) {
        archivo << std::left << std::setw(10) << procesos[i].pid
                << std::setw(35) << procesos[i].nombre
                << procesos[i].memoriaKB << "\n";
    }

    archivo.close();
    std::cout << "Reporte guardado exitosamente en: " << nombreArchivo << "\n";
}
