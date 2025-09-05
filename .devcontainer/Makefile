ifndef CONTAINER
CONTAINER := podman
endif

help:
	@echo "Makefile commands:"
	@echo "  build  - Build the container image using $(CONTAINER)"
	@echo "  push   - Push the container image to Docker Hub"

push:
	$(CONTAINER) push gvegayon/appliedhpcr:latest \
		docker.io/gvegayon/appliedhpcr:latest

build:
	$(CONTAINER) build -t gvegayon/appliedhpcr:latest .

.PHONY: push build