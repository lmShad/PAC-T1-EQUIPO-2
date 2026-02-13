// Integrante 2:  Jonathan Emir Jacobo Martinez
#include "Analisis.h"
#include <algorithm>
#include <cctype>
#include <string>

// Función auxiliar para comparar strings sin importar mayúsculas/minúsculas
bool iequals(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) return false;
    return std::equal(a.begin(), a.end(), b.begin(),
        [](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); });
}

std::vector<ProcesoSospechoso> analizarProcesos(
    const Proceso* procesos,
    int cantidadTotal,
    int modo,
    const std::vector<std::string>& sospechososUsuario,
    size_t umbralMemoriaMB)
{
    std::vector<ProcesoSospechoso> resultado;
    size_t umbralKB = umbralMemoriaMB * 1024; // Convertimos MB a KB porque Procesos.h usa KB

    for (int i = 0; i < cantidadTotal; ++i) {
        const Proceso& proc = procesos[i];
        bool enListaUsuario = false;

        // Verificar si está en la lista negra
        for (const auto& s : sospechososUsuario) {
            if (iequals(proc.nombre, s)) {
                enListaUsuario = true;
                break;
            }
        }

        bool memoriaExcesiva = (proc.memoriaKB > umbralKB);

        // LÓGICA DE DETECCIÓN
        if (modo == 1) {
            // Modo Básico: Solo lista negra
            if (enListaUsuario) {
                resultado.push_back({proc, "Coincide con lista del usuario", NivelRiesgo::ALTO});
            }
        }
        else { // Modo Estricto (2)
            if (enListaUsuario && memoriaExcesiva) {
                resultado.push_back({proc, "CRITICO: Lista negra + Memoria Alta", NivelRiesgo::ALTO});
            }
            else if (enListaUsuario) {
                resultado.push_back({proc, "Coincide con lista del usuario", NivelRiesgo::ALTO});
            }
            else if (memoriaExcesiva) {
                // Si pasa el umbral es MEDIO, si pasa el triple es ALTO
                if (proc.memoriaKB > (umbralKB * 3)) {
                     resultado.push_back({proc, "Consumo de memoria EXTREMO", NivelRiesgo::ALTO});
                } else {
                     resultado.push_back({proc, "Consumo de memoria elevado", NivelRiesgo::MEDIO});
                }
            }
        }
    }
    return resultado;
}
