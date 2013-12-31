int iArray[10];
char cArray[10];
str sArray[10];

def int quickSort(int left, int right, str type){

  int l=left; int r=right;

  if(type == "int"){
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
  }else if(type == "char"){
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
        cArray[l]=cArray[r];
        cArray[r]=t;
        l=l+1;
        r=r-1;
      }
    }
  }else if(type == "str"){
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

def int reverse(str type){
  int i=0;
  int j=9;
  if(type == "int"){
    while(i<j){
      int t;
      t = iArray[i];
      iArray[i] = iArray[j];
      iArray[j] = t;
      i = i + 1;
      j = j - 1;
    }
  }else if(type == "char"){
    while(i<j){
      char t;
      t = cArray[i];
      cArray[i] = cArray[j];
      cArray[j] = t;
      i = i + 1;
      j = j - 1;
    }
  }else if(type == "str"){
    while(i<j){
      str t;
      t = sArray[i];
      sArray[i] = sArray[j];
      sArray[j] = t;
      i = i + 1;
      j = j - 1;
    }
  }
  return 0;
}

print "Welcome! This is an application designed for sorting!";

while(1){

  str order;
  while(1){
    print "Please enter the element order for output:";
    print "(asc for ascending order, des for descending order)";
    read order;
    if(order == "asc")
      break;
    else if(order == "des")
      break;
  }

  str type;
  print "Please enter the type of elements you would like to sort:";
  print "(int for integer, char for character, str for string)";
  read type;

  int i;
  char temp;

  if(type == "int"){

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

    quickSort(0,9,type);
    if(order == "des")
      reverse(type);

    print "after sorting:";
    for(i=0;i<10;i=i+1;){
      print iArray[i];
    }

  }else if(type == "char"){

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

    quickSort(0,9,type);
    if(order == "des")
      reverse(type);

    print "after sorting:";
    for(i=0;i<10;i=i+1;){
      print cArray[i];
    }

  }else if(type == "str"){

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

    quickSort(0,9,type);
    if(order == "des")
      reverse(type);

    print "after sorting:";
    for(i=0;i<10;i=i+1;){
      print sArray[i];
    }

  }else{
    print "Invalid type: " + type;
    print "Please try again";
    continue;
  }

  //This line is for flushing the buffer
  if(type != "str")
    read temp;

  print "Finished sorting on type " + type;

  str input;

  while(1){
    print "Would you like to try again?";
    print "(enter yes or no)";
    read input;
    if(input == "yes")
      break;
    else if(input == "no")
      break;
  }

  if(input == "yes")
    continue;
  else if(input == "no"){
    print "Thank you!";
    break;
  }

}
