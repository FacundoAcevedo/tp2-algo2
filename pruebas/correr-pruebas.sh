#!/usr/bin/env bash

error() {
	echo "$1" >&2
	exit 1
}

advertencia() {
	echo "$1" >&2
}

uso() {
error "$(cat <<EOF
$0

Formas de uso:
  $0 programa          Correr todas las pruebas para el programa
  $0 programa prueba   Correr unicamente la prueba indicada
  $0 -h                Imprimir este mensaje
EOF
)"
}

[ "$1" ] || uso
[ "$1" == "-h" ] && uso

PROGRAMA="$1"
PROGRAMA=`readlink -e "$PROGRAMA"`

PRUEBA="$2"

ROOT=`dirname $0`
ROOT=`readlink -e "$ROOT"`

ok=0
total=0
for dir in `find "$ROOT" -mindepth 1 -maxdepth 1 -type d`; do
	cd "$dir"
	tmp=`mktemp`
	prueba_actual=`basename "$dir"`
	
	[ "$PRUEBA" -a "$PRUEBA" != "$prueba_actual" ] && continue
	[ -f sucursales.csv ] || { advertencia "Ignorando el directorio ${prueba_actual}: no existe sucursales.csv"; continue; }

	total=$(( $total + 1 ))
	echo -n "$prueba_actual"": "
	if [ -f entrada ]; then
		"$PROGRAMA" <entrada >"$tmp"
	else
		"$PROGRAMA" >"$tmp"
	fi
	cod="$?"
	if [ "$cod" != 0 ]; then
		echo "$prueba_actual"": ERROR (codigo de salida: $cod)"
	else
		if diff -N -q salida "$tmp" >/dev/null 2>&1; then
			echo "OK"
			ok=$(( $ok + 1 ))
		else
			echo "ERROR (diferencias en la salida esperada)"
			echo "--- salida esperada:"
			[ -f salida ] && cat salida
			echo "--- salida obtenida:"
			cat "$tmp"
		fi
	fi
	rm -f "$tmp"
done

echo
echo "Pruebas pasadas: $ok / $total"

