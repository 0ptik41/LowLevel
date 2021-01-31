from ctypes import *


lib = cdll.LoadLibrary('./libPython.so')
lib.print_python_bytes.argtypes = [py_object]

var = b'TEST_VARIABLE'

print(var)
print(hex(id(var)))
lib.print_python_bytes(var)

