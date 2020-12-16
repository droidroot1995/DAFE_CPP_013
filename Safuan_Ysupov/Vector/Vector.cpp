//Vectors and dynamically allocated memory
#include <iostream>
using namespace std;


class vector
{
    int sz;          // The size
    double* elem;    // Pointer to the first element (of type double)
public:
    vector(int s) :           // Constructor
        sz{ s },              // sz member initialization
        elem{ new double[s] }   // Elem member initialization
    {
        for (int i = 0; i < s; i++)  // initialization
            elem[i] = 0;            // of elements
    }

    vector(initializer_list<double> lst)
    {
        sz =lst.size();
        elem=new double[sz];
    
        copy(lst.begin(), lst.end(), elem);
    }
    ~vector()           // Destructor, free memory
    {
        delete[] elem;
    }
    // Constructor: allocates s numbers in memory
    // of type double, points to them pointer
    // elem and stores s into sz

    int size() const { return sz; } //ТCurrent size
    double get(int n) const { return elem[n]; } //Reading
    void set(int n, double v) { elem[n] = v; } //Writing
};
// Destructor. 
/* Just like a constructor is implicitly called when a class object is created,
the destructor is implicitly called when the object goes out of scope.
The constructor ensures that the object will be correct
createdand initialized.The destructor, on the other hand, ensures that
the object will be properly cleaned up before being destroyed.*/

void f(void* pv)
{
    void* pv2 = pv; // Correct (type void * for this
                     // and is intended)
         // double * pd = pv; // Error: Unable to cast
                     // void * to douЫe *
         // * pv = 7; // Error: Unable to dereference void *
                     // (the type of object pointed to by pv,
                     // unknown)
         // pv [2] = 9; // Error: void * cannot be indexed
    int* pi = static_cast <int*> (pv); // OK: explicit conversion
    /*The static_cast operator allows you to explicitly convert the pointers of bound
    types one into another, for example, such as void* or douЫe* */
}

/*
*The C ++ language provides two operators for casting types, which
potentially worse than the static_cast operator.
• The reinterpret_cast operator can convert a type to perfectly
another, unrelated to it, such as int in douЫe* .
• The const cast operator lets you drop the const qualifier.
*/

int main()
{
    vector v(5);
    for (int i = 0; i < v.size(); ++i)
    {
        v.set(i, 1.1 * 1);
        cout << "v[" << i << "]==" << v.get(i) << endl;
    }
    int x = v.size();
    double d = v.get(3);
    cout << x << ' ' << d;

    /*Like operator. (dot) . operator -> (arrow) can be used
    to access data members and member functions.Since the built - in
    types such as intand doubye have no members, the -> operator does not apply to them.The dotand arrow operators are often referred to as operators
    member access operators.*/

    // operator -> (arrow) to access
    // to its members using a pointer to an object
    vector* p = new vector(4);
    x = p->size();
    d = p->get(3);

    void* pvl = new int; // Oh! \: Int * becomes void *
    void* pv2 = new double[10]; // OK: douЬle * turns to void *

    /*• Assigning something to a pointer changes the value of the pointer,
        not the object it points to.
        • To get a pointer, you usually need to
        use the new or &operator.
        • To access the object pointed to by the pointer, use the*and [] operators.
        • Assigning a new value to the reference changes the value of the object to
        which she links, not the link itself.
        • After initialization, the link cannot be redirected to another
        an object.
        • Link assignment performs deep copying
        (the new value is assigned to the object that the reference points to);
    pointer assignments do not use deep copying(new
        the value is assigned to the pointer, not the object).
        • Null pointers are dangerous.*/
    int х = 10;
    int* р = &х; // To get a pointer, you need the & operator
    *р = 7;  // To assign a value to variable x
             // via p pointer used *
    int х2 = *р;  // Read x value using p pointer
    int* р2 = &х2;  // Get a pointer to another variable
                    // int type
    р2 = р;      // Pointers p2 and p point to variable x
    р = &х2;     // Pointer p points to another object
    
    // Relevant example for links 
    int y = 10;
    int& r = y;   // The & symbol stands for a type, not an initializer
    r = 7;        // Assign the value to the variable y
                  // using the link r (the * operator is not needed)
    int y2 = r;   // Read the variable y using the link r
                  // (operator * is not needed)
    int& r2 = y2; // Reference to another variable of type int
    r2 = r;       // the value of the variable y is assigned
                  // variable y2
    // r = & y2;  // Error: cannot change the value of the link
                  // (you cannot assign int * to the reference int &)
   
}
/*
When creating an object of class vector in dynamic memory, the operator
new does the following :
• first allocates memory for an object of class vector;
• then calls the vector class constructor to initialize the object;
this constructor allocates memory for the elements of the vector object
and initializes them.
By deleting an object of class vector, the delete operator does the following :
• first calls the vector class destructor; this destructor, in its
queue, calls the destructors of the elements(if any), and
then frees the memory occupied by the elements of the vector;
• then frees the memory occupied by the vector.
*/

/*void type * means "a pointer to a memory cell whose type
unknown to the compiler. "It is used when needed
transfer an address from one part of the program to another.
and each of them knows nothing about the type of object with which the other works
part. */