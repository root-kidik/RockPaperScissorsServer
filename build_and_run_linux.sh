#!/bin/bash

set -e

sudo apt install git                     \
                 g++                     \
                 python3                 \
                 cmake                   \
                 python3-venv            \
                 pkg-config              \
                 libxcb-util-dev         \
                 libx11-dev              \
                 libxau-dev              \
                 libgl1-mesa-dev         \
                 libx11-xcb-dev          \
                 libfontenc-dev          \
                 libice-dev              \
                 libsm-dev               \
                 libxaw7-dev             \
                 libxcomposite-dev       \
                 libxcursor-dev          \
                 libxdamage-dev          \
                 libxext-dev             \
                 libxfixes-dev           \
                 libxi-dev               \
                 libxinerama-dev         \
                 libxkbfile-dev          \
                 libxmu-dev              \
                 libxmuu-dev             \
                 libxpm-dev              \
                 libxrandr-dev           \
                 libxrender-dev          \
                 libxres-dev             \
                 libxss-dev              \
                 libxt-dev               \
                 libxtst-dev             \
                 libxv-dev               \
                 libxxf86vm-dev          \
                 libxcb-glx0-dev         \
                 libxcb-render0-dev      \
                 libxcb-render-util0-dev \
                 libxcb-xkb-dev          \
                 libxcb-icccm4-dev       \
                 libxcb-image0-dev       \
                 libxcb-keysyms1-dev     \
                 libxcb-randr0-dev       \
                 libxcb-shape0-dev       \
                 libxcb-sync-dev         \
                 libxcb-xfixes0-dev      \
                 libxcb-xinerama0-dev    \
                 libxcb-dri3-dev         \
                 uuid-dev                \
                 libxcb-cursor-dev       \
                 libxcb-dri2-0-dev       \
                 libxcb-dri3-dev         \
                 libxcb-present-dev      \
                 libxcb-composite0-dev   \
                 libxcb-ewmh-dev         \
                 libxcb-res0-dev

python3 -m venv env
source env/bin/activate
pip3 install conan

conan profile detect --exist-ok
conan install . --build=missing --settings:all compiler.cppstd=17 --settings:all build_type=Release
cmake --preset conan-release
cmake --build --preset conan-release

echo "Runned"
./build/Release/bin/RockPaperScissorsServer
