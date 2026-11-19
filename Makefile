ifndef CONTAINER
CONTAINER := podman
endif

ifndef IMAGE
IMAGE := ghcr.io/gvegayon/appliedhpcr:latest
endif

ifndef PORT
PORT := 4200
endif

RUN := $(CONTAINER) run --rm -v "$(CURDIR)":/workspace -w /workspace

help:
	@echo "Makefile commands:"
	@echo "  build             - Preview the book with the local quarto (render all)"
	@echo "  container-render  - Render the book (HTML) using the container image"
	@echo "  container-preview - Render and preview the book at http://localhost:$(PORT)"
	@echo "                      using the container image"
	@echo "  diagrams          - Render the mermaid diagrams (fig/**/*.mmd) to PNG"
	@echo "                      using mermaid.ink (needs curl and internet)"
	@echo ""
	@echo "Variables (defaults): CONTAINER=$(CONTAINER), IMAGE=$(IMAGE), PORT=$(PORT)"
	@echo "Example: make container-preview CONTAINER=docker"

build:
	quarto preview --render all

# One-off render of the English book (HTML), same as the CI workflow
container-render:
	$(RUN) $(IMAGE) quarto render --to html

# Render the HTML book and serve it (with live reload) on
# http://localhost:$(PORT). Stop it with Ctrl+C.
# HTML only, to keep it fast; PDF builds are left to CI.
container-preview:
	$(RUN) -p $(PORT):$(PORT) $(IMAGE) \
		quarto preview --render html --to html --host 0.0.0.0 --port $(PORT) --no-browser

# Diagrams ---------------------------------------------------------------------
# The book's diagrams are written in mermaid (fig/**/*.mmd) but included as
# PNG files, so rendering the book (in particular the PDF) does not need a
# headless browser. After editing a .mmd file, run `make diagrams` and commit
# both files.
#
# Each diagram is rendered by mermaid.ink twice: once at its natural size, to
# read its width, and then at 3x that width for a sharp image.
MMD := $(shell find fig -name '*.mmd')
PNG := $(MMD:.mmd=.png)

diagrams: $(PNG)

%.png: %.mmd
	@echo "Rendering $<..."
	@b64=$$(base64 < "$<" | tr -d '\n' | tr '+/' '-_'); \
	curl -sSf --retry 5 --retry-delay 3 -o "$@" "https://mermaid.ink/img/$$b64?type=png" && \
	w=$$(file "$@" | sed -E 's/.*PNG image data, ([0-9]+) x.*/\1/') && \
	sleep 2 && \
	curl -sSf --retry 5 --retry-delay 3 -o "$@" "https://mermaid.ink/img/$$b64?type=png&width=$$w&scale=3" || \
	{ rm -f "$@"; echo "Failed to render $<"; exit 1; }

.PHONY: help build container-render container-preview diagrams
