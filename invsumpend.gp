primend(x,sfx,target) = {
 local(delta=target-sfx,p);
 if(delta >= 0,
   p=nextprime(x+1);
   while(delta >= p,  
    delta=delta-p; p=nextprime(p+1));return([precprime(p-1),p,delta]),
   p=precprime(x);	   
   while(delta <0, 
    delta=delta+p; p=precprime(p-1));return([p,nextprime(p+1),delta]))
}


primesum(x1,x2) = {
 local(p,som);
 p=nextprime(x1);
 while(p <= x2,
  som = som+p;
  p=nextprime(p+1));
 return(som);
}

