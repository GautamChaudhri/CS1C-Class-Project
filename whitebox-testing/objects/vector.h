#ifndef ALPHA_VECTOR_H
#define ALPHA_VECTOR_H  //This is necessary for inclusion guards. DO NOT DELETE
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
namespace alpha {
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
        vector(const vector& other) : size_v(other.size_v), space(other.space) {
            elem = new T[space];

            for (int i = 0; i < size_v; i++) {
                elem[i] = other.elem[i];
            } // END for (int i = 0; i < size_v; i++)
        } // END vector(const vector& other)

        /***********************************************************************
         * COPY ASSIGNMENT
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
         * DESTRUCTOR
         **********************************************************************/
        ~vector() { delete[] elem; }
        
        /***********************************************************************
         * ACCESSOR - RETURN REFERENCE - MODIFIABLE
         **********************************************************************/
        T& operator[] (int n) { return elem[n]; }

        /***********************************************************************
         * ACCESSOR - RETURN REFERENCE
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
         * void resize(int newsize)
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
            * DOES NOTHING - EQUALS EACH OTHER
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
            * DOES NOTHING - DEFAULT - SMALLER THAN OG / INVALID INPUT / ERROR
            *******************************************************************/
            else { }

        } // END void resize(int newsize)

        /***********************************************************************
         * FUNCTION - ADD ELEMENT
         * ----------------------------------------------------------------------
         * This function will be passed a value:
         *      val     - data to add to vector
         * 
         * Function adds the data to the back of the vector. If there is no
         * space then the function will increase the space before adding
         * ---------------------------------------------------------------------
         * PRE-CONDITIONS
         *      size_v  - original size of vector
         * 
         * POST-CONDITIONS
         *      newsize  - new size of vector
         **********************************************************************/
        void push_back(const T val) {
            /*******************************************************************
             * IF NO SPACE - MAKE ROOM
             ******************************************************************/
            if (size_v == space) {
                reserve(space + 1);
            }
            /*******************************************************************
             * IF SPACE
             ******************************************************************/
            elem[size_v] = val;
            size_v++;
        } // END void push_back(const T val)

         /**********************************************************************
         * void reserve(int newalloc)
         * ---------------------------------------------------------------------
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
            * DOES NOTHING - EQUALS EACH OTHER
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
            * DOES NOTHING - DEFAULT - SMALLER THAN OG / INVALID INPUT / ERROR
            *******************************************************************/
            else { }

        } // END void reserve(int newalloc)

        
        using iterator = T*;
        using const_iterator = const T*;

        /***********************************************************************
         * POINTS TO FIRST ELEMENT
         **********************************************************************/
        iterator begin() { return elem; }

        /***********************************************************************
         * CONSTANT - POINTS TO FIRST ELEMENT
         **********************************************************************/
        const_iterator begin() const { return elem; }

        /***********************************************************************
         * POINTS TO ONE BEYOND THE LAST ELEMENT
         **********************************************************************/
        iterator end() { return elem + size_v; }

        /***********************************************************************
         * CONSTANT - POINTS TO ONE BEYOND THE LAST ELEMENT
         **********************************************************************/
        const_iterator end() const { return elem + size_v; }

        /***********************************************************************
         * INSERT NEW ELEMENT (V) BEFORE P
         **********************************************************************/
        iterator insert(iterator p, const T& v) {
            /*******************************************************************
             * CHECK IF ENOUGH SPACE
             ******************************************************************/
            // record the index where we want to insert
            int index = static_cast<int>(p - elem);

            // grow storage if needed
            if (size_v == space) {
                reserve(space + 1);
            }

            // iterator next = end();
            // while (next != p) {
            //     *next = *(next - 1);
            //     next--;
            // }

            // recompute pointers into the (possibly moved) data
            p = elem + index;
            iterator end_it = elem + size_v;

            // shift elements [index..size_v-1] one position to the right
            for (iterator it = end_it; it != p; --it)
                *it = *(it - 1);

            *p = v;
            size_v++;

            return p;
        } // END iterator insert(iterator p, const T& v)

        /***********************************************************************
         * REMOVE ELEMENT POINTED TO BY P
         **********************************************************************/
        iterator erase(iterator p) {
            /*******************************************************************
             * IF P AT THE END
             ******************************************************************/
            if (p == end()) {
                return p;
            }

            iterator next = p + 1;
            while (next != end()) {
                *p = *next;
                p++;
                next++;
            }

            p--;
            p->~T();
            size_v--;

            return p;
        } // END iterator erase(iterator p)
        
}; // END class vector
}; // END namespace alpha
#endif // ALPHA_VECTOR_H
