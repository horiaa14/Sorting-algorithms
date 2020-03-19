#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<sys/time.h>
#include<unordered_map>
#include<random>
#define MAX_SIZE 500000
#define CONST_LIMIT 30000
#define BASE 10
#define BITS 16
#define MASK ((1 << BITS) - 1)
#define NR_BUCKETS 10
using namespace std;

unordered_map<int, string> umap;

bool isSorted(vector<int>& v) {
    int l = v.size();
    for(int i = 1; i < l; i++)
        if(v[i] < v[i - 1])
            return false;
    return true;
}

void bubbleSort(vector<int> &v, int nr, int Max) {
    if(nr > CONST_LIMIT) {
        cout << "Bubble Sort -- NO -- " << nr << " " << Max << " ???\n";
    } else {
        struct timeval tv;
        int tstart, tend;
        gettimeofday( &tv, NULL );
        tstart = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        bool ok;
        int n = v.size();
        do {
            ok = true;
            for(int i = 0; i < n - 1; i++) {
                if(v[i] > v[i + 1]) {
                    swap(v[i], v[i + 1]);
                    ok = false;
                }
            }
        } while(!ok);
        gettimeofday(&tv, NULL);
        tend = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        cout << "BubbleSort " << umap[isSorted(v)] << " " << nr << " " << Max << " "<< (tend - tstart) / 1000 << "."<< (tend - tstart) % 1000 << "s\n";
    }
}

void insertionSort(vector<int> &v, int nr, int Max) {
    if(nr > CONST_LIMIT) {
        cout << "InsertionSort -- NO -- " << nr << " " << Max << " ???\n";
    } else {
        struct timeval tv;
        int tstart, tend;
        gettimeofday( &tv, NULL );
        tstart = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        int x, j;
        for(unsigned i = 1; i < v.size(); ++i) {
            x = v[i];
            j = i - 1;
            while(j >= 0 && v[j] > x) {
                v[j + 1] = v[j];
                j--;
            }
            v[j + 1] = x;
        }
        gettimeofday(&tv, NULL);
        tend = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        cout << "InsertionSort " << umap[isSorted(v)] << " " << nr << " " << Max << " "<< (tend - tstart) / 1000 << "."<< (tend - tstart) % 1000 << "s\n";
    }
}

void quickSort(vector<int> &v, int Begin, int End) {
    int b, e, pivot;
    b = Begin;
    e = End;
    pivot = v[b + rand() % (e - b)];
    while(b <= e) {
        while(v[b] < pivot)
            b++;
        while(v[e] > pivot)
            e--;
        if(b <= e) {
            swap(v[b], v[e]);
            b++;
            e--;
        }
    }
    if(Begin < e)
        quickSort(v, Begin, e);
    if(b < End)
        quickSort(v, b, End);
}

void quickSortUtil(vector<int> &v, int nr, int Max) {
    struct timeval tv;
    int tstart, tend;
    gettimeofday( &tv, NULL );
    tstart = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    quickSort(v, 0, v.size() - 1);
    gettimeofday(&tv, NULL);
    tend = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    cout << "QuickSort " << umap[isSorted(v)] << " " << nr << " " << Max << " "<< (tend - tstart) / 1000 << "."<< (tend - tstart) % 1000 << "s\n";

}

void mergeSort(vector<int> &v, int b, int e) {
    if(b < e) {
        int mid = (b + e) >> 1;
        mergeSort(v, b, mid);
        mergeSort(v, mid + 1, e);
        int i, j;
        vector<int>aux;
        i = b;
        j = mid + 1;
        while(i <= mid && j <= e) {
            if(v[i] < v[j]) {
                aux.push_back(v[i]);
                i++;
            } else {
                aux.push_back(v[j]);
                j++;
            }
        }
        while(i <= mid) {
            aux.push_back(v[i]);
            i++;
        }
        while(j <= e) {
            aux.push_back(v[j]);
            j++;
        }
        for(i = b; i <= e; i++)
            v[i] = aux[i - b];
    }
}

void mergeSortUtil(vector<int>&v, int nr, int Max) {
    struct timeval tv;
    int tstart, tend;
    gettimeofday( &tv, NULL );
    tstart = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    mergeSort(v, 0, v.size() - 1);
    gettimeofday(&tv, NULL);
    tend = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    cout << "MergeSort " << umap[isSorted(v)] << " " << nr << " " << Max << " "<< (tend - tstart) / 1000 << "."<< (tend - tstart) % 1000 << "s\n";

}

void sortStd(vector<int>&v, int nr, int Max) {
    struct timeval tv;
    int tstart, tend;
    gettimeofday( &tv, NULL );
    tstart = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    sort(v.begin(), v.end());
    gettimeofday(&tv, NULL);
    tend = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    cout << "std::sort() " << umap[isSorted(v)] << " " << nr << " " << Max << " "<< (tend - tstart) / 1000 << "."<< (tend - tstart) % 1000 << "s\n";
}

void heapDown(vector<int>&v, int heapSize, int i) {
    int l, r, p;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if(l <= heapSize && v[l] < v[i])
        p = l;
    else p = i;
    if(r <= heapSize && v[r] < v[p])
        p = r;
    if(p != i) {
        swap(v[p], v[i]);
        heapDown(v, heapSize, p);
    }
}

void buildHeap(vector<int> &v) {
    int n = v.size();
    for(int i = n / 2; i >= 0; i--)
        heapDown(v, n - 1, i);
}

