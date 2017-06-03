library(gdata)

tab_a = c("DATA","THB", "USD", "AUD", "HKD", "CAD", "NZD", "SGD", "EUR", "HUF", "CHF", "GBP", "UAH", "JPY", "CZK", "DKK", "ISK", "NOK", "SEK", "HRK", "RON", "BGN", "TRY",
"LTL", "LVL", "ILS", "CLP", "PHP", "MXN", "ZAR", "BRL", "MYR", "RUB", "IDR", "INR", "KRW", "CNY", "XDR", "NUMER", "PEŁNY NUMER")
tab_b = c("DATA","AFN", "MGA", "PAB", "ETB", "VEF", "BOB", "GHS", "CRC", "SVC", "NIO", "GMD", "MKD", "DZD", "BHD", "IQD", "JOD", "KWD", "LYD", "RSD", "TND", "MAD", "AED", "STD", "BSD",
"BBD", "BZD", "BND", "FJD", "GYD", "JMD", "LRD", "NAD", "SRD", "TTD", "XCD", "SBD", "ZWL", "VND", "AMD", "CVE", "BIF", "XOF", "XAF", "XPF", "DJF", "GNF", "KMF", "CDF",
"RWF", "EGP", "GIP", "LBP", "SDG", "SYP", "HTG", "PYG", "ANG", "AWG", "PGK", "LAK", "MWK", "ZMK", "AOA", "MMK", "GEL", "MDL", "ALL", "HNL", "SLL", "SZL", "LSL",
"AZN", "MZN", "NGN", "ERN", "TWD", "PEN", "MRO", "TOP", "MOP", "ARS", "DOP", "COP", "UYU", "BWP", "GTQ", "IRR", "YER", "QAR", "OMR", "SAR", "KHR", "BYR",
"MVR", "MUR", "NPR", "PKR", "SCR", "LKR", "KGS", "TJS", "UZS", "KES", "SOS", "TZS", "UGX", "BDT", "WST", "KZT", "MNT", "VUV", "BAM", "NUMER", "PEŁNY NUMER")

input <- function(){
currency <- readline(prompt ="Prosze wpisac walute: ")
date <- readline(prompt ="Prosze wpisac rok: ")

if(is.element(currency, tab_a)){
  currency_col <- match(currency, tab_a)
}else{
  currency_col <- match(currency, tab_b)
}
return(c(currency, date, currency_col))
}

download_data <- function(url_data){

url <- "http://www.nbp.pl/kursy/Archiwum/archiwum_tab_"

if(is.element(url_data[1], tab_a)){
  url <- paste(url, "a_", sep = "")
}else{
  url <- paste(url, "b_", sep = "")
}

url <- paste(url, as.character(url_data[2]), ".xls", sep = "")
table <- read.xls(url)
return(table)
}

####################################################################################################

url_data <- input()
currency_col <- as.numeric(url_data[3])
data <- download_data(url_data)
currencies <- c()
dates <- c()

for(i in 1:nrow(data)){
  dates <- c(dates, as.character(data[i,1]))
}
dates <- dates[-1]

for(i in 1:ncol(data)){
  currencies <- c(currencies, as.character(data[1,i]))
}
currencies <- currencies[-c(1, length(currencies), length(currencies)-1)]

print(length(tab_a))
print(length(tab_b))
print(currency_col)
print(data[ ,currency_col])