Bachelor's thesis
=====

```
Title: 2D path rendering using OpenGL ES 2.0
Author: LEDÁN Szilárd
Supervisor: KISS Ákos, PhD, assistant professor
Department of Software Enginering, University of Szeged
```

### Getting started

#### 1. Step: Fetch `gepard` code

```bash
./scripts/fetch-code.sh
```

#### 2. Step: Install dependencies

```bash
./scripts/install-deps.sh # --dev
```

#### 3. Step: Build code and paper

Build `pdf` and `code`.
```bash
cmake -H. -Bbuild
make -C build
```
