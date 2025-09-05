# Versión en Español - HPC Aplicado con R

Esta es la versión en español del libro "Applied HPC with R" por George G. Vega Yon.

## Estado Actual

🚧 **Trabajo en Progreso** 🚧

Esta traducción está actualmente en desarrollo. El contenido incluye:

- ✅ Estructura básica del libro
- ✅ Configuración de Quarto
- ✅ Prefacio traducido
- ✅ Plantillas básicas para todos los capítulos
- 🔄 Traducción completa de contenido (en progreso)

## Estructura

La versión en español está organizada en la carpeta `es/` y sigue la misma estructura que la versión original en inglés:

```
es/
├── _quarto.yaml          # Configuración del libro en español
├── index.qmd             # Prefacio en español
├── profiling.qmd         # Perfilado de Código
├── efficiency.qmd        # Eficiencia
├── intro.qmd             # Introducción a Computación Paralela
├── parallel-pkg.qmd      # El Paquete parallel
├── slurm-fundamentals.qmd # Fundamentos de SLURM
├── slurm-simpi.qmd       # SLURM con Simulación
├── rcpp-part1.qmd        # Rcpp Parte 1
├── rcpp-debugging.qmd    # Depuración de Rcpp
├── misc.qmd              # Misceláneos
├── references.qmd        # Referencias
└── [symlinks to shared resources]
```

## Recursos Compartidos

Los siguientes recursos se comparten con la versión en inglés mediante enlaces simbólicos:

- `fig/` - Directorio de imágenes
- `*.R`, `*.cpp`, `*.slurm` - Archivos de código fuente
- `rcpp-part1_files/` - Archivos generados

## Contribuir

Si encuentras errores de traducción o deseas contribuir con la traducción, por favor:

1. Abre un issue en el repositorio
2. Proporciona sugerencias específicas
3. Indica el archivo y sección que necesita corrección

## Construcción

Para construir la versión en español:

```bash
cd es/
quarto render
```

## Versión Original

La versión original en inglés está disponible en el directorio raíz del repositorio.