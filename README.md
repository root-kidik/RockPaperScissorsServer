# Rock Paper Scissors

## Build

### Linux (Ubuntu 24.04 LTS)

```sh
sudo snap install code --classic

sudo apt install git g++ python3 cmake python3-venv pkg-config

sudo apt install libxcb-util-dev libx11-dev libxau-dev libgl1-mesa-dev libx11-xcb-dev libfontenc-dev libice-dev libsm-dev libxaw7-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxext-dev libxfixes-dev libxi-dev libxinerama-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxrandr-dev libxrender-dev libxres-dev libxss-dev libxt-dev libxtst-dev libxv-dev libxxf86vm-dev libxcb-glx0-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev uuid-dev libxcb-cursor-dev libxcb-dri2-0-dev libxcb-dri3-dev libxcb-present-dev libxcb-composite0-dev libxcb-ewmh-dev libxcb-res0-dev

python3 -m venv env
source env/bin/activate
pip3 install conan

conan profile detect --exist-ok
conan install . --build=missing --settings:all compiler.cppstd=17 --settings:all build_type=Release
conan install . --build=missing --settings:all compiler.cppstd=17 --settings:all build_type=Debug
```

### Windows (Windows 11)

- [git](https://github.com/git-for-windows/git/releases/download/v2.47.1.windows.2/Git-2.47.1.2-64-bit.exe)
- [visual studio](https://visualstudio.microsoft.com/ru/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false)
- [python](https://www.python.org/ftp/python/3.13.1/python-3.13.1-amd64.exe)
- [cmake](https://github.com/Kitware/CMake/releases/download/v3.31.5/cmake-3.31.5-windows-x86_64.msi)

- [vscode](https://code.visualstudio.com/download#)
- расширения:
    - C/C++
    - CMake
    - CMake Tools

в powershell от имени администратора
```sh
Set-ExecutionPolicy RemoteSigned
```

в дериктории проекта
```sh
python -m venv env
env/Scripts/activate

pip install conan

conan profile detect --exist-ok
conan install . --build=missing --settings:all compiler.cppstd=17 --settings:all build_type=Release
conan install . --build=missing --settings:all compiler.cppstd=17 --settings:all build_type=Debug
```

В vscode включить
Cmake › Options: Status Bar Visibility -> visible

затем выбрать пресет и собрать

## TODO:

- [ ] `LoginCommand`
- [ ] `SingleCommandSender`