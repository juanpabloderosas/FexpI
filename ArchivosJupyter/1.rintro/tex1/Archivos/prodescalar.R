################VECTORES PRODUCTO ESCALAR Y ANGULO###################
# Borra consola, variables y funciones definidas en el entorno Global
cat("\014")
rm(list = setdiff(ls(), lsf.str()));
rm(list=lsf.str());

library("crayon")

#definimos dos vectores
v1 <- c(1,0)
v2 <- c(0,1)

#calculamos producto punto
prod <- sum(v1*v2)

#calculamos modulos
modv1 <- sqrt(sum(v1^2))
modv2 <- sqrt(sum(v2^2))

#calculamos angulo
theta <- acos(prod/(modv1*modv2))

#ploteamos
plot(c(0, max(c(v1[1],v2[1]))+ 1) , c(0, max(c(v1[2],v2[2]))+1) ,type = "n", xlab = "x", ylab = "y")+
arrows(x0 = c(0,0), y0 = c(0,0), x1 = c(v1[1], v2[1]), y1 = c(v1[2], v2[2]), lwd = 2, col = "red",code = 2, angle = 10)


#imprimimos nuestros resultados
cat("\014") +
cat(bold(red(sprintf("Vectores \n v1 = <%.2f , %.2f> \n v2 = <%.2f , %.2f> \n \n", + 
 v1[1], v1[2], v2[1], v2[2])))) + 
  
cat(bold(red(sprintf("Modulos \n |v1|  = %.3f \n |v2| = %.3f \n \n", + 
                         modv1, modv2))))  +
  
cat(bold(red(sprintf("Producto Escalar \n v1 . v2 = %.3f \n \n", + 
                         prod))))  +
  
cat(bold(red(sprintf("Angulo entre v1 y v2 \n v1^v2 = %.3f rad \n \n", + 
                         theta))))  +
  
cat(bold(red(sprintf("Angulo entre v1 y v2 \n v1^v2 = %.3f ° \n \n", + 
                         theta*180/pi))))



