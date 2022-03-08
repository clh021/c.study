#!/usr/bin/python3
import ctypes

print("Hello, World!")


lib = ctypes.cdll.LoadLibrary("./hello_module.so")

lib.hello("world")  # hello world!
