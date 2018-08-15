cmake_minimum_required(VERSION 3.9)
project(xdrProject C)

set(CMAKE_C_STANDARD 99)

add_executable(xdrProject main.c xdr.c xdr.h stellar.h stellar.c base64.c base64.h base32.c base32.h)