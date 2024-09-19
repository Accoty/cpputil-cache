if [ -d _build ]; then
    rm _build -rf
fi

mkdir _build
cd _build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make -j4