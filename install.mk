.POSIX:
.SILENT:
.PHONY: \
	all \
	python \
	rust

all: python rust

python:
	pip3 install --upgrade pip setuptools
	pip3 install -r requirements-dev.txt

rust:
	cargo install --force unmake@0.0.17
