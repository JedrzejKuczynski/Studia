library(gdata)
library(xlsx)

input <- function(){  # Funkcja odpowiedzialna za informacje podawane przez użytkownika.
currency <- readline(prompt = "Prosze wpisac walute: ")
date_b <- readline(prompt = "Od: ")
date_e <- readline(prompt = "Do: ")

return(c(currency, date_b, date_e))
}

download_data <- function(url_data){ # Funkcja odpowiedzialna za ściąganie danych z serisu NBP.

  table_list <- c()

for(i in as.numeric(url_data[2]):as.numeric(url_data[3])){
  
  url <- "http://www.nbp.pl/kursy/Archiwum/archiwum_tab_a_"
  table <- NULL
  url <- paste(url, as.character(i), ".xls", sep = "")
  table <- read.xls(url)
  table_list <- c(table_list, list(table))
}

return(table_list)
}

####################################################################################################

url_data <- input() # Uzyskujemy informacje od użytkownika.
data <- download_data(url_data) # Ściągamy dane z serwisu NBP.

wb <- createWorkbook() # Lokalnie tworzymy nasz plik .xlsx, aby go przeparsować
index <- 1

for(i in as.numeric(url_data[2]):as.numeric(url_data[3])){ # W przedziale dat podanych przez użytkownika
  sheet <- createSheet(wb, sheetName = as.character(i)) # tworzymy dla każdej z nich oddzielny arkusz
  addDataFrame(data[index], sheet) # dodajemy do niego odpowiednią ramkę danych
  index <- index + 1
}
saveWorkbook(wb, "big_data.xlsx") # i zapisujemy cały plik.
