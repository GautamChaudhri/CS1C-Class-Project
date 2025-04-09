/*******************************************************************************
 * vector.h
 * -----------------------------------------------------------------------------
 * Worked on by: Aram, Aspen, Luke
 * -----------------------------------------------------------------------------
 * This vector will be used to hold the shapes that will be displayed.
 * It supports the following basic operations:
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
        /***********************************************************************
         * DEFAULT CONSTRUCTOR
         **********************************************************************/
        vector() : size_v(0), space(1) {
            elem = new T[space];
        } // END vector()
        
        /***********************************************************************
         * ALTERNATE CONSTRUCTOR - size given
         **********************************************************************/
        explicit vector(int s) : size_v(s), space(s) {
            elem = new T[space];
        } // END explicit vector(int s) 

        /***********************************************************************
         * COPY CONSTRUCTOR
         **********************************************************************/
        vector(const vector& other) : size_v(other.size), space(other.space) {
            elem = new T[space];

            for (int i = 0; i < size_v; i++) {
                elem[i] = other.elem[i];
            } // END for (int i = 0; i < size_v; i++)
        } // END vector(const vector& other)

        /***********************************************************************
         * COPY ASSIGNEMNT
         **********************************************************************/
        vector& operator=(const vector& other) {
            /*******************************************************************
            * CHECKS IF SELF-ASSIGNMENT
            *******************************************************************/
            if (this == &other) { 
                return *this; 
            }

            /*******************************************************************
            * IF NOT SELF-ASSIGNMENT
            *******************************************************************/
            delete[] elem;
            
            size_v = other.size_v;
            space = other.space;
            elem = new T[space];

            for (int i = 0; i < size_v; i++) {
                elem[i] = other.elem[i];
            }

            return *this;
        } // END vector& operator=vector

        /***********************************************************************
         * MOVE CONSTRUCTOR
         **********************************************************************/
        vector(vector&& other) noexcept 
            : size_v(other.size_v), elem(other.elem), space(other.space) {
            other.size_v = 0;
            other.elem = nullptr;
            other.space = 0;
        }

        /***********************************************************************
         * MOVE ASSIGNMENT
         **********************************************************************/
        vector& operator=(vector&& other) noexcept {
            /*******************************************************************
            * CHECKS IF SELF-ASSIGNMENT
            *******************************************************************/
            if (this == &other) { 
                return *this; 
            }

            /*******************************************************************
            * IF NOT SELF-ASSIGNMENT
            *******************************************************************/
            delete[] elem;
            
            size_v = other.size_v;
            space = other.space;
            elem = other.elem;

            other.size_v = 0;
            other.space = 0;
            other.elem = nullptr;

           return *this;
        } // END vector& operator=(const vector&& other) noexcept

        /***********************************************************************
         * DESTURCTOR
         **********************************************************************/
        ~vector() { delete[] elem; }
        
        /***********************************************************************
         * ACCESSOR - RETURN REFERNCE - MODIFIABLE
         **********************************************************************/
        T& operator[] (int n) { return elem[n]; }

        /***********************************************************************
         * ACCESSOR - RETURN REFERNCE
         **********************************************************************/
        const T& operator[] (int n) const { return elem[n]; }
        
        /***********************************************************************
         * ACCESSOR - RETURN CURRENT SIZE
         **********************************************************************/
        int size() const { return size_v; }

        /***********************************************************************
         * ACCESSOR - RETURN CURRENT AVAILABLE SPACE
         **********************************************************************/
        int capacity() const { return space; }

        /***********************************************************************
         * void resize(int newsize) - not done
         * ----------------------------------------------------------------------
         * This function will be passed a number:
         *      newsize     - size to increase vector by
         * 
         * depending on size_v the following will happen:
         *      size_v = newsize
         *      nothing will happen
         * 
         *      size_v < newsize
         *      will change size_v to newsize
         * 
         *      size_v > newsize (default)
         *      error will occur
         * ---------------------------------------------------------------------
         * PRE-CONDITIONS
         *      size_v  - original size of vector
         * 
         * POST-CONDITIONS
         *      newsize  - new size of vector
         **********************************************************************/
        void resize(int newsize) {

            /*******************************************************************
            * EQUALS EACH OTHER
            *******************************************************************/
            if (size_v == newsize) {}

            /*******************************************************************
            * OG SIZE LESS THAN NEW SIZE
            *******************************************************************/
            else if (size_v < newsize) {
                reserve(newsize);
                size_v = newsize;
            } // END else if (size_v < newsize)

            /*******************************************************************
            * DEFAULT - SMALLER THAN OG / INVALID INPUT / ERROR
            *******************************************************************/
            else {
                // WILL DO ERROR LATER
            }

        } // END void resize(int newsize)

        /***********************************************************************
         * FUNCTION - ADD ELEMENT
         **********************************************************************/
        // void push_back(T val);

         /***********************************************************************
         * void reserve(int newalloc) - not done
         * ----------------------------------------------------------------------
         * This function will be passed a number:
         *      newalloc     - size to increase vector capacity by
         * 
         * depending on space the following will happen:
         *      space = newalloc
         *      nothing will happen
         * 
         *      space < newalloc
         *      will change space to newalloc
         * 
         *      size_v > newalloc (default)
         *      error will occur
         * ---------------------------------------------------------------------
         * PRE-CONDITIONS
         *      space  - original size of vector
         * 
         * POST-CONDITIONS
         *      newalloc  - new size of vector
         **********************************************************************/
        void reserve(int newalloc) {
            /*******************************************************************
            * EQUALS EACH OTHER
            *******************************************************************/
            if (space == newalloc) {}

            /*******************************************************************
            * OG SIZE LESS THAN NEW SIZE
            *******************************************************************/
            else if (space < newalloc) {

                // CREATE BIGGER ARRAY
                T* new_elem = new T[newalloc];

                // COPY DATA
                for (int i = 0; i < size_v; i++) {
                    new_elem[i] = elem[i];
                }

                delete[] elem;
                elem = new_elem;
                
                // UPDATE SPACE
                space = newalloc;
            } // END else if (space < newalloc)

            /*******************************************************************
            * DEFAULT - SMALLER THAN OG / INVALID INPUT / ERROR
            *******************************************************************/
            else {
                // ADDING ERROR STUFF LATER
            }

        } // END void reserve(int newalloc)

        
        // using iterator = T*;
        // using const_iterator = const T*;

        // iterator begin(); // points to first element
        // const_iterator begin() const;
        // iterator end(); // points to one beyond the last element
        // const_iterator end() const;
        // iterator insert(iterator p, const T& v); // insert a new element v before p
        // iterator erase(iterator p); // remove element pointed to by p
};