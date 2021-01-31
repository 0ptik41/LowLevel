/*  gcc -Wall -Wextra -pedantic -Werror -std=c99 -shared -Wl,-soname,libPython.so -o libPython.so -fPIC -I/usr/include/python3.4 inspect.c */
#include "python3.6m/Python.h"

void print_python_bytes(PyObject *p){
     /* The pointer with the correct type.*/
     PyBytesObject *s;
     unsigned int i;
     printf("[.] bytes object info\n");
     /* casting the PyObject pointer to a PyBytesObject pointer */
     s = (PyBytesObject *)p;
     
     if (s && PyBytes_Check(s)){
          printf("  address of the object: %p\n", (void *)s);
          /* op_size is in the ob_base structure, of type PyVarObject. */
          printf("  size: %ld\n", s->ob_base.ob_size);
          /* ob_sval is the array of bytes, ending with the value 0:
         ob_sval[ob_size] == 0 */
          printf("  trying string: %s\n", s->ob_sval);
          printf("  address of the data: %p\n", (void *)(s->ob_sval));
          printf("  bytes:");
          for (i = 0; i < s->ob_base.ob_size + 1; i++){
               printf(" %02x", s->ob_sval[i] & 0xff);
          }
          printf("\n");
     }
     /* if this is not a PyBytesObject print an error message */
     else{
          fprintf(stderr, "  [ERROR] Invalid Bytes Object\n");
     }
}