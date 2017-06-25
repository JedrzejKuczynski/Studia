library(readxl)
library(vioplot)
library(e1071)

input <- function() {  # Funkcja odpowiedzialna za informacje podawane przez uzytkownika.
  currency <- readline(prompt = "Prosze wpisac walute: ")
  date_b <- readline(prompt = "Od (prosze wpisac w formacie YYYY-MM-DD): ")
  date_e <- readline(prompt = "Do prosze wpisac w formacie YYYY-MM-DD): ")
  return(c(currency, date_b, date_e))
}

url_data <- c("USD", "1996-01-01", "2017-03-12")

download_data <- function(url_data) { # Funkcja odpowiedzialna za sciaganie danych z serisu NBP.
  
  urlb <- "http://www.nbp.pl/kursy/Archiwum/archiwum_tab_a_" # Bazowy URL do sciagania danych
  col_types <- c("date", rep("text", 26)) # Definiujemy typy kolumn dla plików excelowych
  
  year_b <- 1900 + as.POSIXlt(url_data[2])$year # Definiujemy zakres lat sciaganych plików
  year_e <- 1900 + as.POSIXlt(url_data[3])$year # (kolumna year klasy POSIXlt zawiera liczbę lat od 1900 roku)
  y <- year_b:year_e # Wektor zawierający nasze lata
  n <- length(y) # Zmienna pomocnicza zawierajaca dlugosc naszego wektora
  table_list <- vector("list", n) # Definicja listy ramek
  names(table_list) <- y # Ustalamy nazwy dla naszych poszczegolnych ramek
  
  for(i in 1:n) { # Sciagamy dane
    yi <- y[i] # Zmienna przechowujaca dany rok uzywana podczas skladania URL
    url <- paste0(urlb, yi, ".xls") # Skladamy odpowiedni URL
    destfile <- paste0(yi, ".xls") # Tworzymy plik Excela
    download.file(url, destfile, mode = "wb") # Sciagamy do niego dane
    
    if(yi < 2000) { # Odpowiednie wczytywanie poszczegolnych plikow do naszej listy ramek, ewentualna zamiana nazw kolumn i ich typow itp.
      table <- read_excel(destfile, skip = 1)
    } else if(yi == 2000) {
      table <- read_excel(destfile)
      names(table)[1] <- "Data"
    } else if(yi == 2004){
      table <- read_excel(destfile, col_types = col_types)
      table <- data.frame(head(table, -4))
      names(table)[1] <- "Data"
    } else if(yi == 2005) {
      col_t <- c(col_types, "text")
      table <- read_excel(destfile, col_types = col_t)
      table <- data.frame(head(table, -5))
      table <- data.frame(tail(table, -1))
      names(table)[1] <- "Data"
    } else if(yi == 2006) {
      col_t <- c(col_types, "text")
      table <- read_excel(destfile, col_types = col_t)
      table <- data.frame(tail(table, -1))
      names(table)[1] <- "Data"
    } else if(yi == 2007) {
      col_t <- c(col_types, rep("text", 15))
      table <- read_excel(destfile, col_types = col_t)
      table <- data.frame(tail(table, -1))
      names(table)[1] <- "Data"
    } else if(yi == 2008) {
      table <- read_excel(destfile)
      table <- data.frame(head(table, -5))
      table <- data.frame(tail(table, -2))
      names(table)[1] <- "Data"
    } else if(yi == 2009) {
      col_t <- c(col_types, rep("text", 12))
      col_t[37] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
      table <- data.frame(head(table, -5))
      table <- data.frame(tail(table, -2))
      names(table)[1] <- "Data"
    } else if(yi == 2010) {
      col_t <- c(col_types, rep("text", 12))
      col_t[37] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
      table <- data.frame(head(table, -5))
      table <- data.frame(tail(table, -1))
      names(table)[1] <- "Data"
    } else if(yi == 2011) {
      col_t <- c(col_types, rep("text", 14))
      col_t[39] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
      table <- data.frame(head(table, -5))
      table <- data.frame(tail(table, -1))
      names(table)[1] <- "Data"
    }else if(yi == 2012) {
      table <- read_excel(destfile)
      table <- data.frame(tail(table, -1))
      names(table)[1] <- "Data"
    }else if(yi == 2013) {
      col_t <- c(col_types, rep("text", 13))
      col_t[39] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
      table <- data.frame(head(table, -4))
      table <- data.frame(tail(table, -1))
      names(table)[1] <- "Data"
    } else if(yi == 2014) {
      col_t <- c(col_types, rep("text", 12))
      col_t[38] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
      table <- data.frame(head(table, -4))
      table <- data.frame(tail(table, -1))
      names(table)[1] <- "Data"
    } else if(yi > 2014) {
      col_t <- c(col_types, rep("text", 11))
      col_t[37] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
      table <- data.frame(head(table, -4))
      table <- data.frame(tail(table, -1))
      names(table)[1] <- "Data"
    } else {
      table <- read_excel(destfile)
      names(table)[1] <- "Data"
    }
    table_list[[i]] <- table
  }
  return(table_list)
}

