
set(PROJECT_NAME HashAlgorithm)
set(PROJECT_LOCATION /home/hex24/Desktop/C_Projects/BlockChainsExercises)
set(PROJECT_STRING "HashAlgorithm")


set(CFLAGS "${CFLAGS} -O3")

set(SRC 
main/main.c
hash/hash.c
hash/random/random.c
blockchain/blockchain_engine.c
)

cmake_minimum_required(VERSION 3.3)
project(${PROJECT_NAME} LANGUAGES C)
add_executable(${PROJECT_STRING} ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)