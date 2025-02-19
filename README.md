# Rock Paper Scissors

## Build

### Linux (Ubuntu 24.10)

- Нужно немного подождать
  - `conan2` - пытается выкачать `qt6`, т.к. мы в России - с официального сайта не получается и он перебирает зеркала
  - `qt6` - для `linux` в данный момент сборка не закеширована в следствии чего один раз локально будет собираться из исходников

- `./build_and_run_linux.sh`

### Windows (Windows 11 24H2)

- [git](https://github.com/git-for-windows/git/releases/download/v2.47.1.windows.2/Git-2.47.1.2-64-bit.exe)
- [visual studio](https://visualstudio.microsoft.com/ru/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false)
- [python](https://www.python.org/ftp/python/3.13.1/python-3.13.1-amd64.exe)
- [cmake](https://github.com/Kitware/CMake/releases/download/v3.31.5/cmake-3.31.5-windows-x86_64.msi)

в powershell от имени администратора (нужно для использования `python3-venv`)
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
cmake --preset conan-release
cmake --build --preset conan-release
```
