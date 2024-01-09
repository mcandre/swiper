.POSIX:
.SILENT:
.PHONY: all

all:
	cargo install --force unmake@0.0.16

	go install github.com/mcandre/karp/cmd/karp@v0.0.8
	go mod tidy

	pip3 install --upgrade pip setuptools
	pip3 install -r requirements-dev.txt
