#include <algorithm>
#include <memory>

#include "AStar.hpp"


SlidingBlocks::Node::Node(StatePtr state, NodePtr parent): State(state), Parent(parent), G(0), H(0)  { }

int SlidingBlocks::Node::GetScore() const
{
    return G + H;
}

SlidingBlocks::StateList SlidingBlocks::FindPath(const State& source, const State& target, HeuristicFunction heuristic)
{
    NodeSet openSet, closedSet;
    NodePtr current = nullptr;
    openSet.push_back(std::make_shared<Node>(std::make_shared<State>(source)));

    while (!openSet.empty())
    {
        auto currentPos = std::min_element(openSet.begin(), openSet.end(), [](auto a, auto b) {
            return a->GetScore() <= b->GetScore();
        });

        current = *currentPos;
        if (*current->State == target)
            break;

        closedSet.push_back(current);
        openSet.erase(currentPos);

        auto move = [&target, heuristic, &openSet, &closedSet, current](Step movement)
        {
            auto neighbor = current->State->Move(movement);
            if (!neighbor)
                return;

            auto checkIfIsEqualToNeighbor = [neighbor](auto item)
            {
                return *item->State == *neighbor;
            };

            if (closedSet.end() != std::find_if(closedSet.begin(), closedSet.end(), checkIfIsEqualToNeighbor))
                return;

            int totalCost = current->G + 1;

            auto successorPos = std::find_if(openSet.begin(), openSet.end(), checkIfIsEqualToNeighbor);
            auto successor = *successorPos;
            if (openSet.end() == successorPos)
            {
                auto successorNode = std::make_shared<Node>(neighbor, current);
                successor->G = totalCost;
                successor->H = heuristic(*successorNode->State, target);
                openSet.push_back(successorNode);
            }
            else if (totalCost < successor->G)
            {
                successor->Parent = current;
                successor->G = totalCost;
            }
        };

        move(Step::Left);
        move(Step::Down);
        move(Step::Right);
        move(Step::Up);
    }

    StateList path;

    while (current)
    {
        path.push_back(current->State);
        current = current->Parent;
    }

    return path;
}
