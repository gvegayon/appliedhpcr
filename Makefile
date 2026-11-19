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
# HTML only: the PDF format converts mermaid diagrams to PNG with headless
# Chromium, which does not run in the container on Apple Silicon (the image is
# amd64 and runs emulated). PDF builds are left to CI.
container-preview:
	$(RUN) -p $(PORT):$(PORT) $(IMAGE) \
		quarto preview --render html --to html --host 0.0.0.0 --port $(PORT) --no-browser

.PHONY: help build container-render container-preview
