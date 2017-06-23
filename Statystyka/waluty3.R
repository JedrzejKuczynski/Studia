library(readxl)
library(tseries)

input <- function() {  # Funkcja odpowiedzialna za informacje podawane przez u?ytkownika.
  currency <- readline(prompt = "Prosze wpisac walute: ")
  date_b <- readline(prompt = "Od (prosze wpisac w formacie YYYY-MM-DD): ")
  date_e <- readline(prompt = "Do prosze wpisac w formacie YYYY-MM-DD): ")
  return(c(currency, date_b, date_e))
}

# url_data <- c("USD", "1996-01-01", "2000-06-01")

download_data <- function(url_data) { # Funkcja odpowiedzialna za sciaganie danych z serisu NBP.
  
  urlb <- "http://www.nbp.pl/kursy/Archiwum/archiwum_tab_a_" # Bazowy URL do sciagania danych
  col_types <- c("date", rep("text", 26)) # Definiujemy typy kolumn dla plików excelowych
  
  year_b <- 1900 + as.POSIXlt(url_data[2])$year # Definiujemy zakres lat sciaganych plików
  year_e <- 1900 + as.POSIXlt(url_data[3])$year # (kolumna year klasy POSIXlt zawiera liczbę lat od 1900 roku)
  y <- year_b:year_e # Wektor zawierający nasze lata
  n <- length(y) # Zmienna pomocnicza zawierajaca długosc naszego wektora
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
    } else if(yi == 2005) {
      col_t <- col_types
      table <- read_excel(destfile, col_types = col_t)
    } else if(yi %in% 2009:2010) {
      col_t <- c(col_types, rep("text", 12))
      col_t[37] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
    } else if(yi == 2011) {
      col_t <- c(col_types, rep("text", 14))
      col_t[39] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
    } else if(yi == 2013) {
      col_t <- c(col_types, rep("text", 13))
      col_t[39] <- "numeric"
      table <- read_excel(destfile, col_types = col_t) 
    } else if(yi == 2014) {
      col_t <- c(col_types, rep("text", 12))
      col_t[38] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
    } else if(yi > 2014) {
      col_t <- c(col_types, rep("text", 11))
      col_t[37] <- "numeric"
      table <- read_excel(destfile, col_types = col_t)
    } else table <- read_excel(destfile)
    
    table_list[[i]] <- table
  }
  return(table_list)
}

###############################################################################

# url_data <- input() # Uzyskujemy informacje od uzytkownika.
data <- download_data(url_data) # Sciagamy dane z serwisu NBP.

idd <- sapply(data, function(x) grep("Data", names(x))) # Przechodzimy po naszych nazwach kolumn naszych danych i szukamy indeksow kolumn zawierajacych daty
idv <- sapply(data, function(x) grep(url_data[1], names(x))) # To samo, tylko ze z interesujaca nas waluta
n <- length(idd)

nam <- c("Data", url_data[1]) # Wektor nazw (Data i odpowiedni trzyliterowy skrót waluty)
dane <- NULL
for(i in 1:n) {
  tmp <- data[[i]] # Zmienna pomocnicza przechowujaca dana ramke
  d <- tmp[idd[i]] # Zmienna przechowujaca cala kolumne dat z ramki
  w <- tmp[idv[i]] # Zmienna przechowujaca cala kolumne wartosci z ramki
  q <- cbind(d, w); names(q) <- nam # Laczymy nasze kolumny w jedna ramke, a kolumnom nadajemy odpowiednie nazwy
  dane <- rbind(dane, q) # Laczymy nasze wyciagnete kolumny Data-Waluta w jedna ramke
                         # (tj. ramke zawierajaca dany przedzial dat)
}

tmp <- dane$Data
date_b <- as.POSIXlt(url_data[2])
date_e <- as.POSIXlt(url_data[3])

for(i in 1:length(tmp)){ # Wyszukujemy indeksow interesujacych nas dat
  if(tmp[i] >= date_b){
    idb <- i
    break
  }
}

for(i in 1:length(tmp)){ # To jest daty poczatkowej i koncowej
  if(tmp[i] >= date_e){
    ide <- i
    break
  }
}
dane <- dane[c(idb:ide),] # Ograniczamy ramke

names(dane) <- nam
summary(dane)
plot(dane, type = "l")
