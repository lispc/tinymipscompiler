int iArray[10];
char cArray[10];
str sArray[10];
def int quickSort(int left, int right, char type){
  int l=left; int r=right;

  if(type == 'i'){
    int pivot = iArray[(left+right)/2];
    while(l<=r){
      while(iArray[l] < pivot)
        l=l+1;
      while(iArray[r] > pivot)
        r=r-1;
      if(l <= r){
        int t;
        t = iArray[l];
        iArray[l]=iArray[r];
        iArray[r]=t;
        l=l+1;
        r=r-1;
      }
    }
  }else if(type == 'c'){
    char pivot = cArray[(left+right)/2];
    while(l<=r){
      while(cArray[l] < pivot)
        l=l+1;
      while(cArray[r] > pivot)
        r=r-1;
      if(l <= r){
        char t;
        t = cArray[l];
        cArray[l]=cArray[r];
        cArray[r]=t;
        l=l+1;
        r=r-1;
      }
    }
  }else if(type == 's'){
    str pivot = sArray[(left+right)/2];
    while(l<=r){
      while(sArray[l] < pivot)
        l=l+1;
      while(sArray[r] > pivot)
        r=r-1;
      if(l <= r){
        str t;
        t = sArray[l];
        sArray[l]=sArray[r];
        sArray[r]=t;
        l=l+1;
        r=r-1;
      }
    }
  }

  if(left < r)
    quickSort(left,r,type);
  if(right > l)
    quickSort(l,right,type);

  return 0;
}

char type;
print "Please enter the type of elements you want to sort:";
print "(i for integer, c for character, s for string)";
read type;

str temp; read temp;

int i;

if(type == 'i'){
  print "Please enter 10 integers for sorting:";
  for(i=0;i<10;i=i+1;){
    int t;
    read t;
    iArray[i] = t;
  }

  print "originally:";
  for(i=0;i<10;i=i+1;){
    print iArray[i];
  }

  quickSort(0,9,'i');
  print "after sorting:";
  for(i=0;i<10;i=i+1;){
    print iArray[i];
  }
}else if(type == 'c'){
  print "Please enter 10 characters for sorting:";
  for(i=0;i<10;i=i+1;){
    char t;
    read t;
    if(t == '\n'){
      i=i-1;  
    }else{
      cArray[i] = t;
    }
  }
  
  print "originally:";
  for(i=0;i<10;i=i+1;){
    print cArray[i];
  }

  quickSort(0,9,'c');
  print "after sorting:";
  for(i=0;i<10;i=i+1;){
    print cArray[i];
  }
}else if(type == 's'){
  print "Please enter 10 strings for sorting:";
  for(i=0;i<10;i=i+1;){
    str t;
    read t;
    sArray[i] = t;
  }
  
  print "originally:";
  for(i=0;i<10;i=i+1;){
    print sArray[i];
  }

  quickSort(0,9,'s');
  print "after sorting:";
  for(i=0;i<10;i=i+1;){
    print sArray[i];
  }
}
