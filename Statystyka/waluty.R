library(gdata)
library(xlsx)

tab_a = c("DATA","THB", "USD", "AUD", "HKD", "CAD", "NZD", "SGD", "EUR", "HUF", "CHF", "GBP", "UAH", "JPY", "CZK", "DKK", "ISK", "NOK", "SEK", "HRK", "RON", "BGN", "TRY",
"LTL", "LVL", "ILS", "CLP", "PHP", "MXN", "ZAR", "BRL", "MYR", "RUB", "IDR", "INR", "KRW", "CNY", "XDR", "NUMER", "PEŁNY NUMER")

input <- function(){
currency <- readline(prompt = "Prosze wpisac walute: ")
date_b <- readline(prompt = "Od: ")
date_e <- readline(prompt = "Do: ")

currency_col <- match(currency, tab_a)

return(c(currency, date_b, date_e, currency_col))
}

download_data <- function(url_data){

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

url_data <- input()
currency_col <- as.numeric(url_data[4])
data <- download_data(url_data)
currencies <- c()
dates <- c()

print(colnames(data.frame(data[1])))

wb <- createWorkbook()
index <- 1

for(i in as.numeric(url_data[2]):as.numeric(url_data[3])){
  sheet <- createSheet(wb, sheetName = as.character(i))
  addDataFrame(data[index], sheet)
  index <- index + 1
}
saveWorkbook(wb, "big_data.xlsx")

#dates_frame <- data.frame(data[1])

#for(i in 1:nrow(data.frame(data[1]))){
 # dates <- c(dates, as.character(dates_frame[i,1]))
#}
#dates <- dates[-1]
#print(dates)
