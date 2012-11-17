#!/usr/bin/env python
#
# Este script Python recibe un numero N por parametro, y genera
# N sucursales distribuidas aleatoriamente en el espacio.
#
# La forma de invocarlo es:
#
#   python generar-sucursales.py 1000 >sucursales.csv

import random
import sys

cant = 500
if sys.argv > 1:
	cant = int(sys.argv[1])

for i in range(cant):
	print "sucursal " + str(i) + ";" + str(random.randint(-32768, 32767)) + ";" + str(random.randint(-32768, 32767))
