#!/bin/sh

# OpenGL auf Linux (X86, ARM) installieren

# Anleitung:
# https://medium.com/geekculture/a-beginners-guide-to-setup-opengl-in-linux-debian-2bfe02ccd1e

# ----------------------------------------------------------------
# Pakete installieren

apt install cmake
apt install pkg-config

apt install mesa-utils
apt install libglu1-mesa-dev
apt install freeglut3-dev
apt install mesa-common-dev

apt install libglew-dev
apt install libglfw3-dev
apt install libglm-dev

apt install libao-dev
apt install libmpg123-dev

apt install libxkbcommon-dev
apt install libxinerama-dev
apt install libxcursor-dev
apt install libxi-dev
apt install doxygen           #    (Dokumentation kompilieren)

# ----------------------------------------------------------------------------------------------------------------------------
# GLFW (Graphics Library Framework) installieren (handle the input from the joystick, keyboard, and mouse)

# cd /usr/local/lib/                                    nicht unbedingt notwendig, temporäres Verzeichnis reicht

git clone https://github.com/glfw/glfw.git
cd glfw
cmake .
make
make install
cd ..
rm -rf glfw

# --------------------------------------------------------------------------------------------------------------------------
# Glad Loader generieren (glad.c, glad.h, khrplatform.h)
# https://glad.dav1d.de/

# Version: soll mindestens 3.3 sein
# Profile:  Core, Compatibility geht auch
# v Generate a loader

# -----------------------------------------------------
g++ triangle.cc glad.c -ldl -lglfw

# Erklärung des Programms:
# https://learnopengl.com/Getting-started/Hello-Window

