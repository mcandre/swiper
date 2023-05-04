.POSIX:
.SILENT:
.PHONY: all

all:
	cargo install --force unmake@0.0.11

	go install github.com/mcandre/karp/cmd/karp@v0.0.7
	go mod tidy

	pip3 install --upgrade pip setuptools
	pip3 install -r requirements-dev.txt