void heapSort(vector<int> &v, int nr, int Max) {
    struct timeval tv;
    int tstart, tend;
    gettimeofday( &tv, NULL );
    tstart = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    vector<int>g;
    int n, minValue, heapSize;
    n = heapSize = v.size();
    buildHeap(v);
    for(int i = 1; i <= n; i++) {
        minValue = v[0];
        //cout << minValue << " ";
        g.push_back(minValue);
        swap(v[0], v[heapSize - 1]);
        heapSize--;
        heapDown(v, heapSize - 1, 0);
    }
    v = g;
    gettimeofday(&tv, NULL);
    tend = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    cout << "HeapSort " << umap[isSorted(v)] << " " << nr << " " << Max << " "<< (tend - tstart) / 1000 << "."<< (tend - tstart) % 1000 << "s\n";
}

void countSort(vector<int> &v, int nr, int Max) {
    if(Max > MAX_SIZE)
        cout << "CountSort -- NO -- " << nr << " " << Max << " ???\n";
    else {
        struct timeval tv;
        int tstart, tend;
        gettimeofday( &tv, NULL );
        tstart = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        vector<int>::iterator it;
        int i, j, maxim, m;
        int nrap[Max + 1];
        for(i = 0; i <= Max; i++)
            nrap[i] = 0;
        maxim = v[0];
        for(it = v.begin(); it != v.end(); ++it) {
            nrap[*it]++;
            if((*it) > maxim)
                maxim = (*it);
        }
        m = 0;
        for(i = 0; i <= maxim; i++)
            for(j = 0; j < nrap[i]; j++)
                v[m++] = i;
        gettimeofday(&tv, NULL);
        tend = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        cout << "CountSort " << umap[isSorted(v)] << " " << nr << " " << Max << " "<< (tend - tstart) / 1000 << "."<< (tend - tstart) % 1000 << "s\n";
    }
}

void radixSort(vector<int> &v, int nr, int Max) {
    struct timeval tv;
    int tstart, tend;
    gettimeofday( &tv, NULL );
    tstart = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    vector<int>::iterator it;
    int Size;
    int maxValue = v[0];
    for(it = v.begin(); it != v.end(); ++it) {
        if((*it) > maxValue)
            maxValue = (*it);
    }
    for(int exp = 1; maxValue / exp > 0; exp *= 10) {
        vector<int>g[NR_BUCKETS];
        for(it = v.begin(); it != v.end(); ++it)
            g[((*it) / exp) % BASE].push_back(*it);
        Size = 0;
        for(int i = 0; i < BASE; i++) {
            for(it = g[i].begin(); it != g[i].end(); ++it)
                v[Size++] = *it;
        }
    }
    gettimeofday(&tv, NULL);
    tend = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    cout << "RadixSort " << umap[isSorted(v)] << " " << nr << " " << Max << " "<< (tend - tstart) / 1000 << "."<< (tend - tstart) % 1000 << "s\n";

}

void radixSort2(vector<int>&x, vector<int>&y, int bits) {
    vector<int>g[1 << BITS];
    for(unsigned i = 0; i < x.size(); ++i) {
        int nrList = (x[i] >> bits) & MASK;
        g[nrList].push_back(x[i]);
    }
    int len = 0;
    for(unsigned i = 0; i <= MASK; i++) {
        for(unsigned j = 0; j < g[i].size(); ++j)
            y[len++] = g[i][j];
    }
}

void radixSort2Util(vector<int>&v, int nr, int Max) {
    vector<int>aux(v.size());
    struct timeval tv;
    int tstart, tend;
    gettimeofday( &tv, NULL );
    tstart = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    radixSort2(v, aux, 0);
    radixSort2(aux, v, BITS);
    gettimeofday(&tv, NULL);
    tend = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    cout << "RadixSort2 " << umap[isSorted(v)] << " " << nr << " " << Max << " "<< (tend - tstart) / 1000 << "."<< (tend - tstart) % 1000 << "s\n";
}

void afisVector(vector<int> p) {
    vector<int>::iterator it;
    for(it = p.begin(); it != p.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";
}

int main() {
    umap[0] = "NO";
    umap[1] = "YES";
    vector<int> b;
    int T, n, x, i, j, max_Value;
    srand(time(NULL));
    ifstream fin("sortare.in");
    fin >> T; // citesc numarul testelor
    for(i = 1; i <= T; ++i) {
        fin >> n >> max_Value; // citesc dimensiunea primului vector si valoarea sa maxima
        vector<int>a;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distribution(1, max_Value);
        for(j = 0; j < n; j++) {
            x = distribution(gen);
            //fout << x << " ";
            a.push_back(x);
        }
        cout << "Testul nr " << i << "\n";
        b = a;
        bubbleSort(b, n, max_Value);
        b = a;
        insertionSort(b, n, max_Value);
        b = a;
        quickSortUtil(b, n, max_Value);
        b = a;
        mergeSortUtil(b, n, max_Value);
        b = a;
        sortStd(b, n, max_Value);
        b = a;
        heapSort(b, n, max_Value);
        b = a;
        countSort(b, n, max_Value);
        b = a;
        radixSort(b, n, max_Value);
        b = a;
        radixSort2Util(b, n, max_Value);
        cout << "\n";
    }
    fin.close();
    return 0;
}
