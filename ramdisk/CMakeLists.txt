cmake -DCMAKE_C_COMPILER=$/home/Desktop/OS-Course-Lab/build/toolchain.cmake
add_executable(hello_chcore.bin main.c)

chcore_install_all_targets()