###############################################################################

url_data <- input() # Uzyskujemy informacje od uzytkownika.
data <- download_data(url_data) # Sciagamy dane z serwisu NBP.


idd <- sapply(data, function(x) grep("Data", names(x))) # Przechodzimy po nazwach kolumn naszych danych i szukamy indeksow kolumn zawierajacych daty
idv <- sapply(data, function(x) grep(url_data[1], names(x))) # To samo, tylko ze z interesujaca nas waluta
n <- length(idd)

nam <- c("Data", url_data[1]) # Wektor nazw (Data i odpowiedni trzyliterowy skrót waluty)
dane <- NULL
for(i in 1:n){
  tmp <- data[[i]] # Zmienna pomocnicza przechowujaca dana ramke
  d <- tmp[as.numeric(idd[i])] # Zmienna przechowujaca cala kolumne dat z ramki
  w <- tmp[as.numeric(idv[i])] # Zmienna przechowujaca cala kolumne wartosci z ramki
  q <- cbind(d, w); names(q) <- nam # Laczymy nasze kolumny w jedna ramke, a kolumnom nadajemy odpowiednie nazwy
  dane <- rbind(dane, q) # Laczymy nasze wyciagnete kolumny Data-Waluta w jedna ramke
                         # (tj. ramke zawierajaca dany przedzial 'calych' lat)
}

tmp <- dane$Data
date_b <- as.POSIXlt(url_data[2])
date_e <- as.POSIXlt(url_data[3])

for(i in 1:length(tmp)){ # Wyszukujemy indeksy interesujacych nas dat
  if(as.POSIXlt(tmp[i]) >= date_b){
    idb <- i
    break
  }
}

for(i in 1:length(tmp)){ # To jest daty poczatkowej i koncowej
  if(as.POSIXlt(tmp[i]) >= date_e){
    ide <- i
    break
  }
}
dane <- dane[c(idb:ide),] # Ograniczamy ramke
dane_obl <- as.numeric(dane[,2])

# Liczymy odpowiednie parametry i rysujemy wykresy

names(dane) <- nam
cat("Wielkosc proby: ", length(dane_obl))
cat("Srednia geometryczna: ", exp(mean(log(dane_obl))))
cat("Srednia harmoniczna: ", 1/mean(1/dane_obl))
cat("Wariancja: ", var(dane_obl))
cat("Odchylenie standardowe: ", sd(dane_obl))
cat("Przedzial zmiennosci: (", round(mean(dane_obl) - sd(dane_obl), 5), ";", round(mean(dane_obl) + sd(dane_obl), 5), ")", sep = "")
cat("Moda: ", as.numeric(names(sort(-table(dane_obl))))[1])
cat("Kurtoza: ", kurtosis(dane_obl))
cat("Skosnosc: ", skewness(dane_obl))
summary(dane)
plot(dane, type = "l", main = "Kurs waluty")
plot(dane, main = "Kurs waluty")
hist(dane_obl, main = nam[2], xlab = "Kurs")
boxplot(dane_obl, main = nam[2], horizontal = TRUE, xlab = "Kurs")
vioplot(dane_obl, col = "yellow", names = nam[2], horizontal = TRUE)