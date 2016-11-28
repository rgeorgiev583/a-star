#include <vector>
#include <list>
#include <algorithm>
#include <memory>

#include "AStar.hpp"


SlidingBlocks::Node::Node(StatePtr state, NodePtr parent): State(state), Parent(parent), G(0), H(0)  { }

SlidingBlocks::StateList SlidingBlocks::FindPath(const State& source, const State& target, HeuristicFunction heuristic)
{
    std::list<NodePtr> openSet;
    std::vector<NodePtr> closedSet;
    NodePtr currentNode = nullptr;
    auto sourceNode = std::make_shared<Node>(std::make_shared<State>(source));
    sourceNode->H = heuristic(source, target);
    openSet.push_back(sourceNode);

    while (!openSet.empty())
    {
        auto currentPos = std::min_element(openSet.begin(), openSet.end(), [](auto a, auto b) {
            return a->H <= b->H;
        });

        currentNode = *currentPos;
        if (*currentNode->State == target)
            break;

        closedSet.push_back(currentNode);
        openSet.erase(currentPos);

        auto move = [&target, heuristic, &openSet, &closedSet, currentNode](Step movement)
        {
            auto neighbor = currentNode->State->Move(movement);
            if (!neighbor)
                return;

            auto checkIfIsEqualToNeighbor = [neighbor](auto item)
            {
                return *item->State == *neighbor;
            };

            if (closedSet.end() != std::find_if(closedSet.begin(), closedSet.end(), checkIfIsEqualToNeighbor))
                return;

            int totalCost = currentNode->G + ManhattanDistance(*currentNode->State, *neighbor);
            auto successorPos = std::find_if(openSet.begin(), openSet.end(), checkIfIsEqualToNeighbor);

            if (openSet.end() == successorPos)
            {
                auto successorNode = std::make_shared<Node>(neighbor, currentNode);
                successorNode->G = totalCost;
                successorNode->H = successorNode->G + heuristic(*neighbor, target);
                openSet.push_back(successorNode);
            }
            else
            {
                auto successor = *successorPos;
                if (totalCost >= successor->G)
                    successor->Parent = currentNode;
            }
        };

        move(Step::Left);
        move(Step::Down);
        move(Step::Right);
        move(Step::Up);
    }

    StateList path;

    while (currentNode)
    {
        path.push_back(currentNode->State);
        currentNode = currentNode->Parent;
    }

    return path;
}
