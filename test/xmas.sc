for (i=1; i<=8; i=i+1;) {
  k=0;
  for (j=1; j<=i; j=j+1;) {
    k = k*10+1;
    if ((j/2*2-j)==0) continue;
    print k;
  }
}
i=i/2;
do {
  print 88;
  i=i-1; 
  if (i==1) break;
} while (1);
