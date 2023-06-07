###############Superficie plana de una mano####################################

# Borra consola, variables y funciones definidas en el entorno Global
rm(list = setdiff(ls(), lsf.str()));
rm(list=lsf.str());
cat("\014") #borra consola

#librerías (si R no tiene instaladas, las instala con "install.packages(libreria)")
if(suppressWarnings(library("jpeg", logical.return = T ) == FALSE)) +
{install.packages("jpeg")} 

if(suppressWarnings(library("crayon", logical.return = T ) == FALSE)) +
  {install.packages("crayon")} 
library("jpeg")
library("crayon")
####ESPECIFICAR CARPETA DE TRABAJO
setwd("/home/juan/Documentos/Docencia/fexpi/2018/notokabotonR/1/Archivos/")


#leemos el archivo de escala de grises (0 = negro/ 1 = blanco/ 0< grises <1)
#Si no está en enscala de grises no va a funcionar...
mano <- readJPEG('mano.jpg') #cargamos la imagen
mano <- as.matrix(mano[,,1]) #la hacemos una matriz

########Ploteo de imágenes#############
#ploteamos la imagen de la mano
plot(c(1,ncol(mano)) , c(1,nrow(mano)) , type = "n", main = "Mano", xlab = "", ylab = "" )
rasterImage(image = mano, xleft = 1, ybottom = 1, xright = ncol(mano), ytop = nrow(mano)) 

##La imágen está compuesta por numeros entre 0 y 1: 
#0/1: pixeles negro/blanco 
#0< grises<1
show(range(mano))

#¿como seleccionar los pixeles de la mano?
#histograma
hist(mano, col = "grey", main = "Histograma pixeles")

#Contraste: quedan en 1's todos los valores menores que...
manosaturada <- mano < 0.65 #establecemos un límite de gris para la mano
storage.mode(manosaturada) <- "numeric" #pasa de logico a numerico T = 1, F = 0


####PLOTEO de SELECCIóN
#si no vemos todo el contorno negro, sería mejor aumentar el contraste
plot(c(1,ncol(manosaturada)) , c(1,nrow(manosaturada)), type = "n", main = "Mano Saturada", xlab = "", ylab = 0)
rasterImage(image = manosaturada, xleft = 1, ybottom = 1, xright = ncol(manosaturada),
            ytop = nrow(manosaturada)) 

####CÁLCULOS DE SUPERFICIE (EN PÍXELES y en cm^2)
#la idea es que sumamos la cantidad de 1's
pixmano <- sum(manosaturada)#pixeles de la mano
pixfoto <- ncol(mano)*nrow(mano) #todos los pixeles
supmano <- (pixmano/pixfoto)*29.7*21 #superficie mano

#Muestra resultados
cat(bold(red(sprintf("La superficie de la mano es %.1f cm^2 \n \n ¿Dónde están los errores de esta medida? \n", as.numeric(supmano)))))

