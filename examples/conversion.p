(*
  Programa de ejemplo de conversión de tipo.
  Se comprueba la conversión de tipo de una variable
*)

clear_screen;

place(3,10);
print('Ejemplo de cambio del tipo de valor de una variable \n');

print('Introduce un número --> ');
read(dato);

print('\nEl número introducido es -> ');
print(dato);

print('\nIntroduce una cadena de caracteres --> ');
read_string(dato);

print('\nLa cadena introducida es -> ');
print(dato);

place(20,10);
print('Fin del ejemplo de cambio del tipo de valor \n');