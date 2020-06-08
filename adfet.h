#define type_of(expr) \
    (_Generic((expr), \
              char: "char", unsigned char: "unsigned char", signed char: "signed char", \
              short: "short", unsigned short: "unsigned short", \
              int: "int", unsigned int: "unsigned int", \
              long: "long", unsigned long: "unsigned long", \
              long long: "long long", unsigned long long: "unsigned long long", \
              float: "float", \
              double: "double", \
              long double: "long double", \
              void*: "void*", \
              char*: "char*",  \
              int*: "int*",  \
              char**: "char**",  \
              int**: "int**",  \
			  char***: "char***",  \
              int***: "int***",  \
			  char****: "char****",  \
              int****: "int****",  \
              default: "?"))
#define sort(array,size,...) (type_of(array) == "int*") ? _Sort( array,size, (0, ##__VA_ARGS__) ) : _Sortc( array,size, (0, ##__VA_ARGS__) )
#define len(array) (type_of(array) == "int*") ? sizeof(array)/sizeof(array[0]) : _length(array)
#define replace( string, old_char ,new_char ,...) _replace( string, old_char, new_char, /*no_of_character to be replaced*/(-1,##__VA_ARGS__))
#define print(array, size, ...) (type_of(array) == "int*") ?  _printi(array, size, ('`',##__VA_ARGS__)) : _printc(array, size, ('`',##__VA_ARGS__))
#define slice(array, start, end, ...) (type_of(array) == "int*") ?  _slicei(array, start, end, (1,##__VA_ARGS__)) : _slicec(array, start, end, (1,##__VA_ARGS__))
#define compare(array_1, size_1, array_2, size_2, ...) (type_of(array_1) == "int*") ?  _comparei(array_1, size_1, array_2, size_2, (0,##__VA_ARGS__)) : _comparec(array_1, size_1, array_2, size_2, (0,##__VA_ARGS__))

// C program to perform TimSort.
void _rev(int *a, int n);
int _min(int n,int m);
void _insertionSort(int arr[], int left, int right);
void _timSort(int arr[], int n, int reverse);
void _merge(int *arr, int l, int m, int r);


const int RUN = 32;

int _min(int n,int m){
    if (n<m) return n;
    return m;
}

void _insertionSort(int *arr, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int temp = arr[i];
		int j = i - 1;
		while (j >= left && arr[j] > temp)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = temp;
	}
}


void _merge(int *arr, int l, int m, int r)
{

	int len1 = m - l + 1, len2 = r - m;
	int left[len1], right[len2];
	for (int i = 0; i < len1; i++)
		left[i] = arr[l + i];
	for (int i = 0; i < len2; i++)
		right[i] = arr[m + 1 + i];

	int i = 0;
	int j = 0;
	int k = l;


	while (i < len1 && j < len2)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}

	// copy remaining elements of left, if any
	while (i < len1)
	{
		arr[k] = left[i];
		k++;
		i++;
	}

	while (j < len2)
	{
		arr[k] = right[j];
		k++;
		j++;
	}
}

void _Sort(int *arr, int n, int reverse)
{

	for (int i = 0; i < n; i+=RUN)
		_insertionSort(arr, i, _min((i+31), (n-1)));


	for (int size = RUN; size < n; size = 2*size)
	{

		for (int left = 0; left < n; left += 2*size)
		{

			int mid = left + size - 1;
			int right = _min((left + 2*size - 1), (n-1));

			_merge(arr, left, mid, right);
		}
	}

    if (reverse == -1)
        _rev(arr,n);
}

void _Sortc(char *arr, int n, int reverse){

	int a[n];

	for(int i=0;i<n;i++){

		a[i] = (int)(arr[i]);
	}

	_Sort(a,n,reverse);

	for(int i=0;i<n;i++){

		arr[i] = (char)(a[i]);
	}

}
void _rev(int *a, int n){


    for(int i=0;i<=n/2;i++){
        int t = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = t;
    }
}

// replace n chararters in a string (Note : It is important to use array of characters instead of pointers as it will raise bus error)
void _replace(char *s,char oc,char nc,int no_of_c){

	int c = 0,n = 0;
	
	if (no_of_c < -1)
		return;

	for(int i=0;s[i] != '\0';i++)
	{
		if (no_of_c !=-1 && no_of_c == c)
		{
			break;
		}
		else if(s[i] == oc)
		{
			s[i] = nc;
			c++;
		}
	}
}

// length of string
int _length(char *s){
	// printf("%d\n",type_of(s) == "char*");
	int c = 0;
	while(*s++)
	 	c++;
	return c;
}

void _printc(char *s,int n,char c){
	// printf("c = %c s = %d\n",c,n);
	if (c=='`'){
		for(int i=0;i<n;i++){
			printf("%c",s[i]);
		}
	}
	else{
		for(int i=0;i<n;i++){
			if(i == n-1)
				printf("%c",s[i]);
			else
				printf("%c%c",s[i],c);
		}
	}
}
void _printi(int *s,int n,char c){
	// printf("c = %c s = %d\n",c,n);
	if (c=='`'){
		for(int i=0;i<n;i++){
			printf("%d",s[i]);
		}
	}
	else{
		for(int i=0;i<n;i++){
			if(i == n-1)
				printf("%d",s[i]);
			else
				printf("%d%c",s[i],c);
		}
	}
}

char *_slicec(char *s,int initial,int n,int step){

	char *arr = (char *)malloc(n*sizeof(char));
	for(int i=0;i<=(n-initial);i+=step){
		arr[i] = s[initial+i];
	}
	return arr;
}
int * _slicei(int *s,int initial,int n,int step){

	int *arr = (int *)malloc(n*sizeof(int));
	for(int i=0;i<=(n-initial);i+=step){
		arr[i] = s[initial+i];
	}
	return arr;
}
int _comparei(int *a,int la, int *b, int lb,int p){

	if (la!=lb){
		if (p == 1)
			printf("\nUequal Lengths.\n");
		return 0;
	}
	else{
		for(int i=0;i<la;i++)
		{
			if (a[i]!=b[i]){
				if (p == 1)
					printf("\nElement %d is not matching.\n",i);
				return 0;
			}
			
		}
	}
	return 1;
}
int _comparec(char *a,int la, char *b, int lb,int p){

	if (la!=lb){
		if (p == 1)
			printf("\nUequal Lengths.\n");
		return 0;
	}
	else{
		for(int i=0;i<la;i++)
		{
			if (a[i]!=b[i]){
				if (p == 1)
					printf("\nElement %d is not matching.\n",i);
				return 0;
			}
		}
	}
	return 1;
}