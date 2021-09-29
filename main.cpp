#include <cstring>
#include <ctime>
#include "string"
#include "iostream"
using namespace std;

struct Set   //список
{
    char element;
    Set* next;

    Set(char c, Set* n = nullptr){
        element = c;
        next = n;
    };
    ~Set() { delete next; }
};

void print_set(Set* A)
{
    Set* ptr = A;
    while (ptr) { cout << ptr->element << " "; ptr = ptr->next; }
}


char *solve_array(char a[], char b[], char c[], char d[])       //решение множеств через массивы
{
    int moves = 0;
    char *res = (char*)calloc(11, sizeof(char));
    char *a_plus_d  = (char*)calloc(11, sizeof(char));
    char *b_multiply_c = (char*)calloc(11, sizeof(char));
    for(int i = 0; i < 11; i++){res[i] = '\0'; a_plus_d[i] = '\0';}
    for(int i = 0; a[i]; i++)
    {
        a_plus_d[i] = a[i];
        moves++;
    }
    for(int i = 0; d[i]; i++)
    {
        bool flag = false;
        for(int j = 0; a[j] && !flag; j++, moves++){
            if(d[i] == a[j])
                flag = true;
        }
        if(flag)
            continue;
        a_plus_d[strlen(a_plus_d)] = d[i];
    }
    for(int i = 0; b[i]; i++)
    {
        bool flag = false;
        for(int j = 0; c[j] && !flag; j++, moves++){if(b[i] == c[j]) flag = true;}
        if(flag)  b_multiply_c[strlen(b_multiply_c)] = b[i];
    }
    int pos = 0;
    for(int i = 0; a_plus_d[i]; i++)
    {
        bool flag = false;
        for(int i = 0; b_multiply_c[i]; i++)
        {
            bool flag = false;
            for(int j = 0; a_plus_d[j] && !flag; j++, moves++){if(a_plus_d[j] == b_multiply_c[i]) flag = true;}
            if(flag) continue;
            a_plus_d[strlen(a_plus_d)] = b_multiply_c[i];
        }
        res[pos++] = a_plus_d[i];
    }
    free(a_plus_d);
    free(b_multiply_c);
    return res;
}

Set* make_set_from_array(char* arr)
{
    Set* prev = nullptr;
    for (int i = strlen(arr) - 1; i >= 0; i--)
    {
        prev = new Set(arr[i], prev);
    }
    return prev;
}

void insert_to_set(Set* s, char e)
{
    Set* last = s;
    while (last && last->next) last = last->next;
    if (!last) return;
    Set* new_el = new Set(e, nullptr);
    last->next = new_el;
}


bool has_list_element(Set *list, char item){
    bool result = false;
    for(Set* iterator = list; iterator; iterator = iterator->next){
        if(iterator->element == item){
            result = true;
            break;
        }
    }
    return result;
}


Set* solve_set(Set *a, Set *b, Set *c, Set *d)
{
    Set *res = nullptr, *a_plus_b = nullptr;
    for(Set *step = a; step; step = step->next){
        if(res)
            insert_to_set(res, step->element);
        else
            res = new Set(step->element);
    }

    for(Set *step = d; step; step = step->next){
        if(res){
            if(!has_list_element(res, step->element)){
                insert_to_set(res, step->element);
            }
        } else {
            res = new Set(step->element);
        }
    }

    for(Set *step = b; step; step = step->next){
            if(has_list_element(c, step->element)){
                if(!has_list_element(res, step->element)){
                    if(res) {
                        insert_to_set(res, step->element);
                    } else {
                        res = new Set(step->element);
                    }

                }
            }
    }
    return res;
}


int* array_to_bits(char* arr)
{
    int a;
    int* bits = (int*)calloc(10, sizeof(int));
    if (bits)
    {
        for (int i = 0; arr[i]; i++)
        {
            a = arr[i] - '0';
            bits[a] = 1;
        }
    }
    return bits;
}

char* bits_to_array(int* bits)
{
    const int M = 10;
    char* arr = (char*)malloc((M + 1) * sizeof(char));
    if (arr)
    {
        for (int i = 0; i < M + 1; i++) arr[i] = '\0';
        for (int i = 0, k = 0; i < M; i++) if (bits[i]) arr[k++] = i + '0';
    }
    return arr;
}

int array_to_short(char* arr)
{
    short s = 0, a;
    for (int i = 0; arr[i]; i++)
    {
        a = arr[i] - '0';
        s |= (1 << a);
    }
    return s;
}

char* short_to_array(short s)
{
    const int M = 10;
    char* arr = (char*)malloc((M + 1) * sizeof(char));
    if (arr)
    {
        for (int i = 0; i < M + 1; i++) arr[i] = '\0';
        for (int i = 0, k = 0; i < M; i++) if ((s >> i) & 0x1) arr[k++] = i + '0';
    }
    return arr;
}

void print_binary_code(short s)
{
    for (int i = 9; i >= 0; i--) cout << ((s >> i) & (0x1)) << ' ';
    cout << endl;
}

