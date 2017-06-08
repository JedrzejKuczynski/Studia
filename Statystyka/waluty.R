library(gdata)

tab_a = c("DATA","THB", "USD", "AUD", "HKD", "CAD", "NZD", "SGD", "EUR", "HUF", "CHF", "GBP", "UAH", "JPY", "CZK", "DKK", "ISK", "NOK", "SEK", "HRK", "RON", "BGN", "TRY",
"LTL", "LVL", "ILS", "CLP", "PHP", "MXN", "ZAR", "BRL", "MYR", "RUB", "IDR", "INR", "KRW", "CNY", "XDR", "NUMER", "PEŁNY NUMER")
# TU TRZA DOPISAC NA INNE LATA

input <- function(){
currency <- readline(prompt = "Prosze wpisac walute: ")
date_b <- readline(prompt = "Od: ")
date_e <- readline(prompt = "Do: ")
currency_col <- match(currency, tab_a)

return(c(currency, date_b, date_e, currency_col))
}

download_data <- function(url_data){

url <- "http://www.nbp.pl/kursy/Archiwum/archiwum_tab_"

if(is.element(url_data[1], tab_a)){  # tu trza zmienic
  url <- paste(url, "a_", sep = "")
}else{
  url <- paste(url, "b_", sep = "")
}

url <- paste(url, as.character(url_data[2]), ".xls", sep = "") # tu trza zmienic
table <- read.xls(url)
return(table)
}

####################################################################################################

url_data <- input()
currency_col <- as.numeric(url_data[3]) # tu trza zmienic
data <- download_data(url_data)
currencies <- c()
dates <- c()

for(i in 1:nrow(data)){
  dates <- c(dates, as.character(data[i,1])) # tu trza sprawdzic
}
dates <- dates[-1] # tu trza sprawdzic

for(i in 1:ncol(data)){ # tu trza sorawdzic
  currencies <- c(currencies, as.character(data[1,i]))
}
currencies <- currencies[-c(1, length(currencies), length(currencies)-1)]

print(length(tab_a))
print(length(tab_b))
print(currency_col)
print(data[ ,currency_col])
