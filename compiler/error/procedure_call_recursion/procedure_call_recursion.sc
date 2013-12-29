i = 3;

def fact(x) {
  t = x;
  if(t==0) return 1;
  else  return t*fact(x-1);
}

print fact(i);
