
#Inicialización: borra todo y carga librerías (se pueden instalar fácilmente si no las tienen):
# install.packages("libreríaquequiero")

#Borra consola, variables y funciones definidas en el entorno Global
rm(list = setdiff(ls(), lsf.str()));
rm(list=lsf.str());
cat("\014")

#librerías
suppressMessages(library("crayon")); suppressMessages(library("ggplot2"));
suppressMessages(library("gridExtra"));suppressMessages(library("latex2exp"))
library(xtable)
library(IRdisplay)
library(repr)
#opciones de ploteo ggplot2
temajuan3 <- theme(
    legend.title = element_text(size = 14),
    panel.background = element_rect(fill = "gray93"),
    legend.box = "vertical",
    legend.direction = "vertical",
    legend.key.height = unit(0.1,"snpc"),
    legend.key.width  = unit(0.1,"snpc"),
    axis.line = element_line(size = 0.5, lineend = "square"),
    axis.ticks = element_line(size = 1, colour = "black"),
    panel.border = element_rect(size = 1, fill = NA ),
    axis.title = element_text(size = 24),
    axis.text.x  = element_text(size = 20),
    axis.text.y = element_text(size = 20),
    legend.background = element_blank(),
    legend.position = c(0.3,0.8),
    legend.key = element_blank(),
    legend.text = element_text(size = 20)
    )
fig <- function(width, heigth){
 options(repr.plot.width = width, repr.plot.height = heigth)
 }
setwd("/home/juan/Documentos/Docencia/fexpi/")

getwd(); #nos dice el directorio de trabajo actual

setwd("/home/juan/Documentos/Docencia/fexpi/2019/Laboratorios/Laboratorio4/Datos/") #indica un nuevo directorio

getwd()

list.files()

archivo <- gsub(readLines(con =  "00.tsv", n = -1), , pattern = "\"",replacement = ""); print(archivo[1:10])

datos <- read.csv(file = "00.tsv", sep = "\t", header = F)

head(datos, 3); dim(datos)

datos <- datos[ , -1] #saca primer columna
datos <- datos[ , -5] #ojo que sacamos la primera y quedaron 5 columnas
head(datos, 3)

colnames(datos) <- c("t", "ax", "ay", "az"); head(datos, 2)

datos$t <- datos$t - datos$t[1]; head(datos, 2); range(datos$t)

datos$t <- datos$t/1000; head(datos, 10); range(datos$t)

ga <- ggplot(data = datos) +
geom_point(aes(x = t, y = ax, colour = "ax")) + 
geom_point(aes(x = t, y = ay, colour = "ay")) +
geom_point(aes(x = t, y = az, colour = "az")) +
ylab(TeX("$a \\; (m\\, / \\,s^2)$")) + xlab("t (s)") + 
scale_colour_manual(values = c("ax" = "green4", "ay" = "red4", "az" = "Deepskyblue4" ),name = NULL) +
temajuan3  + theme(legend.position = c(0.2,0.4), legend.direction = "horizontal")
fig(width = 16,heigth = 8); show(ga)

# IMPORTANTE: definir el "Working Directory" (directorio de trabajo): escribimos dónde están nuestres archives de datos.
setwd("/home/juan/Documentos/Docencia/fexpi/2020/NTB/2.rcargadatos/Datos/")
#NOTA: en windows se mantienen las barras "/", por ejemplo: setwd("d:/archivos/archivosR/")
#Para ver que funciona:
getwd()

#ahora vemos el merged-ice-core-yearly.csv/ parámetro n = -1 : lee todas las líneas del archivo
archivo <- gsub(readLines(con =  "merged-ice-core-yearly.csv", n = -1), , pattern = "\"",replacement = "")

print(archivo[1:35])

diox <- read.csv(file = "merged-ice-core-yearly.csv", header = T, sep = ";", skip = 26)

head(diox, 5); nrow(diox)

at <- read.csv("TA.csv", sep = ",", header = T); head(at,5) #cada une mira cómo hacerlo

#PLOT anomalía térmica:
fig(width = 28,heigth = 16) #cosa del Jupyter para que muestre más grande el gráfico
plot(x = at$Year, y =  at$TA, main = "Anomalía Térmica entre los años 1880 y 2017", #main; título del gráfico
    xlab = "Año", #título eje x
    ylab = "Anomalía Térmica (°C)", #ídem y
    pch = 16, # símbolo de punto
    cex = 1, #tamaño de punto
    cex.axis = 1.5,
     cex.lab = 1.5,
     cex.main = 2
    )


#PLOT CO2: se pueden hacer por capas (hay más cosas en el pdf)
fig(width = 26,heigth =15)
grafco2 <- plot(diox$Y, diox$CO2, xlab = "Año",
ylab = expression(paste("C",O[2]," (ppm)")), #símbolos raros para el subíndice
main = expression(paste("Concentración de ",CO[2],
"(ppm) entre los años 13 y 2018")), pch = 20, cex.axis = 1.5, cex.lab = 1.35,cex.main = 2.5, ) + 
#segmentos indicando el tiempo de las revoluciones industriales
segments(x0 = c(1750,1875), x1 = c(1750,1875),y0 = 0,y1 = c(300,320), lty = 2)
#texto de etiquetas dentro del gráfico (no lo use casi nunca)
text(x = c(1620,1740), y = c(306,326),  
     labels = c("Primera\nRevolución Industrial\n(1750 ,carbón)", "Segunda\nRevolución Industrial\n(1850, Petróleo)"),
    cex  = 2, col = "Red4")

plot(at$TA, diox$CO2)

Y.comunes <- intersect(at$Year, diox$Y ); Y.comunes

co2.comun <- vector(mode = "numeric", length = length(Y.comunes)) #valores co2 para años comunes
at.comun <- vector(mode = "numeric", length = length(Y.comunes)) #valores anomalía térmica 
for(i in 1:length(Y.comunes)){
co2.comun[i] <- diox$CO2[diox$Y == Y.comunes[i]]
at.comun[i] <- at$TA[at$Year == Y.comunes[i]]
}
co2.comun; at.comun; length(co2.comun) == length(at.comun)

correlatio <- data.frame(Y = Y.comunes, CO2 = co2.comun, AT = at.comun);
rm(Y.comunes, co2.comun, at.comun) #borra variables de la memoria

head(correlatio)

gcor <- ggplot(data = correlatio) + 
geom_point(aes(x = CO2, y = AT, colour = "Mediciones")) + 
geom_smooth(aes(x = CO2, y = AT, colour = "Ajuste Lineal (Recta)"), method = "lm",formula = "y ~ x" ) + 
scale_colour_manual(values = c("Mediciones" = "Black", "Ajuste Lineal (Recta)" = "Blue"), name = NULL) + 
xlab(expression(CO[2] (ppm))) + ylab("Anomal. Térmica (°C)") + 
temajuan3 + 
guides(colour = guide_legend(override.aes = list(linetype = c(1,0), shape = c(NA, 16), size = c(1,2) ))) 

fig(width = 24,heigth = 12); show(gcor)

ajuste.recta <- lm(correlatio$AT ~ correlatio$CO2) # AT proporcional a c_1 + c_2 CO2
ajuste.recta

ajuste.recta$coefficients[1] #ordenada al origen
ajuste.recta$coefficients[2] #pendiente

summary.lm(ajuste.recta)$coefficients

summary.lm(ajuste.recta)$r.squared
