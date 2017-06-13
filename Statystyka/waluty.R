library(readxl)
library(xlsx)

input <- function(){  # Funkcja odpowiedzialna za informacje podawane przez użytkownika.
currency <- readline(prompt = "Prosze wpisac walute: ")
date_b <- readline(prompt = "Od (prosze wpisac w formacie YYYY-MM-DD): ")
date_e <- readline(prompt = "Do prosze wpisac w formacie YYYY-MM-DD): ")

return(c(currency, date_b, date_e))
}

download_data <- function(url_data){ # Funkcja odpowiedzialna za ściąganie danych z serisu NBP.

  table_list <- c()
  
  year_b <- strsplit(url_data[2],"-") # Obrabiamy datę.
  year_b <- year_b[[1]]
  year_b <- year_b[1]
  year_e <- strsplit(url_data[3], "-")
  year_e <- year_e[[1]]
  year_e <- year_e[1]

for(i in as.numeric(year_b):as.numeric(year_e)){
  
  url <- "http://www.nbp.pl/kursy/Archiwum/archiwum_tab_a_"
  table <- NULL
  url <- paste(url, as.character(i), ".xls", sep = "") # Składamy odpowiedni URL
  destfile <- paste(as.character(i), ".xls", sep = "") # Tworzymy plik Excela
  download.file(url, destfile) # Ściągamy do niego dane
  if(i < 2000){
  table <- read_excel(destfile, skip = 1) # Odpowiednio go czytamy.
  }else if(i == 2004){
    table <- read_excel(destfile, col_types = c("date", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text"))
  }else if(i == 2005){
    table <- read_excel(destfile, col_types = c("date", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "numeric", "text", 
                  "text"))
  }else if(i == 2009 || i == 2010){
    table <- read_excel(destfile, col_types = c("date", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "numeric", 
                  "text", "text"))
  }else if(i == 2011){
    table <- read_excel(destfile, col_types = c("date", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "text", "text", "text", "text", "text", 
                  "numeric", "text", "text"))
  }else if(i == 2013){
    table <- read_excel(destfile, col_types = c("date", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "numeric", "text")) # Wewnętrzne kodowanie Excela, trzeba zmienić typy kolumn.
  }else if(i == 2014){
    table <- read_excel(destfile, col_types = c("date", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "numeric", 
                                                "text"))
  }else if(i > 2014){
    table <- read_excel(destfile, col_types = c("date", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "text", "text", 
                                                "text", "text", "text", "numeric", 
                                                "text"))
  }else{
    table <- read_excel(destfile)
  }
  table_list <- c(table_list, list(table))
}
return(table_list)
}

####################################################################################################

url_data <- input() # Uzyskujemy informacje od użytkownika.
data <- download_data(url_data) # Ściągamy dane z serwisu NBP.

wb <- createWorkbook() # Lokalnie tworzymy nasz plik .xlsx (może się przyda)
index_df <- 1

year_b <- strsplit(url_data[2],"-") # Obrabiamy datę.
year_b <- year_b[[1]]
year_b <- year_b[1]
year_e <- strsplit(url_data[3], "-")
year_e <- year_e[[1]]
year_e <- year_e[1]

#for(i in as.numeric(year_b):as.numeric(year_e)){ # W przedziale dat podanych przez użytkownika
#  sheet <- createSheet(wb, sheetName = as.character(i)) # tworzymy dla każdej z nich oddzielny arkusz
#  addDataFrame(data[index_df], sheet) # dodajemy do niego odpowiednią ramkę danych
#  index_df <- index_df + 1
#}
#saveWorkbook(wb, "big_data.xlsx") # i zapisujemy cały plik.

index_df <- 1

for(i in 1:length(data)){
  print(head(data[i]))
}

for(i in as.numeric(year_b):as.numeric(year_e)){
  if(i >= 1996 && i < 2000){
  }
  index_df <- index_df + 1
}
