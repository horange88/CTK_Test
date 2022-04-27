# CTK_Test
## CTK_EmbeddedCodingInterview

### Instrucciones
El proyecto consta de un caso de prueba que se puede compilar con Makefile
```
make
```

Ejecutar caso de prueba con
```
./main
```

### Explicación


El caso de prueba consiste en el llamado a la función `log_transactions()`,
pasando como parámetro un arreglo de bytes que simula los datos serializados
según el protocolo de comunicación especificado.

Los datos simulados se encuentran en el archivo `Test/Datest.h`.

Luego del llamado a la función `log_transactions()`, se imprime el log generado, mostrando
los datos ordenados por fecha.