# ---------------------------------------------------------------------------------

# Explicaciones

Se considera memoria compartida en la presente suma de columnas de una matriz de 1024 filas y 512 columnas.

Para ello hay que tener en consideración el siguiente esquema que indica que la forma en la que una matriz está alojada en la memoria host es diferente a como se guarda en la memoria global del device. Es decir, si por el host se considera la matriz vista en una dimensión se alineará considerando las filas completas, pero si la vemos desde el device se alineará por columnas. 

![](https://raw.githubusercontent.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/master/3%20Suma%20de%20columnas%20de%20matriz%20con%20memoria%20compartida/capturas/im1.png)

Para mostrar la organización de las dimensiones en el device consideramos el siguiente gráfico:

![](https://raw.githubusercontent.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/master/3%20Suma%20de%20columnas%20de%20matriz%20con%20memoria%20compartida/capturas/im2.png)

Habiendo visto esta parte inicial podemos mostrar cómo se han considerado las dimensiones tanto del grid como de los bloques:

![](https://raw.githubusercontent.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/master/3%20Suma%20de%20columnas%20de%20matriz%20con%20memoria%20compartida/capturas/im3.png)

En la imagen previa se muestra que en los bloques existe una distribución bidimensional de los hilos, pues se hizo:

![](https://raw.githubusercontent.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/master/3%20Suma%20de%20columnas%20de%20matriz%20con%20memoria%20compartida/capturas/im4.png)

Ahora, notemos que en la dimensión x del grid cada identificador representa el bloque que se encargará de procesar más de una columna. Pues cada bloque procesa la cantidad de "chunk" columnas.

En el código del kernel existe la variable Nds, este es es el arreglo compartido que va recogiendo los resultados de las hebras para luego sincronizarlas el bloque, esto como paso previo a la recopilación de resultados que hace el primer hilo del bloque.

Al utilizar la memoria compartida permite a todos los hilos del bloque acceder a datos de la memoria compartida. Asi los hilos cooperan compartiendo sus datos. Ocasionando ejecuciones más rápidas. Ademas es más rápido el acceso a la memoria compartida que a la memoria global.
![](https://raw.githubusercontent.com/FranklinCncr/TopicosEnComputacionGraficaGrupo/master/3%20Suma%20de%20columnas%20de%20matriz%20con%20memoria%20compartida/capturas/memoria_cmpa.png)
Tambien los datos la memoria compartida solo se conservan cuando se ejecuta el kernel. Cuando el kernel concluye, el contenido de la memoria compartida desaparece  la memoria. Por otro lado la memoria compartida limita la cantidad de hilos por bloque.


