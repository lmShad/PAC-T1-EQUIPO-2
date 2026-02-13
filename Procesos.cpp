// Integrante 1: Jose Miguel Castellanos Martinez
#undef UNICODE
#undef _UNICODE

#include "Procesos.h"
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <stdexcept>
#include <iostream>

Proceso* obtenerProcesosActivos(int& cantidadTotal) {
    cantidadTotal = 0;

    // Tomar una foto del sistema
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Fallo critico: No se pudo capturar el estado de los procesos.");
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    // Primer conteo para saber cuánta memoria reservar
    if (Process32First(hSnapshot, &pe)) {
        do {
            cantidadTotal++;
        } while (Process32Next(hSnapshot, &pe));
    } else {
        CloseHandle(hSnapshot);
        throw std::runtime_error("Error al leer el primer proceso del sistema.");
    }

    // Reservar memoria dinámica
    Proceso* listaProcesos = new Proceso[cantidadTotal];

    // Reiniciar para leer datos
    Process32First(hSnapshot, &pe);
    int indice = 0;

    do {
        listaProcesos[indice].pid = pe.th32ProcessID;
        listaProcesos[indice].nombre = pe.szExeFile;
        listaProcesos[indice].memoriaKB = 0;

        // Intentar leer la memoria del proceso
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe.th32ProcessID);
        if (hProcess) {
            PROCESS_MEMORY_COUNTERS pmc;
            if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                // WorkingSetSize viene en Bytes, convertimos a KB
                listaProcesos[indice].memoriaKB = pmc.WorkingSetSize / 1024;
            }
            CloseHandle(hProcess);
        }
        indice++;
    } while (Process32Next(hSnapshot, &pe) && indice < cantidadTotal);

    CloseHandle(hSnapshot);
    return listaProcesos;
}

void liberarMemoriaProcesos(Proceso* lista) {
    if (lista != nullptr) {
        delete[] lista;
    }
}
