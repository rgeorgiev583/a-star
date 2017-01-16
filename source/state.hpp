#ifndef __STATE__
#define __STATE__

#include <memory>


namespace SlidingBlocks
{
    class SquareIntMatrix
    {
        void copy(const SquareIntMatrix& other)
        {
            size = other.size;
            data = new int*[size];

            for (int i = 0; i < size; i++)
            {
                data[i] = new int[size];

                for (int j = 0; j < size; j++)
                    data[i][j] = other.data[i][j];
            }
        }

        void destroy()
        {
            for (int i = 0; i < size; i++)
                delete data[i];

            delete data;
            data = nullptr;
        }

    protected:
        int** data;
        int size;

    public:
        SquareIntMatrix(): data(nullptr), size(0)
        {
        }
        SquareIntMatrix(int _size): data(nullptr), size(_size)
        {
            data = new int*[size];

            for (int i = 0; i < size; i++)
                data[i] = new int[size];
        }
        SquareIntMatrix(const SquareIntMatrix& other): data(nullptr)
        {
            copy(other);
        }
        SquareIntMatrix& operator=(const SquareIntMatrix& other)
        {
            if (&other != this)
            {
                destroy();
                copy(other);
            }

            return *this;
        }
        ~SquareIntMatrix()
        {
            destroy();
        }

        bool operator==(const SquareIntMatrix& other) const
        {
            if (size != other.Size())
                return false;

            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    if (data[i][j] != other.data[i][j])
                        return false;

            return true;
        }

        int Size() const                  { return size; }

        const int* operator[](int i) const  { return data[i]; }
        int* operator[](int i)              { return data[i]; }
    };

    enum class Step  { None, Left, Right, Down, Up };

    class State: public SquareIntMatrix
    {
        int emptyCellY, emptyCellX;
        Step movement;

    public:
        State();
        State(int n, int from);
        State(const SquareIntMatrix& matrix, int emptyCellY_ = 0, int emptyCellX_ = 0);

        Step GetMovement() const  { return movement; }

        bool operator==(const State& other) const;

        std::shared_ptr<State> Move(Step movement) const;

        void Print() const;
    };

    int ManhattanDistance(const State& from, const State& to);
}


#endif  // __STATE__
