#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 4000;

struct Elem {
    char full_name[30];
    unsigned short int number;
    char date[10];
    char full_lawyer_name[22];
};
struct List{
    Elem elem;
    List* next;
    union {
        Elem* data;
        unsigned char Digit[sizeof(data)];
    };
};
struct body {
    List* head;
    List* tail;
};
struct queue
{
    List* top, * tail;
};
List* printList(List* p, short int& count, bool direction){
    for (int i = 0; i < 20; i++, count++)
    {
        cout << count << ") " << p->data->full_name << "\t" << p->data->number << "\t" << p->data->date << "\t" << p->data->full_lawyer_name << endl;
        p = p->next;
    }
    return p;
}

void digitalSort(List*& head) {
    int first_f = 16;
    int sec_f = 12;
    struct Queue {
        List* tail;
        List* head;
    } q[256];
    int L = first_f + sec_f;
    List* p;

    for (int j = 0; j < L; j++) {
        for (auto& i : q) {
            i.tail = i.head = nullptr;
        }
        while (head) {
            int d;
            if (j < sec_f) {
                d = 255 - abs(head->elem.full_name[L - j - 1 - first_f]);
            }
            else if (j < sec_f + first_f) {
                //d = 255 - abs(head->elem.number);
                d = 255 - abs(head->elem.full_lawyer_name[L - j - 1]);
            }
            else {
                throw out_of_range("d out of range");
            }
            if (d > 255 or d < 0) {
                throw out_of_range("Out of queue range");
            }
            p = q[d].tail;
            if (q[d].head == nullptr)
                q[d].head = head;
            else
                p->next = head;

            p = q[d].tail = head;
            head = head->next;
            p->next = nullptr;
        }
        int i;
        for (i = 0; i < 256; i++) {
            if (q[i].head != nullptr)
                break;
        }
        head = q[i].head;
        p = q[i].tail;
        for (int k = i + 1; k < 256; k++) {
            if (q[k].head != nullptr) {
                p->next = q[k].head;
                p = q[k].tail;
            }
        }
    }
}
int strcomp(const string& str1, const string& str2, int len = -1) {
    if (len == -1) {
        len = (int)str1.length();
    }
    for (int i = 0; i < len; ++i) {
        if ((str1[i] == '\0') && (str2[i] == '\0')) {
            return 0;
        }
        else if (str1[i] == ' ' && str2[i] != ' ') {
            return -1;
        }
        else if (str1[i] != ' ' && str2[i] == ' ') {
            return 1;
        }
        else if (str1[i] < str2[i]) {
            return -1;
        }
        else if (str1[i] > str2[i]) {
            return 1;
        }
    }
    return 0;
}
int PrintSort(List* p, short int& count)
{
    int b = 0;
    for (int i = 0; i < N / 20 + 1; i++)
    {
        p = printList(p, count, 1);
        std::cout << "Next 20?  1/0: ";
        cin >> b;
        if (b == false)
        {
            break;
            return 1;
        }
    }
}
void make_index_array(Elem* arr[], List* root, int n = N) {
    List* p = root;
    for (int i = 0; i < n; i++) {
        arr[i] = &*(p->data);
        p = p->next;
    }
}
void Create_Queue(queue* q, Elem* R)
{
    List* q2;
    q2 = new List();
    if (q->top == NULL && q->tail == NULL)
    {
        q2->data = R;
        q2->next = NULL;
        q->tail = q2;
        q->top = q->tail;
    }
    else
    {
        List* q3;
        q3 = q->tail->next;
        q->tail->next = q2;
        q2->data = R;
        q2->next = q3;
        q->tail = q2;
    }
}
int B2Search(Elem* arr[], queue* top) {
    string key;
    std::cout << "Input key (3 char):";
    cin >> key;
    std::cout << endl;
    int L = 0;
    int R = N - 1;
    int i = 0;
    while (L < R)
    {
        int m = (L + R) / 2;
        if (strcomp(arr[m]->full_name, key, 3) < 0) L = m + 1;
        else R = m;

    }
    i = R;
    while (strcomp(arr[i]->full_name, key, 3) == 0) {

        Create_Queue(top, arr[i]);
        i++;
    }

    if (strcomp(arr[R]->full_name, key, 3) == 0) return R;
    else  std::cout << "Elements not founded";
}
void PrintQueue(queue* q, int count) {
    List* q2;
    int i = 0;
    count++;
    for (q2 = q->top; q2 != NULL; q2 = q2->next, count++)
    {
        //SetConsoleCP(1251);

        std::cout << count << ") " << q2->data->full_name << "\t" << q2->data->number << "\t" << q2->data->date << "\t" << q2->data->full_lawyer_name << endl;
    }


    printf("\n");
}
void init(queue* q)
{
    q->top = NULL;
    q->tail = NULL;
}
int menu() {
    int choiсe;
    cout << "1) Drop source database\n";
    cout << "2) Drop sorted database\n";
    cout << "3) Binary search in database\n";
    cout << "4) Make AVL-Tree\n";
    cout << "5) Binary search in tree\n";
    cout << "6) Encoding using the Gilbert-Moore method \n";
    cout << "0) Exit\n";
    cin >> choiсe;
    system("cls");
    return choiсe;
}
int main(){
    FILE* fin = fopen("testBase3.dat", "rb");
    List* head = new List;
    List* p = head;
    Elem* ind_arr[N];
    unsigned int size = 0;
    int choiсe = menu(), z = 0, L = 4;
    short int count = 1;
    bool b;
    for (int i = 0; i < N; i++)
    {
        p->data = new Elem;
        z = fread((Elem*)p->data, sizeof(Elem), 1, fin);
        if (i != N - 1)
        {
            p->next = new List;
            p = p->next;
        }
        else p->next = NULL;
    }
    p = head;
    
    switch (choiсe){
    case (1): {
        system("clear");
        for (int i = 0; i < N / 20 + 1; i++) {
            p = printList(head, count, 1);
            cout << "Next 20?  1/0: ";
            cin >> b;
            if (b == false) {
                break;
                choiсe = 1;
            }
        }
    }
    case (2): {
        system("clear");
        digitalSort(p);
        PrintSort(p, count);
        }

    case (3): {
        system("clear");
        make_index_array(ind_arr, head);
        queue* top = new queue;
        init(top);
        int num = B2Search(ind_arr, top);
        PrintQueue(top, num);
        }
    //default:
    //    break;
        }
   }
