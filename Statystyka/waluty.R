library(gdata)

tab_a = c("THB", "USD", "AUD", "HKD", "CAD", "NZD", "SGD", "EUR", "HUF", "CHF", "GBP", "UAH", "JPY", "CZK", "DKK", "ISK", "NOK", "SEK", "HRK", "RON", "BGN", "TRY",
"ILS", "CLP", "PHP", "MXN", "ZAR", "BRL", "MYR", "RUB", "IDR", "INR", "KRW", "CNY", "XDR")
tab_b = c("AFN", "MGA", "PAB", "ETB", "VEF", "BOB", "CRC", "SVC", "NIO", "GMD", "MKD", "DZD", "BHD", "IQD", "JOD", "KWD", "LYD", "RSD", "TND", "MAD", "AED", "STD", "BSD",
"BBD", "BZD", "BND", "FJD", "GYD", "JMD", "LRD", "NAD", "SRD", "TTD", "XCD", "SBD", "VND", "AMD", "CVE", "AWG", "BIF", "XOF", "XAF", "XPF", "DJF", "GNF", "KMF", "CDF",
"RWF", "EGP", "GIP", "LBP", "SSP", "SDG", "SYP", "GHS", "HTG", "PYG", "ANG", "PGK", "LAK", "MWK", "ZMW", "AOA", "MMK", "GEL", "MDL", "ALL", "HNL", "SLL", "SZL", "LSL",
"AZN", "MZN", "NGN", "ERN", "TWD", "TMT", "PEN", "MRO", "TOP", "MOP", "ARS", "DOP", "COP", "CUP", "UYU", "BWP", "GTQ", "IRR", "YER", "QAR", "OMR", "SAR", "KHR", "BYN",
"LKR", "MVR", "MUR", "NPR", "PKR", "SCR", "KGS", "TJS", "UZS", "KES", "SOS", "TZS", "UGX", "BDT", "WST", "KZT", "MNT", "VUV", "BAM")

input <- function(){
currency <- readline(prompt ="Prosze wpisac walute: ")
date <- readline(prompt ="Prosze wpisac rok: ")

return(c(currency, date))
}

download_data <- function(){
  
url_data <- input()
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

data <- download_data()
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