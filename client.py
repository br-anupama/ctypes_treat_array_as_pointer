#!/usr/bin/python

from ctypes import *
import socket

import int_array_as_pointer as array_py



p = array_py.place()

setattr(p, 'pos_n', 1989)
setattr(p, 'pos_s', 2018)

stu = array_py.student()
setattr(stu, "type", 8000)
print "length :", sizeof(p)/sizeof(c_int)
setattr(stu, 'length', sizeof(p)/sizeof(c_int) )
memmove(addressof(stu.buffer), addressof(p), sizeof(p) )


s = socket.socket()
s.connect(('localhost', 8080))
s.send(stu)
s.close()