int* solve_bits(int* a, int* b, int* c, int* d)
{
    int* e = (int*)calloc(10, sizeof(int));
    if (e) for (int i = 0; i < 10; i++) e[i] = a[i] || (b[i] && c[i]) || d[i];
    return e;
}

short solve_short(short a, short b, short c, short d)
{
    short e = a | (b & c) | d;
    return e;
}

char* get_random_string_set()
{
    char* s = (char*)calloc(11, sizeof(char));
    int k = 0;
    const string alph = "0123456789";
    for(int i = 0; i < 10; i++) if(rand()%2) s[k++] = alph[i];
    s[k] = 0;
    return s;
}

char* get_random_string_set(int p, int q)
{
    char* s = (char*)calloc(11, sizeof(char));
    int k = 0;
    const string alph = "0123456789";
    for(int i = 0; i < 10; i++) if(rand()% p >= q) s[k++] = alph[i];
    s[k] = 0;
    return s;
}

char* shuffle_string(char *s)
{
    int m = strlen(s);
    for(int i = 0; i < m; i++)
    {
        int r = rand() % m;
        char cur = s[i];
        s[i] = s[r];
        s[r] = cur;
    }
    return s;
}

char *remove_copies(char *str)
{
    char *res = (char*)calloc(11, sizeof(char));
    for(int i = 0, pos = 0; str[i]; i++)
    {
        bool added = false;
        for(int j = 0; j < pos && !added; j++)
        {
            if(res[j] == str[i]) added = true;
        }
        if(added) continue;
        res[pos++] = str[i];
    }
    return res;
}

int main()
{
    srand(time(0));
    // (A | B) \C \D
    const int M = 2048;
    //char a[M + 1], b[M + 1], c[M + 1], d[M + 1], *e;
    char *a = (char*)calloc(M+1, sizeof(char)),
            *b = (char*)calloc(M+1, sizeof(char)),
            *c = (char*)calloc(M+1, sizeof(char)),
            *d = (char*)calloc(M+1, sizeof(char)),
            *e;
    int* bitsa, *bitsb, *bitsc, *bitsd, *solvebits;
    short shorta, shortb, shortc, shortd, solveshort;
    clock_t time;
    cout << "Input set A. Do not separate items with anything." << '\n';
    cin >> a;
    cout << "Input set B. Do not separate items with anything." << '\n';
    cin >> b;
    cout << "Input set C. Do not separate items with anything." << '\n';
    cin >> c;
    cout << "Input set D. Do not separate items with anything." << '\n';
    cin >> d;
    a = remove_copies(a);
    b = remove_copies(b);
    c = remove_copies(c);
    d = remove_copies(d);
    //0123456789ABCDEF, FEDCBA9876543210
    /*cout << "a = " << (a = shuffle_string(get_random_string_set(10, 0))) << "\n";
    cout << "b = " << (b = shuffle_string(get_random_string_set(10, 0))) << "\n";
    cout << "c = " << (c = shuffle_string(get_random_string_set(10, 0))) << "\n";
    cout << "d = " << (d = shuffle_string(get_random_string_set(10, 0))) << "\n";*/
    // array
    //char a[] = "1238", b[] = "456", c[]="12", d[]="24";
    cout << "\n======================================== Array ========================================\n\n";
    time = clock();
    char* resArr = solve_array(a, b, c, d);
    cout << "Work time: " << clock() - time << "ms\n";
    for (int i = 0; i < (int)strlen(resArr); i++) cout << resArr[i] << " ";

    //list
    cout << "\n\n======================================== List ========================================\n\n";
    Set* aset = make_set_from_array(a);
    Set* bset = make_set_from_array(b);
    Set* cset = make_set_from_array(c);
    Set* dset = make_set_from_array(d);
    time = clock();
    Set* resSet = solve_set(aset, bset, cset, dset);
    cout << "Work time: " << clock() - time << "ms\n";
    print_set(resSet);

    //bits array
    cout << "\n\n======================================== Bits ========================================\n\n";
    bitsa = array_to_bits(a);
    bitsb = array_to_bits(b);
    bitsc = array_to_bits(c);
    bitsd = array_to_bits(d);

    time = clock();
    solvebits = solve_bits(bitsa, bitsb, bitsc, bitsd);
    cout << "Work time: " << clock() - time << "ms\n";
    for (int i = 0; i < 10; i++) cout << solvebits[i] << ' ';
    cout << '\n';
    e = bits_to_array(solvebits);
    for (int i = 0; e[i]; i++) cout << e[i] << ' ';

    //machine word
    cout << "\n\n======================================== Short ========================================\n\n";
    shorta = array_to_short(a);
    shortb = array_to_short(b);
    shortc = array_to_short(c);
    shortd = array_to_short(d);
    time = clock();
    solveshort = solve_short(shorta, shortb, shortc, shortd);
    cout << "Work time: " << clock() - time << "ms\n";
    print_binary_code(solveshort);
    e = short_to_array(solveshort);
    for (int i = 0; e[i]; i++) cout << e[i] << ' ';

    return 0;
}

