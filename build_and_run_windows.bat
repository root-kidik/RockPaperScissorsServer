python -m venv env
call env\Scripts\activate

pip install conan

conan profile detect --exist-ok
conan install . --build=missing --settings:all compiler.cppstd=17 --settings:all build_type=Release
cmake --preset conan-default
cmake --build --preset conan-release

call run_windows.bat
