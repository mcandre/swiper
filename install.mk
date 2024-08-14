.POSIX:
.SILENT:
.PHONY: all

all:
	cargo install --force unmake@0.0.17

	npm install -g snyk

	pip3 install --upgrade pip setuptools
	pip3 install -r requirements-dev.txt
