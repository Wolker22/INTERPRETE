print('Escribe una palabra --> ');
read_string(palabra1);

print('Escribe otra palabra --> ');
read_string(palabra2);

if (palabra1 <= palabra2) 
then 
    print(palabra1);
    print(' es lexicográficamente anterior a ');
    print(palabra2);
else 
    print(palabra2);
    print(' es lexicográficamente anterior a ');
    print(palabra1);
end_if;

