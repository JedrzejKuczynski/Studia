library(readxl)
library(xlsx)

# input <- function() { 
#   # Funkcja odpowiedzialna za informacje podawane przez u?ytkownika.
#   currency <- readline(prompt = "Prosze wpisac walute: ")
#   date_b <- readline(prompt = "Od (prosze wpisac w formacie YYYY-MM-DD): ")
#   date_e <- readline(prompt = "Do prosze wpisac w formacie YYYY-MM-DD): ")
#   return(c(currency, date_b, date_e))
# }

url_data <- c("USD", "1996-01-01", "2000-06-01")

download_data <- function(url_data) { 
  # Funkcja odpowiedzialna za ?ci?ganie danych z serisu NBP.
  
  urlb <- "http://www.nbp.pl/kursy/Archiwum/archiwum_tab_a_"
  col_types <- col_t <- c("date", rep("text", 26))
  
  year_b <- 1900 + as.POSIXlt(url_data[2])$year
  year_e <- 1900 + as.POSIXlt(url_data[3])$year
  y <- year_b:year_e
  n <- length(y)
  table_list <- vector("list", n)
  names(table_list) <- y
  
  for(i in 1:n) {
    yi <- y[i]
    url <- paste0(urlb, yi, ".xls") # Sk?adamy odpowiedni URL
    destfile <- paste0(yi, ".xls") # Tworzymy plik Excela
    download.file(url, destfile, mode = "wb") # ?ci?gamy do niego dane
    
    if(yi < 2000) {
      table <- read_excel(destfile, skip = 1) # Odpowiednio go czytamy.
    } else if(yi == 2004){
      table <- read_excel(destfile, col_types = col_types)
    } else if(yi == 2005) {
      col_t <- col_types
      # col_t[26] <- NULL
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
      # Wewn?trzne kodowanie Excela, trzeba zmieni? typy kolumn.
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

# url_data <- input() # Uzyskujemy informacje od u?ytkownika.
USDdata <- download_data(url_data) # ?ci?gamy dane z serwisu NBP.

library(lubridate)
str(USDdata)
tmp <- USDdata[[5]]
is.Date(tmp[, 1])

apply(tmp, 2, is.POSIXt)

(idd <- c("date", "Data", "") %in% names(tmp))
(idw <- grep(url_data[1], names(tmp)))

lapply(USDdata, function(x) grep("Data", names(x)))


index_df <- 1
dates <- c()
values <- c()
indices <- c()
