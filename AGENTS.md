# Agent instructions

This repository is a Quarto book, *Applied HPC with R*.
English sources live in the root directory, and the Spanish translation lives in `es/` (it has its own `_quarto.yml`).

## Rendering the book

Quarto, R, and the R packages the book needs (`slurmR`, `Rcpp`, `RcppArmadillo`, `future`, `microbenchmark`, `lobstr`, ...) may not be installed on the host.
The repository ships a devcontainer (`.devcontainer/`) with everything needed.
Agents can use it to render things if needed, with `podman` or, if available, `docker` (use whichever is installed; the commands are the same, just swap the name).

The root `Makefile` wraps the most common cases (`CONTAINER`, `IMAGE`, and `PORT` can be overridden, e.g., `make container-preview CONTAINER=docker`):

```bash
make container-render   # one-off HTML render of the English book
make container-preview  # render the HTML book + serve at http://localhost:4200 (Ctrl+C to stop)
```

The CI workflow (`.github/workflows/pages.yaml`) renders using the prebuilt image `ghcr.io/gvegayon/appliedhpcr:latest`, so you can use it directly:

```bash
# Render the English book (HTML) from the repo root
podman run --rm -v "$PWD":/workspace -w /workspace \
  ghcr.io/gvegayon/appliedhpcr:latest quarto render --to html

# Render a single chapter
podman run --rm -v "$PWD":/workspace -w /workspace \
  ghcr.io/gvegayon/appliedhpcr:latest quarto render slurm-under-the-hood.qmd --to html

# Spanish version
podman run --rm -v "$PWD":/workspace -w /workspace/es \
  ghcr.io/gvegayon/appliedhpcr:latest quarto render --to html

# PDF (Typst, orange-book extension)
podman run --rm -v "$PWD":/workspace -w /workspace \
  ghcr.io/gvegayon/appliedhpcr:latest quarto render --to orange-book-typst
```

If the image is not available (or `.devcontainer/Containerfile` changed), build it locally first:

```bash
cd .devcontainer && podman build -t gvegayon/appliedhpcr:latest .
```

(`make build` in `.devcontainer/` does the same, and honors `CONTAINER=docker`.)
Then replace `ghcr.io/gvegayon/appliedhpcr:latest` with `gvegayon/appliedhpcr:latest` in the commands above.

Notes:

- On macOS, `podman` needs a running VM (`podman machine start`).
- Don't use ```` ```{mermaid} ```` chunks: the PDF build would need a headless browser to convert them. Write the diagram as a `.mmd` file under `fig/`, run `make diagrams` (renders PNGs through mermaid.ink; needs `curl` and internet), and include the PNG as a regular image. Commit both files.
- Rendering rewrites files under `_book/` (and `es/_docs/`), which are tracked or semi-tracked. Do not commit render output unless asked to.
- Only run the container when rendering is actually needed to verify a change (e.g., diagrams, cross-references, or code chunks that execute); for plain text edits it is not necessary.

## Conventions

- Prose: one sentence per line in `.qmd` files.
- Cross-references use Quarto syntax (`@fig-...`, `@tbl-...`); when removing or renaming a figure or table, search for every reference to it (`grep -rn "fig-name" *.qmd es/*.qmd`).
- When a chapter changes, the Spanish version in `es/` should be updated too (or flagged as pending).
