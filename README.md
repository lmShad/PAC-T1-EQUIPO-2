Proyecto: Monitoreo de procesos en C++

Descripción General

Este proyecto implementa un monitor de procesos del sistema en C++ diseñado específicamente para entornos Windows. El programa captura la lista de procesos activos, analiza su consumo de recursos y determina cuáles pueden considerarse sospechosos basándose en criterios técnicos y de usuario.

Funcionalidades principales:

Visualización: Muestra procesos activos (PID, nombre y memoria usada).
Análisis Dual: Evaluación en modo básico o estricto.
Detección Inteligente: * Coincidencia con listas negras definidas por el usuario.Identificación por uso elevado de memoria.
Reportes: Generación automática de un archivo .txt con los resultados detallados.

El proyecto está estructurado de forma modular, separando la lógica de obtención de datos, el motor de análisis y el sistema de reportes.

Integrantes del Equipo:

Nombre 1 – JoM235
Nombre 2 – ImShad
Nombre 3 – BR4ND0NFL0RES
Nombre 4 – LookendSmookey

Instrucciones de Compilación y Ejecución

Requisitos
Sistema Operativo: Windows
Compilador: Compatible con C++ (g++, MinGW o MSVC)
Librerías del Sistema:Windows API<tlhelp32.h><psapi.h>

Compilación (con g++)
Ejecuta el siguiente comando en tu terminal para vincular las librerías necesarias:Bashg++ main.cpp Procesos.cpp Analisis.cpp Registro.cpp -o monitor -lpsapi

Ejecución
Para iniciar el programa, usa el comando:Bashmonitor.exe

Interacción con el Usuario
Al ejecutarse, el programa solicitará los siguientes datos:
Modo de análisis: (1 = Básico, 2 = Estricto).
Nombre del archivo: Para guardar el reporte (ej. reporte.txt).
Lista de procesos: Nombres de procesos sospechosos.

Entrada Esperada

Modo de análisis:	1 para Básico o 2 para Estricto
Archivo de salida:	Nombre del archivo .txt a generar
Lista opcional:	Nombres manuales definidos por el usuario

Enfoque tecnico
El sistema utiliza la Windows API para interactuar con el núcleo del sistema operativo mediante las siguientes funciones clave:

CreateToolhelp32Snapshot(): Captura el estado actual de los procesos.
Process32First() y Process32Next(): Permiten recorrer la lista de procesos obtenidos.OpenProcess(): Abre un canal de acceso a cada proceso individual.
GetProcessMemoryInfo(): Consulta el Working Set Size (uso de memoria).
Nota técnica: El uso de memoria se convierte automáticamente a kilobytes (KB). La memoria del programa se gestiona dinámicamente mediante el uso de new[] y delete[].

Criterios de Detección de Riesgo definidos en dos niveles de sensibilidad para el análisis:

Modo 1 (Básico)
Se activa si el proceso coincide con la lista proporcionada por el usuario.
Nivel asignado: Riesgo MEDIO.


Modo 2 (Estricto)
Aplica criterios más rigurosos de evaluación:
Riesgo MEDIO: El nombre coincide con la lista del usuario.
Riesgo ALTO: El uso de memoria es superior a 200 MB.
Riesgo ALTO: Coincidencia en lista y supera el umbral de memoria.
"El reporte final incluye procesos con riesgo MEDIO y ALTO."

Salida Generada (Reporte)
El archivo final proporciona una visión integral del estado del sistema: 
Fecha y hora exacta del análisis.
Conteo total de procesos detectados.
Listado completo de procesos activos.
Sección de Hallazgos: Detalle de procesos sospechosos (PID, Nombre, Memoria, Razón y Nivel de Riesgo).

Si no se detectan anomalías, el sistema generará un mensaje indicando que no se encontraron riesgos.
Referencias
Documentación oficial de Windows API
Documentación de tlhelp32.h
Documentación de psapi.h
https://learn.microsoft.com/
https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-createtoolhelp32snapshot
https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-getprocessmemoryinfo
