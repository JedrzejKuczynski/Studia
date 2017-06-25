laczna <- function(a, b, c){
  if(missing(b) & missing(c)){
    factorial = 1
    for(i in 1:a){
      factorial =  factorial * i
    } 
    return(factorial)
  }else if(missing(c) & is.numeric(a)){
    sum = a^2 + b^2
    c = sqrt(sum)
    return(c)
  }else if(a == "suma"){
    sum = (b*(b+1))/2
    return(sum)
  }else if(a == "iloczyn"){
    multi = 1
    for(i in 1:b){
      if(i %% 2 != 0){
        multi = multi * i
      }
    }
    return(multi)
  }
  else{
    delta = b^2 - 4*a*c
    print(delta)
    if(delta < 0){
      return("BRAK PIERWIASTKÓW")
    }else if(delta == 0){
      r = -b/(2*a)
      return(r)
    }else{
      delta = sqrt(delta)
      r1 = (-b + delta)/(2*a)
      r2 = (-b - delta)/(2*a)
      return(list(r1, r2))
    }
  }
}

laczna("iloczyn", 6)