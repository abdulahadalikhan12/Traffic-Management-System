#include "../src/Graph.h"
#include "../src/MinHeap.h"


Road::Road(char dest, int travelTime)
    : dest(dest), travelTime(travelTime), next(nullptr), status(1) {}

Intersection::Intersection(char name, int greenTime)
    : name(name), greenTime(greenTime), roads(nullptr), next(nullptr) {}

Graph::Graph()
{
    for (int i = 0; i < MAX_INTERSECTIONS; ++i)
    {
        intersections[i] = nullptr;
    }
}

// add a new intersection
void Graph::addIntersection(char name, int greenTime)
{
    int index = name - 'A'; // Map 'A' to 0, 'B' to 1, ..., 'Z' to 25
    if (index < 0 || index >= MAX_INTERSECTIONS)
    {
        std::cout << "Invalid intersection name!" << std::endl;
        return;
    }

    if (intersections[index] == nullptr)
    {
        intersections[index] = new Intersection(name, greenTime);
    }
}

// find an intersection by its name
Intersection *Graph::findIntersection(char name)
{
    int index = name - 'A'; // Map 'A' to 0, 'B' to 1, ..., 'Z' to 25
    if (index < 0 || index >= MAX_INTERSECTIONS)
    {
        return nullptr;
    }
    return intersections[index];
}

// add a road between two intersections
void Graph::addRoad(char from, char to, int travelTime)
{
    Intersection *fromIntersection = findIntersection(from);
    if (!fromIntersection)
    {
        addIntersection(from);
        fromIntersection = findIntersection(from);
    }

    Road *newRoad = new Road(to, travelTime);
    newRoad->next = fromIntersection->roads;
    fromIntersection->roads = newRoad;
}

// Visualize the city traffic network (intersection names and their roads)
void Graph::visualizeNetwork()
{
    for (int i = 0; i < MAX_INTERSECTIONS; ++i)
    {
        if (intersections[i])
        {
            std::cout << intersections[i]->name << " -> ";
            Road *road = intersections[i]->roads;
            while (road)
            {
                std::cout << "(" << road->dest << ", " << road->travelTime << "s) ";
                road = road->next;
            }
            std::cout << std::endl;
        }
    }
}

void Graph::visualizeSignals()
{
    for (int i = 0; i < MAX_INTERSECTIONS; i++)
    {
        if (intersections[i])
        {
            std::cout << intersections[i]->name << " -> " << intersections[i]->greenTime << "s" << std::endl;
        }
    }
}

// Create intersections from a CSV file
void Graph::createIntersections(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line))
    {
        char name;
        int greenTime;
        if (sscanf(line.c_str(), "%c,%d", &name, &greenTime) == 2)
        {
            addIntersection(name, greenTime);
        }
    }

    file.close();
}

// Create roads between intersections from a CSV file
void Graph::createNetwork(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line))
    {
        char from, to;
        int travelTime;
        if (sscanf(line.c_str(), "%c,%c,%d", &from, &to, &travelTime) == 3)
        {
            addRoad(from, to, travelTime);
        }
    }

    file.close();
}

// Dijkstra's Algorithm to find shortest path
void Graph::dijkstra(char start, char end)
{
    int dist[MAX_INTERSECTIONS];     // distance array
    int parent[MAX_INTERSECTIONS];   // parent array for path reconstruction
    bool visited[MAX_INTERSECTIONS]; // visited array
    MinHeap pq(MAX_INTERSECTIONS);   // min-heap priority queue

    std::fill(dist, dist + MAX_INTERSECTIONS, INT_MAX);     // init distances to infinity
    std::fill(visited, visited + MAX_INTERSECTIONS, false); // init visited array to false
    std::fill(parent, parent + MAX_INTERSECTIONS, -1);      // init parent array to -1

    int startIndex = start - 'A';
    int endIndex = end - 'A';

    dist[startIndex] = 0;

    // single source shortest path
    pq.insert({0, start}); // insert the source node into the priority queue

    while (!pq.isEmpty())
    {
        MinHeap::Node current = pq.extractMin();
        char u = current.node;
        int uIndex = u - 'A';

        if (visited[uIndex])
            continue; // skip if already visited
        visited[uIndex] = true;

        Intersection *intersection = findIntersection(u);
        if (!intersection)
            continue;

        Road *road = intersection->roads;
        while (road)
        {
            char v = road->dest;
            int weight = road->travelTime;
            int vIndex = v - 'A';

            if (dist[uIndex] != INT_MAX && dist[uIndex] + weight < dist[vIndex])
            {
                dist[vIndex] = dist[uIndex] + weight;
                parent[vIndex] = uIndex;
                pq.insert({dist[vIndex], v});
            }
            road = road->next;
        }
    }

    // output the shortest path and its distance
    if (dist[endIndex] == INT_MAX)
    {
        std::cout << "No path found from " << start << " to " << end << "." << std::endl;
    }
    else
    {
        std::cout << "Shortest path from " << start << " to " << end << " is " << dist[endIndex] << "s." << std::endl;
        std::cout << "Path: ";
        char path[MAX_INTERSECTIONS];
        int pathLength = 0;
        int current = endIndex;

        while (current != -1)
        {
            path[pathLength++] = 'A' + current;
            current = parent[current];
        }

        for (int i = pathLength - 1; i >= 0; i--)
        {
            std::cout << path[i] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::simulateRoadClosure(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    while(getline(file, line))
    {
        char start, end;
        std::string status;
        if (sscanf(line.c_str(), "%c,%c,%d", &start, &end, &status) == 3)
        {
            updateRoadStatus(start, end, status);
        }
    }
    file.close();
}

void Graph::updateRoadStatus(char start, char end, std::string status)
{
    Intersection *startIntersection = findIntersection(start);
    
    //If the starting intersection is not found
    if(startIntersection == NULL)
        std::cout << "Intersection "<<start<<" not found.\n";
    
    else{
        Road *temp = startIntersection -> roads;
        
        //Iterate to end of the list if necessary
        while(temp != NULL){
            //if the destination is the same then we assign new status
            if(temp-> dest == end){
                
                if(status == "Clear"){
                    temp -> status = 1;
                    std::cout<<"New Status for "<<start<<" -> "<<end<<" = Clear";
                }

                else if(status == "Blocked"){
                    temp -> status = 2;
                    std::cout<<"New Status for "<<start<<" -> "<<end<<" = Blocked";
                }

                else if(status == "Under Repair"){
                    temp -> status = 3;
                    std::cout<<"New Status for "<<start<<" -> "<<end<<" = Under Repair";
                }
                return;
            }
            temp = temp -> next;
        }
    }
}

