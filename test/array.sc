Array a[6];
a[0]=1;
a[1]=2;
a[2]=2;
a[3]=3;
a[4]=3;
a[5]=3;
i=0;
while(i<6)
{
	print a[i];
	i = i + 1;
}
i=0;
while(i<6)
{
	a[i] = a[i] + 1;  //a=[2,3,3,4,4,4]
	i = i + 1;
}
i=-1;
while(i<5){
        print a[i+1];
        i = i + 1;
}
print a[a[0]];
print a[a[5]];
print a[a[1]==3];
a[a[5]]=7;
print a[a[5]];
