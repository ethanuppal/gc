# gc

![CI Status Badge](https://github.com/ethanuppal/gc/actions/workflows/ci.yaml/badge.svg)
[![CodeFactor Badge](https://www.codefactor.io/repository/github/ethanuppal/gc/badge)](https://www.codefactor.io/repository/github/ethanuppal/gc)

A garbage collection runtime for practice

This is a garbage collection runtime I'm building for practice.
I'm only testing it on Apple Silicon via through Rosetta (so it runs on 64-bit Intel).
See [`project.md`](./doc/project.md) for information on the project structure.

## Usage

This project is managed through a `Makefile`.
Run `make help` for usage information.

## Testing

Tests are under [`test/`](./test/).

## CI

`make test` will install dependencies if they are missing, so the [CI](./.github/workflows/ci.yaml) need only
run that command.
