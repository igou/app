void insertsort(int a[],int length)
{
	int index;
	int tmp;
	int i;
	
	for(i=0;i<length;i++)
		printf("%d,",a[i]);	
		printf("\n\n");
	for(index=1;index<length;index++)
	{
		if(a[index]<a[index-1])
		{
			i = index;
			while(i>0&&a[i]<a[i-1])
				{
					tmp = a[i];
					a[i]= a[i-1];
					a[i-1]= tmp;
					i--;					
				}
			}
	}
	for(i=0;i<length;i++) 
		printf("%d,",a[i]);	
}
