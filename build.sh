if [ -d build ]; then
    rm build -rf
fi

mkdir build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make -j4