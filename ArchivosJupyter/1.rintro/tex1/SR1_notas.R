#Limpieza de entorno. Aca aparecen unos comandos extragnos...que borran todo
#Borra consola, variables y funciones definidas en el entorno Global
rm(list = setdiff(ls(), lsf.str()));
rm(list=lsf.str());
cat("\014")
#(aca escribimos todo sin acentos...)
#PRIMER PASO
#Cargamos las notas de los 30 estudiantes
#De paso: una forma de no alargar demasiado cada
#linea, usando un simbolo "+"
notas <- c(3.1, 4.6, 2.7, 3.6, 3.6, 1.7, 3.8, +
             4.9, 4.1, 2.3, 1.6, 2.9, 4.1, 2.6, +
             4.2, 7.5, 7.0, 8.3, 9.0, 7.9, 8.2, 8.6, +
             7.9, 7.5, 8.2, 7.9, 8.1, 8.1, 9.5, 10)
#Nos fijamos si la cantidad de numeros que metimos es 30
show( length(notas) )
#Calculamos la media (el promedio) del curso
show(media <- mean(notas))
#Calculamos la mediana de las notas
show(mediana <- median(notas))
#Vemos el rango de la variable notas (la menor y la mayor)
rango <- range(notas)
#vemos la dispersion de datos mediante un histograma
show( hist(notas, breaks = 10, probability = T))
#notamos que parece haber dos modas
#graficamos la densidad de prob con el kernel
#y notamos que tiene dos maximos...
lines(density(c(notas,10)), lwd = 2, col = "red")
sprintf('La
 media de las notas es: %f \n', media)
sprintf('La
 mediana de las notas es: %f \n', mediana)
sprintf('El
 rango de las notas es: %f \n', rango[2]-rango[1])
sprintf('La
 nota minima es: %f \n', rango[1])
sprintf('La
 nota maxima es: %f \n', rango[2])

