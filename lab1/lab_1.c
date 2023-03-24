#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<sys/time.h>

int getrand(int min,int max)
{
    return (double)rand()/(RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void counting_sort(int *arr,int count)
{
    int max = arr[0];

    for(int n = 1;n < count;n++){
        if(max < arr[n])
            max = arr[n];
    } 

    int arr_2[max + 1],arr_3[count];

    for(int n = 0;n < max + 1;n++){
        arr_2[n] = 0;
    }

    for(int n = 0;n < count;n++){
        arr_2[arr[n]]++;
    }

    for(int n = 1;n <= max;n++){
        arr_2[n] += arr_2[n - 1];
    }

    for(int n = count - 1;n >= 0;n--){
        arr_3[arr_2[arr[n]] - 1] = arr[n];
        arr_2[arr[n]]--;
    }
    
    for(int n = 0;n < count;n++){
        arr[n] = arr_3[n];
    }
}

void merge(int *arr,int low,int mid,int high)
{
    int n1 = mid - low + 1,n2 = high - mid;
    int L[n1],R[n2];
    int x = 0,y = 0,l = low;
  
    for(int n = 0;n < n1;n++){
        L[n] = arr[low + n];
    }

    for(int n = 0;n < n2;n++){
        R[n] = arr[mid + n + 1];
    }

    while(x < n1 && y < n2){
        if(L[x] <= R[y]){
            arr[l] = L[x];
            x++;        
        }else{
            arr[l] = R[y];
            y++;
        }
        l++;
    }

    while(x < n1){
        arr[l] = L[x];
        x++;
        l++;
    }

    while(y < n2){
        arr[l] = R[y];
        y++;
        l++;
    }
}

void merge_sort(int *arr,int low,int high)
{
    if(low < high){
        int mid = low + (high - low) / 2;
        merge_sort(arr,low,mid);
        merge_sort(arr,mid + 1,high);
        merge(arr,low,mid,high);
    }
}

void bubble_sort(int count,int *arr)
{
    for(int i = count - 1;i > 0;i--){
        for(int n = 0;n < i;n++){
            int x = arr[n];
            if(arr[n] > arr[n + 1]){
                arr[n] = arr[n + 1];
                arr[n + 1] = x;
            }
        }
    }
}

int main()
{
    int *arr, *arr_2, *arr_3;
    double time_counting,time_bubble,time_merge;

    printf("size\t\t\tcounting\t\t\tbublle\t\t\tmerge\n");

    for(int size = 50000;size <= 1000000;size += 50000){
        arr = (int *)malloc(sizeof(int) * size);
        assert((arr != NULL) && "Don't work arr");

        arr_2 = (int *)malloc(sizeof(int) * size);
        assert((arr_2 != NULL) && "Don't work arr 2");

        arr_3 = (int *)malloc(sizeof(int) * size);
        assert((arr_3 != NULL) && "Don't work arr 3");

        for(int n = 0;n < size;n++){
            arr[n] = arr_2[n] = arr_3[n] = getrand(0,1000);
        }

        time_counting = wtime();
        counting_sort(arr,size);
        time_counting = wtime() - time_counting;

        time_bubble = wtime();
        bubble_sort(size,arr_2);
        time_bubble = wtime() - time_bubble;

        time_merge = wtime();
        merge_sort(arr_3,0,size - 1);
        time_merge = wtime() - time_merge;
        
        for(int n = 0;n < size - 1;n++){
            assert(arr[n] <= arr[n + 1] && "Counting sort did not sorted");
        }
        
        for(int n = 0;n < size - 1;n++){
            assert(arr_2[n] <= arr_2[n + 1] && "Bublle sort did not sorted");
        }

        for(int n = 0;n < size - 1;n++){
            assert(arr_3[n] <= arr_3[n + 1] && "Merge sort did not sorted");
        }
        
        printf("%d\t\t\t%.6lf\t\t\t%.6lf\t\t\t%.6lf\n",size,time_counting,time_bubble,time_merge);

        free(arr);
        free(arr_2);
        free(arr_3);
    }
    return 0;
}