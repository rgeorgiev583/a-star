#include <cmath>
#include <utility>

#include "State.hpp"


SlidingBlocks::State::State()
{
    int n;
    scanf("%d", n);
    size = sqrt(n + 1);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &data[i][j]);

            if (data[i][j] == 0)
            {
                emptyCellY = i;
                emptyCellX = j;
            }
        }
}

SlidingBlocks::State::State(int n, int from)
{
    size = n;
    int block = from;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            data[i][j] = block == 9 ? block++ : 0;
}

SlidingBlocks::State::State(const SquareMatrix<int>& matrix, int _emptyCellY, int _emptyCellX):
        SquareMatrix<int>(matrix), emptyCellY(_emptyCellY), emptyCellX(_emptyCellX)  { }

bool SlidingBlocks::State::operator==(const SlidingBlocks::State& other) const
{
    return SquareMatrix<int>::operator==(other) &&
           emptyCellX == other.emptyCellX && emptyCellY == other.emptyCellY;
}

std::shared_ptr<SlidingBlocks::State> SlidingBlocks::State::Move(Step movement) const
{
    auto canMove = false;
    auto moved = *this;
    moved.movement = movement;

    switch (movement)
    {
        case Step::Left:
            if (emptyCellX < Size() - 1)
            {
                moved[moved.emptyCellY][moved.emptyCellX] = moved[moved.emptyCellY][moved.emptyCellX + 1];
                moved.emptyCellX++;
                canMove = true;
            }
            break;

        case Step::Right:
            if (emptyCellX > 0)
            {
                moved[moved.emptyCellY][moved.emptyCellX] = moved[moved.emptyCellY][moved.emptyCellX - 1];
                moved.emptyCellX--;
                canMove = true;
            }
            break;

        case Step::Down:
            if (emptyCellY < Size() - 1)
            {
                moved[moved.emptyCellY][moved.emptyCellX] = moved[moved.emptyCellY + 1][moved.emptyCellX];
                moved.emptyCellX++;
                canMove = true;
            }
            break;

        case Step::Up:
            if (emptyCellY < Size() - 1)
            {
                moved[moved.emptyCellY][moved.emptyCellX] = moved[moved.emptyCellY - 1][moved.emptyCellX];
                moved.emptyCellX--;
                canMove = true;
            }
            break;
    }

    if (canMove)
        moved[emptyCellY][emptyCellX] = 0;
    return canMove ? std::make_shared<SlidingBlocks::State>(moved) : nullptr;
}

void SlidingBlocks::State::Print() const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%d ", data[i][j]);
    }

    printf("\n");
}

int SlidingBlocks::ManhattanDistance(const State& from, const State& to)
{
    int size = from.Size();

    if (size != to.Size())
        return -1;

    int count = 0;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (from[i][j] != to[i][j])
                count++;

    return count;
}
