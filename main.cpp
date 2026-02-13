// Integrante 4: Juan Carlos Fernandez Flores
#include "Procesos.h"
#include "Analisis.h"
#include "Registro.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits> // Necesario para limpiar el buffer correctamente

int pedirModo() {
    int modo;
    std::cout << "Seleccione el modo de analisis (1 = Basico, 2 = Estricto): ";
    std::cin >> modo;

    if (std::cin.fail() || (modo != 1 && modo != 2)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada invalida. Se usara modo 1 por defecto.\n";
        return 1;
    }
    return modo;
}

std::vector<std::string> pedirSospechosos() {
    std::vector<std::string> lista;
    std::string entrada;
    std::cout << "Ingrese nombres de procesos sospechosos  ";

    std::getline(std::cin, entrada);

    if (entrada.empty()) {
        return lista;
    }

    std::stringstream ss(entrada);
    std::string nombre;

    while (std::getline(ss, nombre, ',')) {
        // Eliminar espacios al inicio si los hay
        while (nombre.length() > 0 && nombre[0] == ' ') {
            nombre.erase(0, 1);
        }
        if (!nombre.empty()) {
            lista.push_back(nombre);
        }
    }
    return lista;
}

void imprimirEnConsola(Proceso* procesos, int cantidad) {
    std::cout << "\n--- LISTA DE PROCESOS ACTIVOS (Muestra parcial) ---\n";
    std::cout << std::left << std::setw(10) << "PID"
              << std::setw(30) << "Nombre"
              << "Memoria (KB)\n";

    int tope = (cantidad > 15) ? 15 : cantidad;

    for (int i = 0; i < tope; i++) {
        std::cout << std::left << std::setw(10) << procesos[i].pid
                  << std::setw(30) << procesos[i].nombre
                  << procesos[i].memoriaKB << "\n";
    }

    if (cantidad > 15) {
        std::cout << "... y " << (cantidad - 15) << " procesos mas ocultos.\n";
    }
}

void imprimirSospechosos(const std::vector<ProcesoSospechoso>& lista) {
    std::cout << "\n--- RESULTADO DEL ANALISIS ---\n";
    if (lista.empty()) {
        std::cout << "Todo limpio. No se detectaron riesgos.\n";
    } else {
        std::cout << "Se encontraron " << lista.size() << " procesos sospechosos:\n";
        for (const auto& item : lista) {
            std::cout << " -> " << item.proceso.nombre
                      << " (Riesgo: ";

            switch(item.nivel) {
                case NivelRiesgo::ALTO: std::cout << "ALTO"; break;
                case NivelRiesgo::MEDIO: std::cout << "MEDIO"; break;
                default: std::cout << "BAJO"; break;
            }

            std::cout << ") - Razon: " << item.razon << "\n";
        }
    }
}

int main() {
    int modo = pedirModo();

    std::string nombreArchivo;
    std::cout << "Nombre del archivo para guardar el reporte (ej. reporte.txt): ";
    std::cin >> nombreArchivo;


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::string> listaUsuario = pedirSospechosos();

    std::cout << "\nLeyendo procesos del sistema...\n";
    int totalProcesos = 0;

    try {
        Proceso* misProcesos = obtenerProcesosActivos(totalProcesos);

        imprimirEnConsola(misProcesos, totalProcesos);

        // Umbral de 200MB (150 * 1024 KB)
        std::vector<ProcesoSospechoso> riesgos = analizarProcesos(misProcesos, totalProcesos, modo, listaUsuario, 150);

        imprimirSospechosos(riesgos);

        guardarReporte(nombreArchivo, misProcesos, totalProcesos, riesgos);

        liberarMemoriaProcesos(misProcesos);
    } catch (const std::exception& e) {
        std::cerr << "Error critico: " << e.what() << "\n";
    }

    std::cout << "\nPrograma terminado.\n";
    // Pausa para que no se cierre la ventana de inmediato
    std::cout << "Presione Enter para salir...";
    std::cin.get();

    return 0;
}
