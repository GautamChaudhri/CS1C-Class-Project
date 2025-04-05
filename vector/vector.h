/*******************************************************************************
 * vector.h
 * -----------------------------------------------------------------------------
 * Worked on by: Aram, Aspen, Luke
 * -----------------------------------------------------------------------------
 * This vector supports the following basic operations:
 *      - constructors for one or more arguments
 *      - default constructors
 *      - copy constructor
 *      - copy assignment
 *      - move constructor
 *      - move assignment
 *      - destructor
 * 
 * Vector also supports:
 *      - a basic iterator member type and member function
 *      - begin()
 *      - end() operations
*******************************************************************************/
template<class T>

class vector
{
    int size_v;     // the size
    T* elem;        // a pointer to the elements
    int space;      // size + free_space
    
    public:
        // DEFAULT CONSTRUCTOR
        vector() : size_v(0), space(1) {
            elem = new T[space];
        }

        // ALTERNATE CONSTRUCTOR - size given
        explicit vector(int s) : size_v(s), space(s) {
            elem = new T[space];
        }

        // // COPY CONSTRUCTOR
        vector(const vector& other) : size_v(other.size), space(other.space) {
            elem = new T[space];

            for (int i = 0; i < size_v; i++) {
                elem[i] = other.elem[i];
            } // END for (int i = 0; i < size_v; i++)
        }

        // // COPY ASSIGNEMNT
        // vector& operator=vector(const vector&);

        // // MOVE CONSTRUCTOR
        // vector(const vector&&) noexcept;

        // // MOVE ASSIGNMENT
        // vector& operator=vector(const vector&&) noexcept;

        // DESTURCTOR
        ~vector() { delete[] elem; }
        
        // ACCESSOR - RETURN REFERNCE - MODIFIABLE
        T& operator[] (int n) { return elem[n]; }

        // ACCESSOR - RETURN REFERNCE
        const T& operator[] (int n) const { return elem[n]; }

        // ACCESSOR - RETURN CURRENT SIZE
        int size() const { return size_v; }

        // ACCESSOR - RETURN CURRENT AVAILABLE SPACE
        int capacity() const { return space; }

        // FUNCTION - GROW
        // void resize(int newsize);

        // FUNCTION - ADD ELEMENT
        // void push_back(T val);

        // FUNCTION - GET MORE SPACE
        // void reserve(int newalloc);

        
        // using iterator = T*;
        // using const_iterator = const T*;

        // iterator begin(); // points to first element
        // const_iterator begin() const;
        // iterator end(); // points to one beyond the last element
        // const_iterator end() const;
        // iterator insert(iterator p, const T& v); // insert a new element v before p
        // iterator erase(iterator p); // remove element pointed to by p
};