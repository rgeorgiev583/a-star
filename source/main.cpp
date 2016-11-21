#include <iostream>

#include "AStar.hpp"

int main()
{
    int n;
    scanf("%d", &n);
    SlidingBlocks::State begin(n, 1), end(begin.Size(), 1);
    auto path = std::move(SlidingBlocks::FindPath(begin, end));

    printf("%d\n", path.size());

    for (auto node: path)
        switch (node->GetMovement())
        {
            case SlidingBlocks::Step::Left:
                printf("left\n");
                break;

            case SlidingBlocks::Step::Right:
                printf("right\n");
                break;

            case SlidingBlocks::Step::Down:
                printf("down\n");
                break;

            case SlidingBlocks::Step::Up:
                printf("up\n");
                break;

            default:
                break;
        }
    return 0;
}
